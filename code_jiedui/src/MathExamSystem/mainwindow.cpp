#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QButtonGroup>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>
#include <QMetaObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , answerButtonGroup(new QButtonGroup(this))
    , currentQuestionIndex(0)
    , totalQuestions(0)
{
    ui->setupUi(this);
    initializeUI();
    setupConnections();

    // 初始化后端连接
    if (!BackendInterface::instance().initialize()) {
        showMessage("无法连接到后端服务", true);
    }

    switchToPage(0); // 显示登录页面
}

MainWindow::~MainWindow()
{
    BackendInterface::instance().shutdown();
    delete ui;
}

void MainWindow::initializeUI()
{
    // 设置答案按钮组
    answerButtonGroup->addButton(ui->optionARadio, 0);
    answerButtonGroup->addButton(ui->optionBRadio, 1);
    answerButtonGroup->addButton(ui->optionCRadio, 2);
    answerButtonGroup->addButton(ui->optionDRadio, 3);

    // 设置窗口属性
    setWindowTitle("数学考试系统");
    setMinimumSize(800, 600);

    // 初始化状态标签
    ui->loginStatusLabel->setText("请登录以开始使用");
    ui->registerStatusLabel->setText("请填写完整的注册信息");
    ui->passwordStatusLabel->setText("请填写密码信息");
}

void MainWindow::setupConnections()
{
    // 连接后端信号
    connect(&BackendInterface::instance(), &BackendInterface::responseReceived,
            this, &MainWindow::onBackendResponse);
    connect(&BackendInterface::instance(), &BackendInterface::errorOccurred,
            this, &MainWindow::onBackendError);

    // 登录页面
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterClicked);

    // 注册页面
    connect(ui->sendCodeButton, &QPushButton::clicked, this, &MainWindow::onSendCodeClicked);
    connect(ui->completeRegisterButton, &QPushButton::clicked, this, &MainWindow::onCompleteRegisterClicked);
    connect(ui->backToLoginButton, &QPushButton::clicked, this, &MainWindow::onBackToLoginClicked);

    // 主菜单页面
    connect(ui->generateExamButton, &QPushButton::clicked, this, &MainWindow::onGenerateExamClicked);
    connect(ui->changePasswordButton, &QPushButton::clicked, this, &MainWindow::onChangePasswordClicked);
    connect(ui->switchUserTypeButton, &QPushButton::clicked, this, &MainWindow::onSwitchUserTypeClicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);

    // 考试页面
    connect(answerButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::onAnswerSelected);
    connect(ui->submitAnswerButton, &QPushButton::clicked, this, &MainWindow::onSubmitAnswerClicked);
    connect(ui->nextQuestionButton, &QPushButton::clicked, this, &MainWindow::onNextQuestionClicked);
    connect(ui->prevQuestionButton, &QPushButton::clicked, this, &MainWindow::onPreviousQuestionClicked);
    connect(ui->submitExamButton, &QPushButton::clicked, this, &MainWindow::onSubmitExamClicked);

    // 修改密码页面
    connect(ui->confirmChangePasswordButton, &QPushButton::clicked,
            this, &MainWindow::onConfirmChangePasswordClicked);
    connect(ui->backToMainFromPasswordButton, &QPushButton::clicked,
            this, &MainWindow::onBackToMainClicked);

    // 考试结果页面
    connect(ui->newExamButton, &QPushButton::clicked, this, &MainWindow::onNewExamClicked);
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &MainWindow::onBackToMenuClicked);
    connect(ui->viewDetailsButton, &QPushButton::clicked, this, &MainWindow::onViewDetailsClicked);
}

void MainWindow::switchToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::showMessage(const QString &message, bool isError)
{
    if (isError) {
        QMessageBox::critical(this, "错误", message);
    } else {
        QMessageBox::information(this, "提示", message);
    }
}

// 登录页面槽函数
void MainWindow::onLoginClicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        showMessage("请输入用户名和密码", true);
        return;
    }

    qDebug() << "用户尝试登录:" << username;

    ui->loginStatusLabel->setText("正在登录...");
    ui->loginButton->setEnabled(false);

    // 使用异步方式调用，避免界面卡住
    QTimer::singleShot(0, this, [this, username, password]() {
        callBackend("Login", {
            {"username", username},
            {"password", password}
        });
    });
}

void MainWindow::onRegisterClicked()
{
    switchToPage(1); // 注册页面
    ui->usernameRegEdit->clear();
    ui->emailEdit->clear();
    ui->codeEdit->clear();
    ui->regPasswordEdit->clear();
    ui->confirmPasswordEdit->clear();
    ui->userTypeComboBox->setCurrentIndex(0);
    ui->registerStatusLabel->setText("请填写完整的注册信息");
}

// 注册页面槽函数
void MainWindow::onSendCodeClicked()
{
    QString username = ui->usernameRegEdit->text().trimmed();
    QString email = ui->emailEdit->text().trimmed();

    if (username.isEmpty()) {
        showMessage("请输入用户名", true);
        return;
    }

    if (!validateEmail(email)) {
        showMessage("请输入有效的邮箱地址", true);
        return;
    }

    // 每次发送验证码前都清空输入框
    ui->codeEdit->clear();

    qDebug() << "📧 发送验证码请求 - 用户名:" << username << "邮箱:" << email;

    ui->registerStatusLabel->setText("正在发送注册码...");
    ui->sendCodeButton->setEnabled(false);

    callBackend("RegisterUser", {
        {"username", username},
        {"email", email}
    });
}

void MainWindow::onCompleteRegisterClicked()
{
    QString username = ui->usernameRegEdit->text().trimmed();
    QString email = ui->emailEdit->text().trimmed();
    QString code = ui->codeEdit->text().trimmed();
    QString password = ui->regPasswordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();
    QString userType = ui->userTypeComboBox->currentText();

    qDebug() << "🔍 用户尝试完成注册 - 详细参数:";
    qDebug() << "   用户名:" << username;
    qDebug() << "   邮箱:" << email;
    qDebug() << "   注册码:" << code;
    qDebug() << "   用户类型:" << userType;
    qDebug() << "   用户类型长度:" << userType.length();
    qDebug() << "   密码:" << password;
    qDebug() << "   确认密码:" << confirmPassword;

    if (!validateRegistrationInput()) {
        qDebug() << "❌ 前端验证失败";
        return;
    }

    qDebug() << "✅ 前端验证通过";

    ui->registerStatusLabel->setText("正在注册...");
    ui->completeRegisterButton->setEnabled(false);

    callBackend("CompleteRegistrationWithType", {
        {"username", username},
        {"email", email},
        {"regCode", code},
        {"password", password},
        {"confirmPassword", confirmPassword},
        {"userType", userType}
    });
}

void MainWindow::onBackToLoginClicked()
{
    switchToPage(0); // 返回登录页面
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    ui->loginStatusLabel->setText("请登录以开始使用");
}

// 主菜单页面槽函数
void MainWindow::onGenerateExamClicked()
{
    //ui->examTypeComboBox->setCurrentText(currentUserType);
    QString userType = ui->examTypeComboBox->currentText();
    int questionCount = ui->questionCountSpinBox->value();

    if (questionCount < 10 || questionCount > 30) {
        showMessage("题目数量必须在10-30之间", true);
        return;
    }

    callBackend("GenerateExam", {
        {"userType", userType},
        {"questionCount", questionCount}
    });
}

void MainWindow::onChangePasswordClicked()
{
    switchToPage(4); // 修改密码页面
    ui->oldPasswordEdit->clear();
    ui->newPasswordEdit->clear();
    ui->confirmNewPasswordEdit->clear();
    ui->passwordStatusLabel->setText("请填写密码信息");
}

void MainWindow::onSwitchUserTypeClicked()
{
    bool ok;
    QString newUserType = QInputDialog::getItem(this,
        "切换学习阶段",
        "选择新的学习阶段:",
        QStringList() << "小学" << "初中" << "高中",
        0,
        false,
        &ok);

    if (ok && !newUserType.isEmpty()) {
        ui->examTypeComboBox->setCurrentText(newUserType);
        callBackend("SwitchUserType", {
            {"newUserType", newUserType}
        });
    }
}

void MainWindow::onLogoutClicked()
{
    currentUsername.clear();
    currentUserType.clear();
    clearExamData();
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    switchToPage(0); // 返回登录页面

    showMessage("已成功退出登录");
}

// 考试页面槽函数
void MainWindow::onAnswerSelected()
{
    ui->submitAnswerButton->setEnabled(true);
}

void MainWindow::onSubmitAnswerClicked()
{
    int selectedAnswer = answerButtonGroup->checkedId();
    if (selectedAnswer == -1) {
        showMessage("请选择一个答案", true);
        return;
    }

    callBackend("SubmitAnswer", {
        {"answer", selectedAnswer}
    });
}

void MainWindow::onNextQuestionClicked()
{
    int selectedAnswer = answerButtonGroup->checkedId();
    if (selectedAnswer != -1)
        callBackend("SubmitAnswer", {
            {"answer", selectedAnswer}
        });
    callBackend("MoveToNextQuestion", {});
}

void MainWindow::onPreviousQuestionClicked()
{
    callBackend("MoveToPreviousQuestion", {});
}

void MainWindow::onSubmitExamClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "确认提交",
        "确定要提交试卷吗？提交后将无法修改答案。",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int selectedAnswer = answerButtonGroup->checkedId();
        if (selectedAnswer != -1)
            callBackend("SubmitAnswer", {
                {"answer", selectedAnswer}
            });
        callBackend("SubmitExam", {});
    }
}

// 修改密码页面槽函数
void MainWindow::onConfirmChangePasswordClicked()
{
    //if (!validateChangePasswordInput()) {
        //return;
    //}
    ui->passwordStatusLabel->setText("正在修改密码...");
    ui->confirmChangePasswordButton->setEnabled(false);

    callBackend("ChangePassword", {
        {"oldPassword", ui->oldPasswordEdit->text()},
        {"newPassword", ui->newPasswordEdit->text()},
        {"confirmNewPassword", ui->confirmNewPasswordEdit->text()}
    });
}

void MainWindow::onBackToMainClicked()
{
    switchToPage(2); // 返回主菜单
}

// 考试结果页面槽函数
void MainWindow::onNewExamClicked()
{
    switchToPage(2); // 返回主菜单
}

void MainWindow::onBackToMenuClicked()
{
    switchToPage(2); // 返回主菜单
}

void MainWindow::onViewDetailsClicked()
{
    QString details = QString("考试详情:\n"
                             "总题数: %1\n"
                             "正确题数: %2\n"
                             "得分: %3分\n"
                             "学习阶段: %4")
        .arg(currentExamResult["totalQuestions"].toInt())
        .arg(currentExamResult["correctAnswers"].toInt())
        .arg(currentExamResult["score"].toDouble())
        .arg(currentExamResult["userType"].toString());

    QMessageBox::information(this, "考试详情", details);
}

// 后端通信响应
void MainWindow::onBackendResponse(const QJsonObject &response)
{
    QString function = response["function"].toString();
    bool success = response["success"].toBool();
    QString message = response["message"].toString();

    qDebug() << "收到后端响应 - 函数:" << function << "成功:" << success << "消息:" << message;

    // 重新启用按钮
    ui->loginButton->setEnabled(true);
    ui->sendCodeButton->setEnabled(true);
    ui->completeRegisterButton->setEnabled(true);
    ui->confirmChangePasswordButton->setEnabled(true);

    if (!success) {
        qDebug() << "❌ 操作失败:" << message;
        showMessage(message, true);
        return;
    }

    qDebug() << "✅ 操作成功，处理响应...";

    if (function == "Login") {
        handleLoginResponse(response);
    }
    else if (function == "RegisterUser") {
        handleRegisterUserResponse(response);
    }
    else if (function == "CompleteRegistrationWithType") {
        handleCompleteRegistrationResponse(response);
    }
    else if (function == "ChangePassword") {
        handleChangePasswordResponse(response);
    }
    else if (function == "GenerateExam") {
        handleGenerateExamResponse(response);
    }
    else if (function == "GetCurrentQuestion") {
        handleGetCurrentQuestionResponse(response);
    }
    else if (function == "SubmitAnswer") {
        handleSubmitAnswerResponse(response);
    }
    else if (function == "MoveToNextQuestion" || function == "MoveToPreviousQuestion") {
        handleMoveQuestionResponse(response);
    }
    else if (function == "SubmitExam") {
        handleSubmitExamResponse(response);
    }
    else if (function == "SwitchUserType") {
        handleSwitchUserTypeResponse(response);
    }
    else {
        qDebug() << "⚠️ 未知函数响应:" << function;
    }
}

void MainWindow::onBackendError(const QString &error)
{
    qDebug() << "❌ 后端通信错误:" << error;

    // 重新启用按钮
    ui->loginButton->setEnabled(true);
    ui->sendCodeButton->setEnabled(true);
    ui->completeRegisterButton->setEnabled(true);
    ui->confirmChangePasswordButton->setEnabled(true);

    showMessage("通信错误: " + error, true);
}

// 响应处理函数
void MainWindow::handleLoginResponse(const QJsonObject &response)
{
    qDebug() << "🔐 处理登录响应...";

    if (response.contains("userInfo")) {
        QJsonObject userInfo = response["userInfo"].toObject();
        currentUsername = userInfo["username"].toString();
        currentUserType = userInfo["userType"].toString();

        qDebug() << "✅ 登录成功 - 用户名:" << currentUsername << "用户类型:" << currentUserType;

        updateUserInfo();
        switchToPage(2); // 主菜单页面
        showMessage("登录成功！");
    } else {
        qDebug() << "❌ 登录响应缺少用户信息";
        showMessage("登录响应数据不完整", true);
    }
}

void MainWindow::handleRegisterUserResponse(const QJsonObject &response)
{
    bool success = response["success"].toBool();
    QString message = response["message"].toString();
    QString regCode = response["regCode"].toString();

    // 获取详细的错误输出
    QString errorOutput = response["errorOutput"].toString();
    QString standardOutput = response["output"].toString();

    qDebug() << "📧 注册码请求响应 - 成功:" << success << "消息:" << message;
    qDebug() << "   注册码:" << regCode;
    qDebug() << "   错误输出:" << errorOutput;
    qDebug() << "   标准输出:" << standardOutput;

    if (success) {
        ui->registerStatusLabel->setText("注册码已发送到邮箱，请查收");
        showMessage("注册码已发送到邮箱");  // 成功时只显示成功消息
    } else {
        // 使用后端返回的具体错误信息
        QString displayMessage = message;  // 直接使用后端返回的消息
        ui->registerStatusLabel->setText("注册失败: " + displayMessage);
        showMessage(displayMessage, true);  // 显示具体的错误类型
    }
}

void MainWindow::handleCompleteRegistrationResponse(const QJsonObject &response)
{
    bool success = response["success"].toBool();
    QString message = response["message"].toString();

    // 获取详细的错误输出
    QString errorOutput = response["errorOutput"].toString();
    QString standardOutput = response["output"].toString();

    qDebug() << "✅ 完成注册响应 - 成功:" << success << "消息:" << message;
    qDebug() << "   错误输出:" << errorOutput;
    qDebug() << "   标准输出:" << standardOutput;

    if (success) {
        switchToPage(0); // 返回登录页面
        showMessage("注册成功！");  // 成功时只显示成功消息
    } else {
        // 使用后端返回的具体错误信息
        QString displayMessage = message;  // 直接使用后端返回的消息
        ui->registerStatusLabel->setText("注册失败: " + displayMessage);
        showMessage(displayMessage, true);  // 显示具体的错误类型
    }
}
void MainWindow::handleChangePasswordResponse(const QJsonObject &response)
{
    bool success = response["success"].toBool();
    QString message = response["message"].toString();

    // 获取详细的错误输出
    QString errorOutput = response["errorOutput"].toString();
    QString standardOutput = response["output"].toString();

    qDebug() << "🔑 修改密码响应 - 成功:" << success << "消息:" << message;
    qDebug() << "   错误输出:" << errorOutput;
    qDebug() << "   标准输出:" << standardOutput;

    if (success) {
        switchToPage(2); // 返回主菜单
        showMessage("密码修改成功！");  // 成功时只显示成功消息
    } else {
        // 使用后端返回的具体错误信息
        QString displayMessage = message;  // 直接使用后端返回的消息
        ui->passwordStatusLabel->setText("修改失败: " + displayMessage);
        showMessage(displayMessage, true);  // 显示具体的错误类型
    }
}

void MainWindow::handleGenerateExamResponse(const QJsonObject &response)
{
    totalQuestions = response["totalQuestions"].toInt();
    currentQuestionIndex = 0;

    switchToPage(3); // 考试页面
    loadCurrentQuestion();
    updateExamProgress();
    showMessage("试卷生成成功！");
}

void MainWindow::handleGetCurrentQuestionResponse(const QJsonObject &response)
{
    QJsonObject questionObj = response["question"].toObject();
    QString content = questionObj["content"].toString();
    QJsonArray options = questionObj["options"].toArray();
    int userAnswer = questionObj["userAnswer"].toInt();

    // 更新题目显示
    ui->questionTextEdit->setPlainText(content);

    // 更新选项
    if (options.size() >= 4) {
        ui->optionALabel->setText(options[0].toString());
        ui->optionBLabel->setText(options[1].toString());
        ui->optionCLabel->setText(options[2].toString());
        ui->optionDLabel->setText(options[3].toString());
    }

    // 恢复用户已选择的答案
    answerButtonGroup->blockSignals(true);
    answerButtonGroup->setExclusive(false);
    QAbstractButton* checkedButton = answerButtonGroup->checkedButton();
    if (checkedButton) {
        checkedButton->setChecked(false);
    }
    answerButtonGroup->setExclusive(true);

    if (userAnswer >= 0 && userAnswer < 4) {
        QAbstractButton *button = answerButtonGroup->button(userAnswer);
        if (button) {
            button->setChecked(true);
        }
    }
    answerButtonGroup->blockSignals(false);

    ui->submitAnswerButton->setEnabled(answerButtonGroup->checkedButton() != nullptr);
}

void MainWindow::handleSubmitAnswerResponse(const QJsonObject &response)
{
    showMessage("答案提交成功！");
    ui->submitAnswerButton->setEnabled(false);
}

void MainWindow::handleMoveQuestionResponse(const QJsonObject &response)
{
    loadCurrentQuestion();
    updateExamProgress();
}

void MainWindow::handleSubmitExamResponse(const QJsonObject &response)
{
    QJsonObject result = response["examResult"].toObject();
    displayExamResult(result);
    switchToPage(5); // 考试结果页面
}

void MainWindow::handleSwitchUserTypeResponse(const QJsonObject &response)
{
    // 更新当前用户类型
    QJsonObject userResponse = BackendInterface::instance().callFunction("GetCurrentUser");
    if (userResponse["success"].toBool()) {
        QJsonObject userInfo = userResponse["userInfo"].toObject();
        currentUserType = userInfo["userType"].toString();
        updateUserInfo();
    }
    showMessage("学习阶段切换成功！");
}

// 工具方法
void MainWindow::updateUserInfo()
{
    ui->currentUserLabel->setText("用户名: " + currentUsername);
    ui->currentUserTypeLabel->setText("学习阶段: " + currentUserType);
    ui->welcomeLabel->setText("欢迎, " + currentUsername + "！");
    ui->examTypeComboBox->setCurrentText(currentUserType);
}

void MainWindow::loadCurrentQuestion()
{
    callBackend("GetCurrentQuestion", {});
}

void MainWindow::updateExamProgress()
{
    QJsonObject indexResponse = BackendInterface::instance().callFunction("GetCurrentQuestionIndex");
    if (indexResponse["success"].toBool()) {
        currentQuestionIndex = indexResponse["currentQuestionIndex"].toInt();
    }

    QJsonObject totalResponse = BackendInterface::instance().callFunction("GetTotalQuestions");
    if (totalResponse["success"].toBool()) {
        totalQuestions = totalResponse["totalQuestions"].toInt();
    }

    ui->progressLabel->setText(QString("第 %1 题 / 共 %2 题").arg(currentQuestionIndex + 1).arg(totalQuestions));

    int progress = totalQuestions > 0 ? (currentQuestionIndex + 1) * 100 / totalQuestions : 0;
    ui->progressBar->setValue(progress);

    // 更新按钮状态
    ui->prevQuestionButton->setEnabled(currentQuestionIndex > 0);
    ui->nextQuestionButton->setEnabled(currentQuestionIndex < totalQuestions - 1);
}

void MainWindow::displayExamResult(const QJsonObject &result)
{
    currentExamResult = result;

    ui->totalQuestionsValue->setText(QString::number(result["totalQuestions"].toInt()));
    ui->correctAnswersValue->setText(QString::number(result["correctAnswers"].toInt()));
    ui->scoreValue->setText(QString::number(result["score"].toDouble(), 'f', 1));
    ui->resultUserTypeValue->setText(result["userType"].toString());

    double score = result["score"].toDouble();
    if (score >= 90) {
        ui->congratsLabel->setText("🎉 优秀！成绩非常出色！");
    } else if (score >= 80) {
        ui->congratsLabel->setText("👍 良好！继续努力！");
    } else if (score >= 60) {
        ui->congratsLabel->setText("💪 及格！还有提升空间！");
    } else {
        ui->congratsLabel->setText("📚 加油！多多练习！");
    }
}

void MainWindow::clearExamData()
{
    currentQuestionIndex = 0;
    totalQuestions = 0;
    currentExamResult = QJsonObject();
    answerButtonGroup->setExclusive(false);
    QAbstractButton* checkedButton = answerButtonGroup->checkedButton();
    if (checkedButton) {
        checkedButton->setChecked(false);
    }
    answerButtonGroup->setExclusive(true);
}

bool MainWindow::validateEmail(const QString &email)
{
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex.match(email).hasMatch();
}

bool MainWindow::validatePassword(const QString &password)
{
    if (password.length() < 6 || password.length() > 10) {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (const QChar &ch : password) {
        if (ch.isUpper()) hasUpper = true;
        else if (ch.isLower()) hasLower = true;
        else if (ch.isDigit()) hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}

bool MainWindow::validateRegistrationInput()
{
    QString username = ui->usernameRegEdit->text().trimmed();
    QString email = ui->emailEdit->text().trimmed();
    QString code = ui->codeEdit->text().trimmed();
    QString password = ui->regPasswordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    if (username.isEmpty()) {
        showMessage("请输入用户名", true);
        return false;
    }


    if (!validateEmail(email)) {
        showMessage("请输入有效的邮箱地址", true);
        return false;
    }

    if (code.isEmpty()) {
        showMessage("请输入注册码", true);
        return false;
    }

    if (!validatePassword(password)) {
        showMessage("密码必须为6-10位，包含大小写字母和数字", true);
        return false;
    }

    if (password != confirmPassword) {
        showMessage("两次输入的密码不一致", true);
        return false;
    }
    return true;
}


bool MainWindow::validateChangePasswordInput()
{
    QString oldPassword = ui->oldPasswordEdit->text();
    QString newPassword = ui->newPasswordEdit->text();
    QString confirmPassword = ui->confirmNewPasswordEdit->text();

    if (oldPassword.isEmpty()) {
        showMessage("请输入原密码", true);
        return false;
    }

    if (!validatePassword(newPassword)) {
        showMessage("新密码必须为6-10位，包含大小写字母和数字", true);
        return false;
    }

    if (newPassword != confirmPassword) {
        showMessage("两次输入的新密码不一致", true);
        return false;
    }

    if (oldPassword == newPassword) {
        showMessage("新密码不能与旧密码相同", true);
        return false;
    }

    return true;
}

void MainWindow::callBackend(const QString &function, const QJsonObject &params)
{
    qDebug() << "🔍 调用后端函数:" << function;
    qDebug() << "🔍 请求参数:" << params;

    QJsonObject response = BackendInterface::instance().callFunction(function, params, 5000);

    qDebug() << "🔍 后端响应:" << response;

    if (response.isEmpty()) {
        qDebug() << "后端调用返回空响应";
        showMessage("后端服务无响应，请检查服务状态", true);
        return;
    }

    // 确保在主线程中处理响应
    QMetaObject::invokeMethod(this, "onBackendResponse",
                              Qt::QueuedConnection,
                              Q_ARG(QJsonObject, response));
}
