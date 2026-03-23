#include "mainwindow.h"
#include "backendinterface.h"
#include "../ipc/IPCServer.h"
#include <QApplication>
#include <QMessageBox>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置应用程序信息
    a.setApplicationName("数学考试系统");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("MathExam");

    qDebug() << "启动数学考试系统...";

    // 直接启动 IPC 服务器
    qDebug() << "启动 IPC 服务器...";
    if (!IPCServer::instance().startServer()) {
        qDebug() << "PC服务器启动失败";
        QMessageBox::critical(nullptr, "错误", "IPC服务器启动失败，部分功能可能受限");
    } else {
        qDebug() << "IPC服务器启动成功";
    }

    // 等待服务器启动
    QThread::msleep(500);

    // 初始化后端接口
    qDebug() << "初始化后端接口...";
    if (!BackendInterface::instance().initialize()) {
        qDebug() << "后端接口初始化失败";
        QMessageBox::critical(nullptr, "错误", "后端服务连接失败，请重启应用程序");
    } else {
        qDebug() << "后端接口初始化成功";
    }

    // 创建并显示主窗口
    MainWindow w;
    w.show();

    qDebug() << "数学考试系统启动完成";

    return a.exec();
}
