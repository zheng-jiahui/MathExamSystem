#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include <QButtonGroup>
#include <QJsonObject>
#include <QJsonArray>
#include "backendinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 登录页面
    void onLoginClicked();
    void onRegisterClicked();

    // 注册页面
    void onSendCodeClicked();
    void onCompleteRegisterClicked();
    void onBackToLoginClicked();

    // 主菜单页面
    void onGenerateExamClicked();
    void onChangePasswordClicked();
    void onSwitchUserTypeClicked();
    void onLogoutClicked();

    // 考试页面
    void onAnswerSelected();
    void onSubmitAnswerClicked();
    void onNextQuestionClicked();
    void onPreviousQuestionClicked();
    void onSubmitExamClicked();

    // 修改密码页面
    void onConfirmChangePasswordClicked();
    void onBackToMainClicked();

    // 考试结果页面
    void onNewExamClicked();
    void onBackToMenuClicked();
    void onViewDetailsClicked();
    bool validateRegistrationInput();

    // 后端通信响应 - 确保每个函数只声明一次
    void onBackendResponse(const QJsonObject &response);
    void onBackendError(const QString &error);

private:
    Ui::MainWindow *ui;
    QButtonGroup *answerButtonGroup;
    QString currentUsername;
    QString currentUserType;
    int currentQuestionIndex;
    int totalQuestions;
    QJsonObject currentExamResult;

    void initializeUI();
    void setupConnections();
    void switchToPage(int pageIndex);
    void showMessage(const QString &message, bool isError = false);

    // 页面更新方法
    void updateUserInfo();
    void loadCurrentQuestion();
    void updateExamProgress();
    void displayExamResult(const QJsonObject &result);
    void clearExamData();

    // 验证方法
    bool validateEmail(const QString &email);
    bool validatePassword(const QString &password);
    bool validateChangePasswordInput();

    // 后端调用方法 - 确保每个函数只声明一次
    void callBackend(const QString &function, const QJsonObject &params = QJsonObject());

    // 响应处理函数 - 确保每个函数只声明一次
    void handleLoginResponse(const QJsonObject &response);
    void handleRegisterUserResponse(const QJsonObject &response);
    void handleCompleteRegistrationResponse(const QJsonObject &response);
    void handleChangePasswordResponse(const QJsonObject &response);
    void handleGenerateExamResponse(const QJsonObject &response);
    void handleGetCurrentQuestionResponse(const QJsonObject &response);
    void handleSubmitAnswerResponse(const QJsonObject &response);
    void handleMoveQuestionResponse(const QJsonObject &response);
    void handleSubmitExamResponse(const QJsonObject &response);
    void handleSwitchUserTypeResponse(const QJsonObject &response);
};

#endif // MAINWINDOW_H
