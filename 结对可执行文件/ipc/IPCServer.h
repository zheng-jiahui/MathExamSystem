#ifndef IPCSERVER_H
#define IPCSERVER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QJsonObject>
#include <QDateTime>
#include <sstream>  // 添加这行

class BackendCore;

class IPCServer : public QObject
{
    Q_OBJECT

public:
    static IPCServer& instance();

    bool startServer();
    void stopServer();

    // 输出重定向相关方法
    void setupOutputRedirection();
    void restoreOutputRedirection();
    void sendOutputMessage(const QString& message, bool isError = false);
    void handleOutput(const QString& message, bool isError = false);

private:
    explicit IPCServer(QObject *parent = nullptr);

    // 服务器和客户端
    QLocalServer *server;
    QLocalSocket *currentClient;
    QString serverName;

    // 后端核心
    BackendCore *backendCore;

    // 输出重定向相关成员
    std::streambuf *originalCoutBuf;
    std::streambuf *originalCerrBuf;
    std::stringstream outputBuffer;  // 现在可以正常使用了
    std::stringstream errorBuffer;

    // 连接处理
    void handleNewConnection();
    void readClientData();
    void clientDisconnected();

    // 请求处理
    void processRequest(const QJsonObject &request, QLocalSocket *client);
    void sendResponse(QLocalSocket *client, const QJsonObject &response);

    // 具体功能处理函数
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
};

#endif // IPCSERVER_H
