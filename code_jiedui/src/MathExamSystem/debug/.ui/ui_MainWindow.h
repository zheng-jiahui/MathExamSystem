/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer;
    QGroupBox *loginGroupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QLabel *loginStatusLabel;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *registerPage;
    QVBoxLayout *verticalLayout_4;
    QLabel *registerTitleLabel;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *registerGroupBox;
    QVBoxLayout *verticalLayout_5;
    QLabel *emailLabel;
    QHBoxLayout *emailLayout;
    QLineEdit *emailEdit;
    QPushButton *sendCodeButton;
    QLabel *codeLabel;
    QLineEdit *codeEdit;
    QLabel *regPasswordLabel;
    QLineEdit *regPasswordEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordEdit;
    QLabel *userTypeLabel;
    QComboBox *userTypeComboBox;
    QLabel *registerStatusLabel;
    QPushButton *completeRegisterButton;
    QPushButton *backToLoginButton;
    QSpacerItem *verticalSpacer_4;
    QWidget *mainMenuPage;
    QVBoxLayout *verticalLayout_6;
    QLabel *welcomeLabel;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *userInfoGroupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *currentUserLabel;
    QLabel *currentUserTypeLabel;
    QSpacerItem *horizontalSpacer;
    QGroupBox *examGroupBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *examSettingsLayout;
    QLabel *examTypeLabel;
    QComboBox *examTypeComboBox;
    QLabel *questionCountLabel;
    QSpinBox *questionCountSpinBox;
    QPushButton *generateExamButton;
    QGroupBox *accountGroupBox;
    QVBoxLayout *verticalLayout_8;
    QPushButton *changePasswordButton;
    QPushButton *switchUserTypeButton;
    QPushButton *logoutButton;
    QSpacerItem *verticalSpacer_6;
    QWidget *examPage;
    QVBoxLayout *verticalLayout_9;
    QLabel *examTitleLabel;
    QLabel *progressLabel;
    QProgressBar *progressBar;
    QGroupBox *questionGroupBox;
    QVBoxLayout *verticalLayout_10;
    QTextEdit *questionTextEdit;
    QGroupBox *optionsGroupBox;
    QGridLayout *gridLayout;
    QRadioButton *optionARadio;
    QLabel *optionALabel;
    QRadioButton *optionBRadio;
    QLabel *optionBLabel;
    QRadioButton *optionCRadio;
    QLabel *optionCLabel;
    QRadioButton *optionDRadio;
    QLabel *optionDLabel;
    QHBoxLayout *examButtonsLayout;
    QPushButton *prevQuestionButton;
    QPushButton *submitAnswerButton;
    QPushButton *nextQuestionButton;
    QPushButton *submitExamButton;
    QSpacerItem *verticalSpacer_7;
    QWidget *changePasswordPage;
    QVBoxLayout *verticalLayout_11;
    QLabel *changePasswordTitleLabel;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *passwordGroupBox;
    QVBoxLayout *verticalLayout_12;
    QLabel *oldPasswordLabel;
    QLineEdit *oldPasswordEdit;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordEdit;
    QLabel *confirmNewPasswordLabel;
    QLineEdit *confirmNewPasswordEdit;
    QLabel *passwordStatusLabel;
    QPushButton *confirmChangePasswordButton;
    QPushButton *backToMainFromPasswordButton;
    QSpacerItem *verticalSpacer_9;
    QWidget *resultPage;
    QVBoxLayout *verticalLayout_13;
    QLabel *resultTitleLabel;
    QSpacerItem *verticalSpacer_10;
    QGroupBox *resultGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *totalQuestionsLabel;
    QLabel *totalQuestionsValue;
    QLabel *correctAnswersLabel;
    QLabel *correctAnswersValue;
    QLabel *scoreLabel;
    QLabel *scoreValue;
    QLabel *resultUserTypeLabel;
    QLabel *resultUserTypeValue;
    QLabel *congratsLabel;
    QHBoxLayout *resultButtonsLayout;
    QPushButton *viewDetailsButton;
    QPushButton *newExamButton;
    QPushButton *backToMenuButton;
    QSpacerItem *verticalSpacer_11;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 700);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                                stop:0 #667eea, stop:1 #764ba2);\n"
"    font-family: \"Microsoft YaHei\", \"Segoe UI\", sans-serif;\n"
"}\n"
"\n"
"QWidget {\n"
"    background: transparent;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    background: rgba(255, 255, 255, 0.95);\n"
"    border: 2px solid #ddd;\n"
"    border-radius: 15px;\n"
"    margin-top: 10px;\n"
"    padding-top: 15px;\n"
"    font-weight: bold;\n"
"    color: #333;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    padding: 0 10px 0 10px;\n"
"    color: #2c3e50;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel {\n"
"    background: transparent;\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 28px;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLineEdit, QComboBox, QSpinBox {\n"
"    background: white;\n"
""
                        "    border: 2px solid #bdc3c7;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    selection-background-color: #3498db;\n"
"}\n"
"\n"
"QLineEdit:focus, QComboBox:focus, QSpinBox:focus {\n"
"    border-color: #3498db;\n"
"    background: #f8f9fa;\n"
"}\n"
"\n"
"QTextEdit {\n"
"    background: white;\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QTextEdit:focus {\n"
"    border-color: #3498db;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #3498db, stop:1 #2980b9);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"    padding: 12px 24px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    min-width: 120px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2980b9, stop:1 #2471a3);\n"
"}\n"
"\n"
"QPu"
                        "shButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2471a3, stop:1 #1c5a85);\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background: #bdc3c7;\n"
"    color: #7f8c8d;\n"
"}\n"
"\n"
"QPushButton.danger {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #e74c3c, stop:1 #c0392b);\n"
"}\n"
"\n"
"QPushButton.danger:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #c0392b, stop:1 #a93226);\n"
"}\n"
"\n"
"QPushButton.success {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2ecc71, stop:1 #27ae60);\n"
"}\n"
"\n"
"QPushButton.success:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #27ae60, stop:1 #229954);\n"
"}\n"
"\n"
"QRadioButton {\n"
"    background: transparent;\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
""
                        "    font-weight: bold;\n"
"    spacing: 8px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    border-radius: 9px;\n"
"    border: 2px solid #bdc3c7;\n"
"    background: white;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background: #3498db;\n"
"    border: 2px solid #3498db;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:hover {\n"
"    background: #2980b9;\n"
"    border: 2px solid #2980b9;\n"
"}\n"
"\n"
"QProgressBar {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 8px;\n"
"    background: white;\n"
"    text-align: center;\n"
"    color: #2c3e50;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #3498db, stop:1 #2ecc71);\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QStackedWidget {\n"
"    background: transparent;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        titleLabel = new QLabel(loginPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(titleLabel);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        loginGroupBox = new QGroupBox(loginPage);
        loginGroupBox->setObjectName(QString::fromUtf8("loginGroupBox"));
        verticalLayout_3 = new QVBoxLayout(loginGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        usernameLabel = new QLabel(loginGroupBox);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));

        verticalLayout_3->addWidget(usernameLabel);

        usernameEdit = new QLineEdit(loginGroupBox);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));

        verticalLayout_3->addWidget(usernameEdit);

        passwordLabel = new QLabel(loginGroupBox);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        verticalLayout_3->addWidget(passwordLabel);

        passwordEdit = new QLineEdit(loginGroupBox);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(passwordEdit);

        loginStatusLabel = new QLabel(loginGroupBox);
        loginStatusLabel->setObjectName(QString::fromUtf8("loginStatusLabel"));
        loginStatusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(loginStatusLabel);

        loginButton = new QPushButton(loginGroupBox);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        verticalLayout_3->addWidget(loginButton);

        registerButton = new QPushButton(loginGroupBox);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    color: #3498db;\n"
"    border: 1px solid #3498db;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: rgba(52, 152, 219, 0.1);\n"
"    color: #2980b9;\n"
"    border-color: #2980b9;\n"
"}"));

        verticalLayout_3->addWidget(registerButton);


        verticalLayout_2->addWidget(loginGroupBox);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        stackedWidget->addWidget(loginPage);
        registerPage = new QWidget();
        registerPage->setObjectName(QString::fromUtf8("registerPage"));
        verticalLayout_4 = new QVBoxLayout(registerPage);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        registerTitleLabel = new QLabel(registerPage);
        registerTitleLabel->setObjectName(QString::fromUtf8("registerTitleLabel"));
        registerTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(registerTitleLabel);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        registerGroupBox = new QGroupBox(registerPage);
        registerGroupBox->setObjectName(QString::fromUtf8("registerGroupBox"));
        verticalLayout_5 = new QVBoxLayout(registerGroupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        emailLabel = new QLabel(registerGroupBox);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));

        verticalLayout_5->addWidget(emailLabel);

        emailLayout = new QHBoxLayout();
        emailLayout->setObjectName(QString::fromUtf8("emailLayout"));
        emailEdit = new QLineEdit(registerGroupBox);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));

        emailLayout->addWidget(emailEdit);

        sendCodeButton = new QPushButton(registerGroupBox);
        sendCodeButton->setObjectName(QString::fromUtf8("sendCodeButton"));

        emailLayout->addWidget(sendCodeButton);


        verticalLayout_5->addLayout(emailLayout);

        codeLabel = new QLabel(registerGroupBox);
        codeLabel->setObjectName(QString::fromUtf8("codeLabel"));

        verticalLayout_5->addWidget(codeLabel);

        codeEdit = new QLineEdit(registerGroupBox);
        codeEdit->setObjectName(QString::fromUtf8("codeEdit"));

        verticalLayout_5->addWidget(codeEdit);

        regPasswordLabel = new QLabel(registerGroupBox);
        regPasswordLabel->setObjectName(QString::fromUtf8("regPasswordLabel"));

        verticalLayout_5->addWidget(regPasswordLabel);

        regPasswordEdit = new QLineEdit(registerGroupBox);
        regPasswordEdit->setObjectName(QString::fromUtf8("regPasswordEdit"));
        regPasswordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_5->addWidget(regPasswordEdit);

        confirmPasswordLabel = new QLabel(registerGroupBox);
        confirmPasswordLabel->setObjectName(QString::fromUtf8("confirmPasswordLabel"));

        verticalLayout_5->addWidget(confirmPasswordLabel);

        confirmPasswordEdit = new QLineEdit(registerGroupBox);
        confirmPasswordEdit->setObjectName(QString::fromUtf8("confirmPasswordEdit"));
        confirmPasswordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_5->addWidget(confirmPasswordEdit);

        userTypeLabel = new QLabel(registerGroupBox);
        userTypeLabel->setObjectName(QString::fromUtf8("userTypeLabel"));

        verticalLayout_5->addWidget(userTypeLabel);

        userTypeComboBox = new QComboBox(registerGroupBox);
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->setObjectName(QString::fromUtf8("userTypeComboBox"));

        verticalLayout_5->addWidget(userTypeComboBox);

        registerStatusLabel = new QLabel(registerGroupBox);
        registerStatusLabel->setObjectName(QString::fromUtf8("registerStatusLabel"));
        registerStatusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(registerStatusLabel);

        completeRegisterButton = new QPushButton(registerGroupBox);
        completeRegisterButton->setObjectName(QString::fromUtf8("completeRegisterButton"));
        completeRegisterButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2ecc71, stop:1 #27ae60);\n"
"}"));

        verticalLayout_5->addWidget(completeRegisterButton);

        backToLoginButton = new QPushButton(registerGroupBox);
        backToLoginButton->setObjectName(QString::fromUtf8("backToLoginButton"));
        backToLoginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    color: #e74c3c;\n"
"    border: 1px solid #e74c3c;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: rgba(231, 76, 60, 0.1);\n"
"}"));

        verticalLayout_5->addWidget(backToLoginButton);


        verticalLayout_4->addWidget(registerGroupBox);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        stackedWidget->addWidget(registerPage);
        mainMenuPage = new QWidget();
        mainMenuPage->setObjectName(QString::fromUtf8("mainMenuPage"));
        verticalLayout_6 = new QVBoxLayout(mainMenuPage);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        welcomeLabel = new QLabel(mainMenuPage);
        welcomeLabel->setObjectName(QString::fromUtf8("welcomeLabel"));
        welcomeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(welcomeLabel);

        verticalSpacer_5 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_5);

        userInfoGroupBox = new QGroupBox(mainMenuPage);
        userInfoGroupBox->setObjectName(QString::fromUtf8("userInfoGroupBox"));
        horizontalLayout = new QHBoxLayout(userInfoGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        currentUserLabel = new QLabel(userInfoGroupBox);
        currentUserLabel->setObjectName(QString::fromUtf8("currentUserLabel"));

        horizontalLayout->addWidget(currentUserLabel);

        currentUserTypeLabel = new QLabel(userInfoGroupBox);
        currentUserTypeLabel->setObjectName(QString::fromUtf8("currentUserTypeLabel"));

        horizontalLayout->addWidget(currentUserTypeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_6->addWidget(userInfoGroupBox);

        examGroupBox = new QGroupBox(mainMenuPage);
        examGroupBox->setObjectName(QString::fromUtf8("examGroupBox"));
        verticalLayout_7 = new QVBoxLayout(examGroupBox);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        examSettingsLayout = new QHBoxLayout();
        examSettingsLayout->setObjectName(QString::fromUtf8("examSettingsLayout"));
        examTypeLabel = new QLabel(examGroupBox);
        examTypeLabel->setObjectName(QString::fromUtf8("examTypeLabel"));

        examSettingsLayout->addWidget(examTypeLabel);

        examTypeComboBox = new QComboBox(examGroupBox);
        examTypeComboBox->addItem(QString());
        examTypeComboBox->addItem(QString());
        examTypeComboBox->addItem(QString());
        examTypeComboBox->setObjectName(QString::fromUtf8("examTypeComboBox"));

        examSettingsLayout->addWidget(examTypeComboBox);

        questionCountLabel = new QLabel(examGroupBox);
        questionCountLabel->setObjectName(QString::fromUtf8("questionCountLabel"));

        examSettingsLayout->addWidget(questionCountLabel);

        questionCountSpinBox = new QSpinBox(examGroupBox);
        questionCountSpinBox->setObjectName(QString::fromUtf8("questionCountSpinBox"));
        questionCountSpinBox->setMinimum(10);
        questionCountSpinBox->setMaximum(30);
        questionCountSpinBox->setValue(10);

        examSettingsLayout->addWidget(questionCountSpinBox);


        verticalLayout_7->addLayout(examSettingsLayout);

        generateExamButton = new QPushButton(examGroupBox);
        generateExamButton->setObjectName(QString::fromUtf8("generateExamButton"));
        generateExamButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #9b59b6, stop:1 #8e44ad);\n"
"    font-size: 16px;\n"
"    padding: 15px 30px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #8e44ad, stop:1 #7d3c98);\n"
"}"));

        verticalLayout_7->addWidget(generateExamButton);


        verticalLayout_6->addWidget(examGroupBox);

        accountGroupBox = new QGroupBox(mainMenuPage);
        accountGroupBox->setObjectName(QString::fromUtf8("accountGroupBox"));
        verticalLayout_8 = new QVBoxLayout(accountGroupBox);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        changePasswordButton = new QPushButton(accountGroupBox);
        changePasswordButton->setObjectName(QString::fromUtf8("changePasswordButton"));

        verticalLayout_8->addWidget(changePasswordButton);

        switchUserTypeButton = new QPushButton(accountGroupBox);
        switchUserTypeButton->setObjectName(QString::fromUtf8("switchUserTypeButton"));

        verticalLayout_8->addWidget(switchUserTypeButton);

        logoutButton = new QPushButton(accountGroupBox);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));
        logoutButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #e74c3c, stop:1 #c0392b);\n"
"}"));

        verticalLayout_8->addWidget(logoutButton);


        verticalLayout_6->addWidget(accountGroupBox);

        verticalSpacer_6 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_6);

        stackedWidget->addWidget(mainMenuPage);
        examPage = new QWidget();
        examPage->setObjectName(QString::fromUtf8("examPage"));
        verticalLayout_9 = new QVBoxLayout(examPage);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        examTitleLabel = new QLabel(examPage);
        examTitleLabel->setObjectName(QString::fromUtf8("examTitleLabel"));
        examTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(examTitleLabel);

        progressLabel = new QLabel(examPage);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));
        progressLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(progressLabel);

        progressBar = new QProgressBar(examPage);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout_9->addWidget(progressBar);

        questionGroupBox = new QGroupBox(examPage);
        questionGroupBox->setObjectName(QString::fromUtf8("questionGroupBox"));
        verticalLayout_10 = new QVBoxLayout(questionGroupBox);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        questionTextEdit = new QTextEdit(questionGroupBox);
        questionTextEdit->setObjectName(QString::fromUtf8("questionTextEdit"));
        questionTextEdit->setReadOnly(true);

        verticalLayout_10->addWidget(questionTextEdit);


        verticalLayout_9->addWidget(questionGroupBox);

        optionsGroupBox = new QGroupBox(examPage);
        optionsGroupBox->setObjectName(QString::fromUtf8("optionsGroupBox"));
        gridLayout = new QGridLayout(optionsGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        optionARadio = new QRadioButton(optionsGroupBox);
        optionARadio->setObjectName(QString::fromUtf8("optionARadio"));

        gridLayout->addWidget(optionARadio, 0, 0, 1, 1);

        optionALabel = new QLabel(optionsGroupBox);
        optionALabel->setObjectName(QString::fromUtf8("optionALabel"));

        gridLayout->addWidget(optionALabel, 0, 1, 1, 1);

        optionBRadio = new QRadioButton(optionsGroupBox);
        optionBRadio->setObjectName(QString::fromUtf8("optionBRadio"));

        gridLayout->addWidget(optionBRadio, 1, 0, 1, 1);

        optionBLabel = new QLabel(optionsGroupBox);
        optionBLabel->setObjectName(QString::fromUtf8("optionBLabel"));

        gridLayout->addWidget(optionBLabel, 1, 1, 1, 1);

        optionCRadio = new QRadioButton(optionsGroupBox);
        optionCRadio->setObjectName(QString::fromUtf8("optionCRadio"));

        gridLayout->addWidget(optionCRadio, 2, 0, 1, 1);

        optionCLabel = new QLabel(optionsGroupBox);
        optionCLabel->setObjectName(QString::fromUtf8("optionCLabel"));

        gridLayout->addWidget(optionCLabel, 2, 1, 1, 1);

        optionDRadio = new QRadioButton(optionsGroupBox);
        optionDRadio->setObjectName(QString::fromUtf8("optionDRadio"));

        gridLayout->addWidget(optionDRadio, 3, 0, 1, 1);

        optionDLabel = new QLabel(optionsGroupBox);
        optionDLabel->setObjectName(QString::fromUtf8("optionDLabel"));

        gridLayout->addWidget(optionDLabel, 3, 1, 1, 1);


        verticalLayout_9->addWidget(optionsGroupBox);

        examButtonsLayout = new QHBoxLayout();
        examButtonsLayout->setObjectName(QString::fromUtf8("examButtonsLayout"));
        prevQuestionButton = new QPushButton(examPage);
        prevQuestionButton->setObjectName(QString::fromUtf8("prevQuestionButton"));

        examButtonsLayout->addWidget(prevQuestionButton);

        submitAnswerButton = new QPushButton(examPage);
        submitAnswerButton->setObjectName(QString::fromUtf8("submitAnswerButton"));
        submitAnswerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2ecc71, stop:1 #27ae60);\n"
"}"));

        examButtonsLayout->addWidget(submitAnswerButton);

        nextQuestionButton = new QPushButton(examPage);
        nextQuestionButton->setObjectName(QString::fromUtf8("nextQuestionButton"));

        examButtonsLayout->addWidget(nextQuestionButton);

        submitExamButton = new QPushButton(examPage);
        submitExamButton->setObjectName(QString::fromUtf8("submitExamButton"));
        submitExamButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #e67e22, stop:1 #d35400);\n"
"    font-size: 16px;\n"
"    padding: 12px 30px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #d35400, stop:1 #ba4a00);\n"
"}"));

        examButtonsLayout->addWidget(submitExamButton);


        verticalLayout_9->addLayout(examButtonsLayout);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_7);

        stackedWidget->addWidget(examPage);
        changePasswordPage = new QWidget();
        changePasswordPage->setObjectName(QString::fromUtf8("changePasswordPage"));
        verticalLayout_11 = new QVBoxLayout(changePasswordPage);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        changePasswordTitleLabel = new QLabel(changePasswordPage);
        changePasswordTitleLabel->setObjectName(QString::fromUtf8("changePasswordTitleLabel"));
        changePasswordTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(changePasswordTitleLabel);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_8);

        passwordGroupBox = new QGroupBox(changePasswordPage);
        passwordGroupBox->setObjectName(QString::fromUtf8("passwordGroupBox"));
        verticalLayout_12 = new QVBoxLayout(passwordGroupBox);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        oldPasswordLabel = new QLabel(passwordGroupBox);
        oldPasswordLabel->setObjectName(QString::fromUtf8("oldPasswordLabel"));

        verticalLayout_12->addWidget(oldPasswordLabel);

        oldPasswordEdit = new QLineEdit(passwordGroupBox);
        oldPasswordEdit->setObjectName(QString::fromUtf8("oldPasswordEdit"));
        oldPasswordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_12->addWidget(oldPasswordEdit);

        newPasswordLabel = new QLabel(passwordGroupBox);
        newPasswordLabel->setObjectName(QString::fromUtf8("newPasswordLabel"));

        verticalLayout_12->addWidget(newPasswordLabel);

        newPasswordEdit = new QLineEdit(passwordGroupBox);
        newPasswordEdit->setObjectName(QString::fromUtf8("newPasswordEdit"));
        newPasswordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_12->addWidget(newPasswordEdit);

        confirmNewPasswordLabel = new QLabel(passwordGroupBox);
        confirmNewPasswordLabel->setObjectName(QString::fromUtf8("confirmNewPasswordLabel"));

        verticalLayout_12->addWidget(confirmNewPasswordLabel);

        confirmNewPasswordEdit = new QLineEdit(passwordGroupBox);
        confirmNewPasswordEdit->setObjectName(QString::fromUtf8("confirmNewPasswordEdit"));
        confirmNewPasswordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_12->addWidget(confirmNewPasswordEdit);

        passwordStatusLabel = new QLabel(passwordGroupBox);
        passwordStatusLabel->setObjectName(QString::fromUtf8("passwordStatusLabel"));
        passwordStatusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(passwordStatusLabel);

        confirmChangePasswordButton = new QPushButton(passwordGroupBox);
        confirmChangePasswordButton->setObjectName(QString::fromUtf8("confirmChangePasswordButton"));
        confirmChangePasswordButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2ecc71, stop:1 #27ae60);\n"
"}"));

        verticalLayout_12->addWidget(confirmChangePasswordButton);

        backToMainFromPasswordButton = new QPushButton(passwordGroupBox);
        backToMainFromPasswordButton->setObjectName(QString::fromUtf8("backToMainFromPasswordButton"));
        backToMainFromPasswordButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    color: #e74c3c;\n"
"    border: 1px solid #e74c3c;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: rgba(231, 76, 60, 0.1);\n"
"}"));

        verticalLayout_12->addWidget(backToMainFromPasswordButton);


        verticalLayout_11->addWidget(passwordGroupBox);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_9);

        stackedWidget->addWidget(changePasswordPage);
        resultPage = new QWidget();
        resultPage->setObjectName(QString::fromUtf8("resultPage"));
        verticalLayout_13 = new QVBoxLayout(resultPage);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        resultTitleLabel = new QLabel(resultPage);
        resultTitleLabel->setObjectName(QString::fromUtf8("resultTitleLabel"));
        resultTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(resultTitleLabel);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_10);

        resultGroupBox = new QGroupBox(resultPage);
        resultGroupBox->setObjectName(QString::fromUtf8("resultGroupBox"));
        gridLayout_2 = new QGridLayout(resultGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        totalQuestionsLabel = new QLabel(resultGroupBox);
        totalQuestionsLabel->setObjectName(QString::fromUtf8("totalQuestionsLabel"));

        gridLayout_2->addWidget(totalQuestionsLabel, 0, 0, 1, 1);

        totalQuestionsValue = new QLabel(resultGroupBox);
        totalQuestionsValue->setObjectName(QString::fromUtf8("totalQuestionsValue"));

        gridLayout_2->addWidget(totalQuestionsValue, 0, 1, 1, 1);

        correctAnswersLabel = new QLabel(resultGroupBox);
        correctAnswersLabel->setObjectName(QString::fromUtf8("correctAnswersLabel"));

        gridLayout_2->addWidget(correctAnswersLabel, 1, 0, 1, 1);

        correctAnswersValue = new QLabel(resultGroupBox);
        correctAnswersValue->setObjectName(QString::fromUtf8("correctAnswersValue"));

        gridLayout_2->addWidget(correctAnswersValue, 1, 1, 1, 1);

        scoreLabel = new QLabel(resultGroupBox);
        scoreLabel->setObjectName(QString::fromUtf8("scoreLabel"));

        gridLayout_2->addWidget(scoreLabel, 2, 0, 1, 1);

        scoreValue = new QLabel(resultGroupBox);
        scoreValue->setObjectName(QString::fromUtf8("scoreValue"));

        gridLayout_2->addWidget(scoreValue, 2, 1, 1, 1);

        resultUserTypeLabel = new QLabel(resultGroupBox);
        resultUserTypeLabel->setObjectName(QString::fromUtf8("resultUserTypeLabel"));

        gridLayout_2->addWidget(resultUserTypeLabel, 3, 0, 1, 1);

        resultUserTypeValue = new QLabel(resultGroupBox);
        resultUserTypeValue->setObjectName(QString::fromUtf8("resultUserTypeValue"));

        gridLayout_2->addWidget(resultUserTypeValue, 3, 1, 1, 1);


        verticalLayout_13->addWidget(resultGroupBox);

        congratsLabel = new QLabel(resultPage);
        congratsLabel->setObjectName(QString::fromUtf8("congratsLabel"));
        congratsLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(congratsLabel);

        resultButtonsLayout = new QHBoxLayout();
        resultButtonsLayout->setObjectName(QString::fromUtf8("resultButtonsLayout"));
        viewDetailsButton = new QPushButton(resultPage);
        viewDetailsButton->setObjectName(QString::fromUtf8("viewDetailsButton"));

        resultButtonsLayout->addWidget(viewDetailsButton);

        newExamButton = new QPushButton(resultPage);
        newExamButton->setObjectName(QString::fromUtf8("newExamButton"));
        newExamButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #2ecc71, stop:1 #27ae60);\n"
"}"));

        resultButtonsLayout->addWidget(newExamButton);

        backToMenuButton = new QPushButton(resultPage);
        backToMenuButton->setObjectName(QString::fromUtf8("backToMenuButton"));

        resultButtonsLayout->addWidget(backToMenuButton);


        verticalLayout_13->addLayout(resultButtonsLayout);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_11);

        stackedWidget->addWidget(resultPage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\225\260\345\255\246\350\200\203\350\257\225\347\263\273\347\273\237", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\346\225\260\345\255\246\350\200\203\350\257\225\347\263\273\347\273\237", nullptr));
        loginGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        usernameLabel->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215:", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        passwordLabel->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201:", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        loginStatusLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\267\347\231\273\345\275\225\344\273\245\345\274\200\345\247\213\344\275\277\347\224\250", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "\346\262\241\346\234\211\350\264\246\345\217\267\357\274\237\347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
        registerTitleLabel->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
        registerGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214\344\277\241\346\201\257", nullptr));
        emailLabel->setText(QCoreApplication::translate("MainWindow", "\351\202\256\347\256\261\345\234\260\345\235\200:", nullptr));
        emailEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\234\211\346\225\210\347\232\204\351\202\256\347\256\261\345\234\260\345\235\200", nullptr));
        sendCodeButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\263\250\345\206\214\347\240\201", nullptr));
        codeLabel->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214\347\240\201:", nullptr));
        codeEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\224\266\345\210\260\347\232\204\346\263\250\345\206\214\347\240\201", nullptr));
        regPasswordLabel->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201 (6-10\344\275\215\357\274\214\345\220\253\345\244\247\345\260\217\345\206\231\345\255\227\346\257\215\345\222\214\346\225\260\345\255\227):", nullptr));
        regPasswordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\347\231\273\345\275\225\345\257\206\347\240\201", nullptr));
        confirmPasswordLabel->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244\345\257\206\347\240\201:", nullptr));
        confirmPasswordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        userTypeLabel->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240\351\230\266\346\256\265:", nullptr));
        userTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\345\260\217\345\255\246", nullptr));
        userTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\345\210\235\344\270\255", nullptr));
        userTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\351\253\230\344\270\255", nullptr));

        registerStatusLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\267\345\241\253\345\206\231\345\256\214\346\225\264\347\232\204\346\263\250\345\206\214\344\277\241\346\201\257", nullptr));
        completeRegisterButton->setText(QCoreApplication::translate("MainWindow", "\345\256\214\346\210\220\346\263\250\345\206\214", nullptr));
        backToLoginButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\346\225\260\345\255\246\350\200\203\350\257\225\347\263\273\347\273\237", nullptr));
        userInfoGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        currentUserLabel->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215: \346\234\252\347\231\273\345\275\225", nullptr));
        currentUserTypeLabel->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240\351\230\266\346\256\265: \346\234\252\351\200\211\346\213\251", nullptr));
        examGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\200\203\350\257\225\345\212\237\350\203\275", nullptr));
        examTypeLabel->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240\351\230\266\346\256\265:", nullptr));
        examTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\345\260\217\345\255\246", nullptr));
        examTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\345\210\235\344\270\255", nullptr));
        examTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\351\253\230\344\270\255", nullptr));

        questionCountLabel->setText(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256\346\225\260\351\207\217:", nullptr));
        generateExamButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\350\200\203\350\257\225", nullptr));
        accountGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\264\246\346\210\267\347\256\241\347\220\206", nullptr));
        changePasswordButton->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        switchUserTypeButton->setText(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\345\255\246\344\271\240\351\230\266\346\256\265", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        examTitleLabel->setText(QCoreApplication::translate("MainWindow", "\345\234\250\347\272\277\350\200\203\350\257\225", nullptr));
        progressLabel->setText(QCoreApplication::translate("MainWindow", "\347\254\254 1 \351\242\230 / \345\205\261 10 \351\242\230", nullptr));
        questionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256", nullptr));
        questionTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\267\347\255\211\345\276\205\351\242\230\347\233\256\345\212\240\350\275\275...</p></body></html>", nullptr));
        optionsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\347\255\224\346\241\210", nullptr));
        optionARadio->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        optionALabel->setText(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271A\345\206\205\345\256\271", nullptr));
        optionBRadio->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        optionBLabel->setText(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271B\345\206\205\345\256\271", nullptr));
        optionCRadio->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        optionCLabel->setText(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271C\345\206\205\345\256\271", nullptr));
        optionDRadio->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        optionDLabel->setText(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271D\345\206\205\345\256\271", nullptr));
        prevQuestionButton->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\351\242\230", nullptr));
        submitAnswerButton->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244\347\255\224\346\241\210", nullptr));
        nextQuestionButton->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\242\230", nullptr));
        submitExamButton->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244\350\257\225\345\215\267", nullptr));
        changePasswordTitleLabel->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        passwordGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\344\277\256\346\224\271", nullptr));
        oldPasswordLabel->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\257\206\347\240\201:", nullptr));
        oldPasswordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\216\237\345\257\206\347\240\201", nullptr));
        newPasswordLabel->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\257\206\347\240\201 (6-10\344\275\215\357\274\214\345\220\253\345\244\247\345\260\217\345\206\231\345\255\227\346\257\215\345\222\214\346\225\260\345\255\227):", nullptr));
        newPasswordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\226\260\345\257\206\347\240\201", nullptr));
        confirmNewPasswordLabel->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244\346\226\260\345\257\206\347\240\201:", nullptr));
        confirmNewPasswordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\345\206\215\346\254\241\350\276\223\345\205\245\346\226\260\345\257\206\347\240\201", nullptr));
        passwordStatusLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\267\345\241\253\345\206\231\345\257\206\347\240\201\344\277\241\346\201\257", nullptr));
        confirmChangePasswordButton->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244\344\277\256\346\224\271", nullptr));
        backToMainFromPasswordButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
        resultTitleLabel->setText(QCoreApplication::translate("MainWindow", "\350\200\203\350\257\225\347\273\223\346\236\234", nullptr));
        resultGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\210\220\347\273\251\347\273\237\350\256\241", nullptr));
        totalQuestionsLabel->setText(QCoreApplication::translate("MainWindow", "\346\200\273\351\242\230\346\225\260:", nullptr));
        totalQuestionsValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        correctAnswersLabel->setText(QCoreApplication::translate("MainWindow", "\346\255\243\347\241\256\351\242\230\346\225\260:", nullptr));
        correctAnswersValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        scoreLabel->setText(QCoreApplication::translate("MainWindow", "\345\276\227\345\210\206:", nullptr));
        scoreValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        resultUserTypeLabel->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240\351\230\266\346\256\265:", nullptr));
        resultUserTypeValue->setText(QCoreApplication::translate("MainWindow", "\345\260\217\345\255\246", nullptr));
        congratsLabel->setText(QCoreApplication::translate("MainWindow", "\346\201\255\345\226\234\345\256\214\346\210\220\350\200\203\350\257\225\357\274\201", nullptr));
        viewDetailsButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\257\246\346\203\205", nullptr));
        newExamButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260\347\232\204\350\200\203\350\257\225", nullptr));
        backToMenuButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
