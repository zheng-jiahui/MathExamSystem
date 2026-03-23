// 包含头文件
#include "IPCServer.h"
#include "../backend/Core/BackendCore.h"
#include <QDebug>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#include <sstream>

// 单例模式：获取唯一实例
IPCServer& IPCServer::instance()
{
    static IPCServer instance;
    return instance;
}

// 清空输出缓冲区辅助函数
void IPCServer::clearOutputBuffers()
{
    outputBuffer.str("");
    outputBuffer.clear();
    errorBuffer.str("");
    errorBuffer.clear();
}

// 捕获输出并添加到响应的辅助函数
void IPCServer::captureAndAddOutputToResponse(QJsonObject &response)
{
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
}

// 根据输出设置错误响应的辅助函数
void IPCServer::setupErrorResponseFromOutput(QJsonObject &response, bool success)
{
    std::string errorOutput = errorBuffer.str();
    if (!errorOutput.empty()) {
        response["message"] = QString::fromStdString(errorOutput).trimmed();
        errorBuffer.str("");
        errorBuffer.clear();
    } else if (success) {
        response["message"] = "操作成功";
    } else {
        response["message"] = "操作失败";
    }
}

// 构建用户信息响应的辅助函数
QJsonObject IPCServer::buildUserInfoResponse(const QJsonObject &params)
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

// 构建题目响应的辅助函数
QJsonObject IPCServer::buildQuestionResponse()
{
    QJsonObject response;
    response["function"] = "GetCurrentQuestion";

    auto question = backendCore->GetCurrentQuestion();
    response["success"] = true;

    QJsonObject questionObj;
    questionObj["content"] = QString::fromStdString(question.content);

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

// 构建考试结果响应的辅助函数
QJsonObject IPCServer::buildExamResultResponse()
{
    QJsonObject response;
    response["function"] = "SubmitExam";

    auto result = backendCore->SubmitExam();
    response["success"] = true;

    QJsonObject resultObj;
    resultObj["totalQuestions"] = result.totalQuestions;
    resultObj["correctAnswers"] = result.correctAnswers;
    resultObj["score"] = result.score;
    resultObj["userType"] = QString::fromStdString(result.userType);

    response["examResult"] = resultObj;
    response["message"] = "考试提交成功";
    return response;
}

// 输出重定向相关方法
void IPCServer::setupOutputRedirection()
{
    originalCoutBuf = std::cout.rdbuf();
    originalCerrBuf = std::cerr.rdbuf();
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
    : QObject(parent), server(nullptr), currentClient(nullptr), backendCore(nullptr),
      originalCoutBuf(nullptr), originalCerrBuf(nullptr)
{
    serverName = "MathExamSystem_Server";
    setupOutputRedirection();
}

// 启动服务器
bool IPCServer::startServer()
{
    if (server) {
        return true;
    }

    backendCore = &BackendCore::GetInstance();
    server = new QLocalServer(this);
    QLocalServer::removeServer(serverName);

    connect(server, &QLocalServer::newConnection,
            this, &IPCServer::handleNewConnection);

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
        server->close();
        server->deleteLater();
        server = nullptr;
    }
}

// 处理新连接
void IPCServer::handleNewConnection()
{
    if (currentClient) {
        QLocalSocket *newClient = server->nextPendingConnection();
        newClient->close();
        newClient->deleteLater();
        return;
    }

    currentClient = server->nextPendingConnection();
    connect(currentClient, &QLocalSocket::readyRead,
            this, &IPCServer::readClientData);
    connect(currentClient, &QLocalSocket::disconnected,
            this, &IPCServer::clientDisconnected);

    qDebug() << "前端已连接";
}

// 读取客户端数据
void IPCServer::readClientData()
{
    if (!currentClient) return;

    while (currentClient->canReadLine()) {
        QByteArray data = currentClient->readLine();
        data = data.trimmed();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject request = doc.object();
            processRequest(request, currentClient);
        }
    }
}

// 客户端断开连接处理
void IPCServer::clientDisconnected()
{
    if (currentClient) {
        currentClient->deleteLater();
        currentClient = nullptr;
    }
    qDebug() << "前端已断开连接";
}

// 处理请求的核心方法
void IPCServer::processRequest(const QJsonObject &request, QLocalSocket *client)
{
    QString function = request["function"].toString();
    QJsonObject params = request["params"].toObject();
    QJsonObject response;
    response["function"] = function;

    if (function == "Login") response = handleLogin(params);
    else if (function == "RegisterUser") response = handleRegisterUser(params);
    else if (function == "CompleteRegistrationWithType") response = handleCompleteRegistration(params);
    else if (function == "ChangePassword") response = handleChangePassword(params);
    else if (function == "GenerateExam") response = handleGenerateExam(params);
    else if (function == "GetCurrentQuestion") response = handleGetCurrentQuestion(params);
    else if (function == "SubmitAnswer") response = handleSubmitAnswer(params);
    else if (function == "MoveToNextQuestion") response = handleMoveToNextQuestion(params);
    else if (function == "MoveToPreviousQuestion") response = handleMoveToPreviousQuestion(params);
    else if (function == "SubmitExam") response = handleSubmitExam(params);
    else if (function == "SwitchUserType") response = handleSwitchUserType(params);
    else if (function == "GetCurrentUser") response = handleGetCurrentUser(params);
    else if (function == "IsLoggedIn") response = handleIsLoggedIn(params);
    else if (function == "GetTotalQuestions") response = handleGetTotalQuestions(params);
    else if (function == "GetCurrentQuestionIndex") response = handleGetCurrentQuestionIndex(params);
    else {
        response["success"] = false;
        response["message"] = "未知的函数: " + function;
    }

    sendResponse(client, response);
}

// 发送响应给客户端
void IPCServer::sendResponse(QLocalSocket *client, const QJsonObject &response)
{
    if (!client || client->state() != QLocalSocket::ConnectedState) {
        qDebug() << "客户端不存在或连接状态";
        return;
    }

    QJsonDocument doc(response);
    QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n";
    client->write(data);
    client->flush();
}

// ========== 后端核心方法包装 ==========

// 处理登录请求
QJsonObject IPCServer::handleLogin(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "Login";
    clearOutputBuffers();

    std::string username = params["username"].toString().toStdString();
    std::string password = params["password"].toString().toStdString();

    bool success = backendCore->Login(username, password);
    response["success"] = success;

    captureAndAddOutputToResponse(response);

    if (success) {
        auto user = backendCore->GetCurrentUser();
        QJsonObject userInfo;
        userInfo["username"] = QString::fromStdString(user.username);
        userInfo["email"] = QString::fromStdString(user.email);
        userInfo["userType"] = QString::fromStdString(user.userType);
        response["userInfo"] = userInfo;
        response["message"] = "登录成功";
    } else {
        setupErrorResponseFromOutput(response, success);
        if (!response.contains("message")) {
            response["message"] = "登录失败";
        }
    }

    return response;
}

// 处理用户注册请求
QJsonObject IPCServer::handleRegisterUser(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "RegisterUser";
    clearOutputBuffers();

    std::string username = params["username"].toString().toStdString();
    std::string email = params["email"].toString().toStdString();
    std::string regCode;

    bool success = backendCore->RegisterUser(username, email, regCode);
    response["success"] = success;
    response["regCode"] = QString::fromStdString(regCode);

    // 捕获输出信息
    captureAndAddOutputToResponse(response);

    // 精确的错误处理逻辑
    std::string errorOutput = errorBuffer.str();
    if (!errorOutput.empty()) {
        // 有错误输出，使用具体错误信息
        response["message"] = QString::fromStdString(errorOutput).trimmed();
        errorBuffer.str("");
        errorBuffer.clear();
    } else if (success) {
        // 成功且没有错误输出
        response["message"] = "注册码发送成功";
    } else {
        // 失败但没有具体错误信息
        response["message"] = "注册申请失败";
    }

    return response;
}

// 处理完成注册请求
QJsonObject IPCServer::handleCompleteRegistration(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "CompleteRegistrationWithType";
    clearOutputBuffers();
    QString usernameQStr = params["username"].toString();
    QString emailQStr = params["email"].toString();
    QString regCodeQStr = params["regCode"].toString();
    QString passwordQStr = params["password"].toString();
    QString confirmPasswordQStr = params["confirmPassword"].toString();
    QString userTypeQStr = params["userType"].toString();
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
        username, email, regCode, password, confirmPassword, userType);
    captureAndAddOutputToResponse(response);
    setupErrorResponseFromOutput(response, success);
    response["success"] = success;
    return response;
}

// 处理修改密码请求
QJsonObject IPCServer::handleChangePassword(const QJsonObject &params)
{
    QJsonObject response;
    response["function"] = "ChangePassword";
    clearOutputBuffers();

    std::string oldPassword = params["oldPassword"].toString().toStdString();
    std::string newPassword = params["newPassword"].toString().toStdString();
    std::string confirmNewPassword = params["confirmNewPassword"].toString().toStdString();

    bool success = backendCore->ChangePassword(oldPassword, newPassword, confirmNewPassword);

    captureAndAddOutputToResponse(response);
    setupErrorResponseFromOutput(response, success);
    response["success"] = success;

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
    Q_UNUSED(params)
    return buildQuestionResponse();
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

    bool success = backendCore->MoveToNextQuestion();
    response["success"] = success;
    response["message"] = success ? "移动到下一题" : "无法移动到下一题";

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
    return buildExamResultResponse();
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
    return buildUserInfoResponse(params);
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
