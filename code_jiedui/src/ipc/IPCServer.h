#ifndef IPCSERVER_H
#define IPCSERVER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QJsonObject>
#include <QDateTime>
#include <sstream>

class BackendCore;

class IPCServer : public QObject
{
    Q_OBJECT

public:
    static IPCServer& instance();
    bool startServer();
    void stopServer();
    void setupOutputRedirection();
    void restoreOutputRedirection();
    void sendOutputMessage(const QString& message, bool isError = false);
    void handleOutput(const QString& message, bool isError = false);

private:
    explicit IPCServer(QObject *parent = nullptr);

    // 原有成员变量
    QLocalServer *server;
    QLocalSocket *currentClient;
    QString serverName;
    BackendCore *backendCore;
    std::streambuf *originalCoutBuf;
    std::streambuf *originalCerrBuf;
    std::stringstream outputBuffer;
    std::stringstream errorBuffer;

    // 原有连接处理函数
    void handleNewConnection();
    void readClientData();
    void clientDisconnected();
    void processRequest(const QJsonObject &request, QLocalSocket *client);
    void sendResponse(QLocalSocket *client, const QJsonObject &response);

    // 原有功能处理函数
    QJsonObject handleLogin(const QJsonObject &params);
    QJsonObject handleRegisterUser(const QJsonObject &params);
    QJsonObject handleCompleteRegistration(const QJsonObject &params);
    QJsonObject handleChangePassword(const QJsonObject &params);
    QJsonObject handleGenerateExam(const QJsonObject &params);
    QJsonObject handleGetCurrentQuestion(const QJsonObject &params);
    QJsonObject handleSubmitAnswer(const QJsonObject &params);
    QJsonObject handleMoveToNextQuestion(const QJsonObject &params);
    QJsonObject handleMoveToPreviousQuestion(const QJsonObject &params);
    QJsonObject handleSubmitExam(const QJsonObject &params);
    QJsonObject handleSwitchUserType(const QJsonObject &params);
    QJsonObject handleGetCurrentUser(const QJsonObject &params);
    QJsonObject handleIsLoggedIn(const QJsonObject &params);
    QJsonObject handleGetTotalQuestions(const QJsonObject &params);
    QJsonObject handleGetCurrentQuestionIndex(const QJsonObject &params);

    // 新增的辅助函数
    void clearOutputBuffers();
    void captureAndAddOutputToResponse(QJsonObject &response);
    void setupErrorResponseFromOutput(QJsonObject &response, bool success);
    QJsonObject buildUserInfoResponse(const QJsonObject &params);
    QJsonObject buildQuestionResponse();
    QJsonObject buildExamResultResponse();
};

#endif // IPCSERVER_H
