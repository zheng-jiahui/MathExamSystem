// 包含头文件
#include "IPCServer.h"
#include "../backend/Core/BackendCore.h"  // 后端核心头文件
#include <QDebug>        // 调试输出
#include <QDataStream>   // 数据流操作
#include <QJsonDocument> // JSON文档处理
#include <QJsonArray>    // JSON数组
#include <QJsonObject>   // JSON对象
#include <QDebug>
#include <iostream>
#include <sstream>

//这个文件实现了后端服务的通信服务器，是前端与后端业务逻辑之间的桥梁

// 单例模式：获取唯一实例
IPCServer& IPCServer::instance()
{
    static IPCServer instance;  // 静态局部变量，程序生命周期内只创建一次
    return instance;
}

// C++的标准输出(std::cout)和标准错误输出(std::cerr)从默认的控制台重定向到字符串流缓冲区。
// 效果：所有std::cout输出都会流向outputBuffer
// 效果：所有std::cerr输出都会流向errorBuffer
void IPCServer::setupOutputRedirection()
{
    // 保存原始缓冲区
    originalCoutBuf = std::cout.rdbuf();
    originalCerrBuf = std::cerr.rdbuf();
    
    // 重定向到字符串流
    std::cout.rdbuf(outputBuffer.rdbuf());
    std::cerr.rdbuf(errorBuffer.rdbuf());
}

void IPCServer::restoreOutputRedirection()
{
    if (originalCoutBuf) {
        std::cout.rdbuf(originalCoutBuf);
    }
    if (originalCerrBuf) {
        std::cerr.rdbuf(originalCerrBuf);
    }
}

void IPCServer::sendOutputMessage(const QString& message, bool isError)
{
    QJsonObject outputMsg;
    outputMsg["type"] = "realtime_output";
    outputMsg["isError"] = isError;
    outputMsg["message"] = message;
    outputMsg["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    sendResponse(currentClient, outputMsg);
}

void IPCServer::handleOutput(const QString& message, bool isError)
{
    if (!currentClient || currentClient->state() != QLocalSocket::ConnectedState) {
        return;
    }
    
    QJsonObject outputMessage;
    outputMessage["type"] = "output";
    outputMessage["isError"] = isError;
    outputMessage["message"] = message;
    outputMessage["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    sendResponse(currentClient, outputMessage);
}

// 构造函数
IPCServer::IPCServer(QObject *parent)
    : QObject(parent)           // 调用父类构造函数
    , server(nullptr)           // 初始化服务器指针为空
    , currentClient(nullptr)    // 初始化客户端指针为空
    , backendCore(nullptr)      // 初始化后端核心指针为空
    , originalCoutBuf(nullptr)
    , originalCerrBuf(nullptr)
{
    serverName = "MathExamSystem_Server";  // 设置服务器名称
    setupOutputRedirection(); // 设置输出重定向
}

// 启动服务器
bool IPCServer::startServer()
{
    // 如果服务器已经启动，直接返回true
    if (server) {
        return true;
    }

    // 初始化后端核心 - 获取单例实例
    backendCore = &BackendCore::GetInstance();

    // 创建本地服务器对象
    server = new QLocalServer(this);

    // 移除可能存在的旧服务器实例（避免端口占用）
    QLocalServer::removeServer(serverName);

    // 连接信号槽：当有新连接时调用handleNewConnection
    connect(server, &QLocalServer::newConnection,
            this, &IPCServer::handleNewConnection);

    // 开始监听指定名称的服务器
    if (!server->listen(serverName)) {
        qDebug() << "无法启动IPC服务器:" << server->errorString();
        return false;
    }

    qDebug() << "IPC服务器已启动:" << serverName;
    return true;
}

// 停止服务器
void IPCServer::stopServer()
{
    if (server) {
        server->close();        // 关闭服务器
        server->deleteLater();  // 延迟删除对象
        server = nullptr;       // 指针置空
    }
}

// 处理新连接
void IPCServer::handleNewConnection()
{
    // 如果已经有客户端连接，拒绝新的连接
    if (currentClient) {
        QLocalSocket *newClient = server->nextPendingConnection();
        newClient->close();      // 关闭新连接
        newClient->deleteLater(); // 清理资源
        return;
    }

    // 接受新客户端连接
    currentClient = server->nextPendingConnection();

    // 连接信号槽：当客户端有数据可读时
    connect(currentClient, &QLocalSocket::readyRead,
            this, &IPCServer::readClientData);

    // 连接信号槽：当客户端断开连接时
    connect(currentClient, &QLocalSocket::disconnected,
            this, &IPCServer::clientDisconnected);

    qDebug() << "前端已连接";
}

// 读取客户端数据
void IPCServer::readClientData()
{
    // 检查当前客户端是否存在
    if (!currentClient) return;

    // 循环读取所有可读的数据行
    // 当socket有数据可读时自动触发
    while (currentClient->canReadLine()) {
        // 读取一行数据并去除首尾空白字符
        QByteArray data = currentClient->readLine();// ← 读取前端发送的数据
        data = data.trimmed();

        // 将JSON数据解析为文档对象
        QJsonDocument doc = QJsonDocument::fromJson(data);

        // 检查是否是有效的JSON对象
        if (doc.isObject()) {
            QJsonObject request = doc.object();  // 获取JSON对象
            processRequest(request, currentClient); // ← 然后调用processRequest处理
        }
    }
}

// 客户端断开连接处理
void IPCServer::clientDisconnected()
{
    if (currentClient) {
        currentClient->deleteLater();  // 清理客户端资源
        currentClient = nullptr;       // 指针置空
    }
    qDebug() << "前端已断开连接";
}

// 处理请求的核心方法
void IPCServer::processRequest(const QJsonObject &request, QLocalSocket *client)
{
    // 从请求中提取函数名和参数
    QString function = request["function"].toString();//从请求中获取要执行的功能名称
    QJsonObject params = request["params"].toObject();//获取该功能需要的参数
    QJsonObject response;//创建空的响应对象

    // 在响应中回显函数名，便于前端识别
    response["function"] = function;

    // 路由到对应的处理函数 - 根据函数名调用不同的处理方法
    if (function == "Login") {
        response = handleLogin(params);
    }
    else if (function == "RegisterUser") {
        response = handleRegisterUser(params);
    }
    else if (function == "CompleteRegistrationWithType") {
        response = handleCompleteRegistration(params);
    }
    else if (function == "ChangePassword") {
        response = handleChangePassword(params);
    }
    else if (function == "GenerateExam") {
        response = handleGenerateExam(params);
    }
    else if (function == "GetCurrentQuestion") {
        response = handleGetCurrentQuestion(params);
    }
    else if (function == "SubmitAnswer") {
        response = handleSubmitAnswer(params);
    }
    else if (function == "MoveToNextQuestion") {
        response = handleMoveToNextQuestion(params);
    }
    else if (function == "MoveToPreviousQuestion") {
        response = handleMoveToPreviousQuestion(params);
    }
    else if (function == "SubmitExam") {
        response = handleSubmitExam(params);
    }
    else if (function == "SwitchUserType") {
        response = handleSwitchUserType(params);
    }
    else if (function == "GetCurrentUser") {
        response = handleGetCurrentUser(params);
    }
    else if (function == "IsLoggedIn") {
        response = handleIsLoggedIn(params);
    }
    else if (function == "GetTotalQuestions") {
        response = handleGetTotalQuestions(params);
    }
    else if (function == "GetCurrentQuestionIndex") {
        response = handleGetCurrentQuestionIndex(params);
    }
    else {
        // 未知函数处理
        response["success"] = false;
        response["message"] = "未知的函数: " + function;
    }

    // 发送响应给客户端
    sendResponse(client, response);
}

// 发送响应给客户端
void IPCServer::sendResponse(QLocalSocket *client, const QJsonObject &response)
{
    // 检查客户端是否存在且处于连接状态
    if (!client || client->state() != QLocalSocket::ConnectedState) {
        qDebug() <<"客户端不存在或连接状态";
        return;
    }

    // 将JSON对象转换为紧凑格式的JSON字符串，并添加换行符
    QJsonDocument doc(response);
    QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n";

    // 发送数据并立即刷新缓冲区
    client->write(data);
    client->flush();
}

// ========== 后端核心方法包装 - 每个方法都是前端请求的处理器 ==========

// 处理登录请求
//返回路径handleLogin()
   // → return response
   // → processRequest()
   //→ sendResponse()
   //→ 前端 BackendInterface
QJsonObject IPCServer::handleLogin(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "Login";

    // 清空输出缓冲区
    outputBuffer.str("");
    outputBuffer.clear();
    errorBuffer.str("");
    errorBuffer.clear();

    // 从参数中提取用户名和密码，并转换为std::string
    std::string username = params["username"].toString().toStdString();
    std::string password = params["password"].toString().toStdString();

    // 调用后端核心的登录方法
    bool success = backendCore->Login(username, password);
    response["success"] = success;

    // 捕获并发送输出信息
    std::string output = outputBuffer.str();
    if (!output.empty()) {
        response["output"] = QString::fromStdString(output);
        outputBuffer.str("");
        outputBuffer.clear();
    }
    
    std::string errorOutput = errorBuffer.str();
    if (!errorOutput.empty()) {
        response["errorOutput"] = QString::fromStdString(errorOutput);
        errorBuffer.str("");
        errorBuffer.clear();
    }

    if (success) {
        // 登录成功，获取用户信息
        auto user = backendCore->GetCurrentUser();
        QJsonObject userInfo;
        userInfo["username"] = QString::fromStdString(user.username);
        userInfo["email"] = QString::fromStdString(user.email);
        userInfo["userType"] = QString::fromStdString(user.userType);
        response["userInfo"] = userInfo;
        response["message"] = "登录成功";
    } else {
        if (!errorOutput.empty()) {
            response["errorOutput"] = QString::fromStdString(errorOutput);
            response["message"]=response["errorOutput"];
            errorBuffer.str("");
            errorBuffer.clear();
        } else  response["message"] = "登录失败";
    }

    return response;
}

// 处理用户注册请求
// 返回QJsonObject：包含处理结果的JSON对象，
// 接收params：从前端传来的参数（也是JSON对象）
QJsonObject IPCServer::handleRegisterUser(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "RegisterUser";

    // 清空输出缓冲区
    outputBuffer.str("");
    outputBuffer.clear();
    errorBuffer.str("");
    errorBuffer.clear();

    // 从前端参数中提取用户名和邮箱地址
    std::string username = params["username"].toString().toStdString();
    std::string email = params["email"].toString().toStdString();
    std::string regCode;  // 用于接收后端生成的注册码

    // 调用后端注册方法
    bool success = backendCore->RegisterUser(username, email, regCode);
    response["success"] = success;
    response["regCode"] = QString::fromStdString(regCode);

    // 捕获标准输出信息
    std::string output = outputBuffer.str();
    if (!output.empty()) {
        response["output"] = QString::fromStdString(output);
        outputBuffer.str("");
        outputBuffer.clear();
    }

    // 捕获错误输出信息
    std::string errorOutput = errorBuffer.str();
    if (!errorOutput.empty()) {
        response["errorOutput"] = QString::fromStdString(errorOutput);
        errorBuffer.str("");
        errorBuffer.clear();
    }

    // 关键修改：根据是否有错误输出来设置消息
    if (!errorOutput.empty()) {
        // 使用后端返回的具体错误信息
        response["message"] = QString::fromStdString(errorOutput).trimmed();
    } else if (success) {
        response["message"] = "注册码发送成功";
    } else {
        response["message"] = "注册申请失败";
    }

    return response;
}

// 处理完成注册请求
QJsonObject IPCServer::handleCompleteRegistration(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "CompleteRegistrationWithType";

    // 清空输出缓冲区
    outputBuffer.str("");
    outputBuffer.clear();
    errorBuffer.str("");
    errorBuffer.clear();

    // 直接从QJsonObject获取QString，然后转换为std::string
    QString usernameQStr = params["username"].toString();
    QString emailQStr = params["email"].toString();
    QString regCodeQStr = params["regCode"].toString();
    QString passwordQStr = params["password"].toString();
    QString confirmPasswordQStr = params["confirmPassword"].toString();
    QString userTypeQStr = params["userType"].toString();

    // 转换为std::string（使用toUtf8确保编码正确）
    std::string username = usernameQStr.toStdString();
    std::string email = emailQStr.toStdString();
    std::string regCode = regCodeQStr.toStdString();
    std::string password = passwordQStr.toStdString();
    std::string confirmPassword = confirmPasswordQStr.toStdString();
    std::string userType = userTypeQStr.toStdString();

    std::cout << "🔍 处理完成注册请求:" << std::endl;
    std::cout << "   用户类型原始QString: '" << userTypeQStr.toStdString() << "'" << std::endl;
    std::cout << "   用户类型std::string长度: " << userType.length() << std::endl;

    bool success = backendCore->CompleteRegistrationWithType(
        username,email, regCode, password, confirmPassword, userType);

    // 捕获并发送输出信息
    std::string output = outputBuffer.str();
    if (!output.empty()) {
        response["output"] = QString::fromStdString(output);
        outputBuffer.str("");
        outputBuffer.clear();
    }

    std::string errorOutput = errorBuffer.str();
    if (!errorOutput.empty()) {
        response["errorOutput"] = QString::fromStdString(errorOutput);
        errorBuffer.str("");
        errorBuffer.clear();
    }

    // 关键修改：根据是否有错误输出来设置消息
    if (!errorOutput.empty()) {
        // 使用后端返回的具体错误信息
        response["message"] = QString::fromStdString(errorOutput).trimmed();
    } else if (success) {
        response["message"] = "注册成功";
    } else {
        response["message"] = "注册失败";
    }

    response["success"] = success;

    return response;
}

// 处理修改密码请求
QJsonObject IPCServer::handleChangePassword(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "ChangePassword";

    // 清空输出缓冲区
    outputBuffer.str("");
    outputBuffer.clear();
    errorBuffer.str("");
    errorBuffer.clear();

    std::string oldPassword = params["oldPassword"].toString().toStdString();
    std::string newPassword = params["newPassword"].toString().toStdString();
    std::string confirmNewPassword = params["confirmNewPassword"].toString().toStdString();

    bool success = backendCore->ChangePassword(oldPassword, newPassword, confirmNewPassword);

    // 捕获并发送输出信息
    std::string output = outputBuffer.str();
    if (!output.empty()) {
        response["output"] = QString::fromStdString(output);
        outputBuffer.str("");
        outputBuffer.clear();
    }
    
    std::string errorOutput = errorBuffer.str();
    if (!errorOutput.empty()) {
        response["errorOutput"] = QString::fromStdString(errorOutput);
        errorBuffer.str("");
        errorBuffer.clear();
    }

    // 关键修改：根据是否有错误输出来设置消息
    if (!errorOutput.empty()) {
        // 使用后端返回的具体错误信息
        response["message"] = QString::fromStdString(errorOutput).trimmed();
    } else if (success) {
        response["message"] = "密码修改成功";
    } else {
        response["message"] = "密码修改失败";
    }

    response["success"] = success;
    //response["message"] = success ? "密码修改成功" : "密码修改失败";

    return response;
}

// 处理生成试卷请求
QJsonObject IPCServer::handleGenerateExam(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "GenerateExam";

    std::string userType = params["userType"].toString().toStdString();
    int questionCount = params["questionCount"].toInt();

    bool success = backendCore->GenerateExam(userType, questionCount);
    response["success"] = success;

    if (success) {
        //获取生成的题目总数并添加到响应
        response["totalQuestions"] = backendCore->GetTotalQuestions();
        response["message"] = "试卷生成成功";
    } else {
        response["message"] = "试卷生成失败";
    }

    return response;
}

// 处理获取当前题目请求
QJsonObject IPCServer::handleGetCurrentQuestion(const QJsonObject &params)
{
    Q_UNUSED(params)  // 告诉编译器这个参数未被使用（避免警告）

    QJsonObject response;
    response["function"] = "GetCurrentQuestion";

    // 从后端获取当前题目信息
    auto question = backendCore->GetCurrentQuestion();
    response["success"] = true;

    // 构建题目对象
    QJsonObject questionObj;
    questionObj["content"] = QString::fromStdString(question.content);

    // 构建选项数组
    QJsonArray options;
    for (const auto& option : question.options) {
        options.append(QString::fromStdString(option));
    }
    questionObj["options"] = options;
    questionObj["correctAnswer"] = question.correctAnswer;
    questionObj["userAnswer"] = question.userAnswer;

    response["question"] = questionObj;

    return response;
}

// 处理提交答案请求
QJsonObject IPCServer::handleSubmitAnswer(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "SubmitAnswer";

    int answer = params["answer"].toInt();
    bool success = backendCore->SubmitAnswer(answer);

    response["success"] = success;
    response["message"] = success ? "答案提交成功" : "答案提交失败";

    return response;
}

// 处理移动到下一题请求
QJsonObject IPCServer::handleMoveToNextQuestion(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "MoveToNextQuestion";

    //bool successsubmit = backendCore->SubmitAnswer(params["answer"].toInt());
    bool success = backendCore->MoveToNextQuestion();

    response["success"] = success ;
    response["message"] = success  ? "移动到下一题" : "无法移动到下一题";

    return response;
}

// 处理移动到上一题请求
QJsonObject IPCServer::handleMoveToPreviousQuestion(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "MoveToPreviousQuestion";

    bool success = backendCore->MoveToPreviousQuestion();
    response["success"] = success;
    response["message"] = success ? "移动到上一题" : "无法移动到上一题";

    return response;
}

// 处理提交考试请求
QJsonObject IPCServer::handleSubmitExam(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "SubmitExam";

    // 提交考试并获取结果
    auto result = backendCore->SubmitExam();
    response["success"] = true;

    // 构建考试结果对象
    QJsonObject resultObj;
    resultObj["totalQuestions"] = result.totalQuestions;
    resultObj["correctAnswers"] = result.correctAnswers;
    resultObj["score"] = result.score;
    resultObj["userType"] = QString::fromStdString(result.userType);

    response["examResult"] = resultObj;
    response["message"] = "考试提交成功";

    return response;
}

// 处理切换用户类型请求
QJsonObject IPCServer::handleSwitchUserType(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "SwitchUserType";

    std::string newUserType = params["newUserType"].toString().toStdString();
    bool success = backendCore->SwitchUserType(newUserType);

    response["success"] = success;
    response["message"] = success ? "用户类型切换成功" : "用户类型切换失败";

    return response;
}

// 处理获取当前用户信息请求
QJsonObject IPCServer::handleGetCurrentUser(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "GetCurrentUser";

    auto user = backendCore->GetCurrentUser();
    response["success"] = true;

    QJsonObject userInfo;
    userInfo["username"] = QString::fromStdString(user.username);
    userInfo["email"] = QString::fromStdString(user.email);
    userInfo["userType"] = QString::fromStdString(user.userType);

    response["userInfo"] = userInfo;

    return response;
}

// 处理检查登录状态请求
QJsonObject IPCServer::handleIsLoggedIn(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "IsLoggedIn";
    response["success"] = true;
    response["isLoggedIn"] = backendCore->IsLoggedIn();
    return response;
}

// 处理获取题目总数请求
QJsonObject IPCServer::handleGetTotalQuestions(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "GetTotalQuestions";
    response["success"] = true;
    response["totalQuestions"] = backendCore->GetTotalQuestions();
    return response;
}

// 处理获取当前题目索引请求
QJsonObject IPCServer::handleGetCurrentQuestionIndex(const QJsonObject &params)
{
    Q_UNUSED(params)

    QJsonObject response;
    response["function"] = "GetCurrentQuestionIndex";
    response["success"] = true;
    response["currentQuestionIndex"] = backendCore->GetCurrentQuestionIndex();
    return response;
}
