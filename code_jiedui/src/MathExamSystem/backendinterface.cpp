#include "backendinterface.h"
#include <QDebug>
#include <QLocalServer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>
#include <QEventLoop>
#include <QProcess>  // 添加这行
#include <QCoreApplication>  // 添加这行
#include <QThread>  // 添加这行

//这个文件实现了一个前端与后端服务的通信桥梁
//建立连接：通过本地Socket连接到后端服务
//消息传递：在前端和后端之间传输数据
//连接维护：管理连接状态，处理断开和重连

//使用Meyers' Singleton模式确保线程安全,整个应用程序中只有一个BackendInterface实例
//提供统一的访问入口,确保了BackendInterface作为一个全局的、唯一的通信管理器，为整个应用程序提供统一的后端服务访问入口。
BackendInterface& BackendInterface::instance()
{
    static BackendInterface instance;
    return instance;
}

//继承自QObject，支持Qt的信号槽机制
//初始化socket为nullptr
//设置服务器名称为"MathExamSystem_Server"
BackendInterface::BackendInterface(QObject *parent)
    : QObject(parent), socket(nullptr)
{
    serverName = "MathExamSystem_Server";
}
//socket本地进程间通信：用于前端GUI和后端服务之间的数据交换
//发送请求和接收响应,维护与后端服务的连接状态

//serverName是后端进程在系统中注册的唯一名称,前端通过这个名称找到并连接到后端服务

//单例模式：确保整个应用程序中只有一个 BackendInterface 实例
//全局访问：任何地方都可以通过 BackendInterface::instance() 访问同一个后端接口
//前端和后端是两个独立的进程，通过本地socket进行通信
bool BackendInterface::initialize()
{
    //如果已经连接，直接返回成功
    if (socket && socket->state() == QLocalSocket::ConnectedState) {
        return true;
    }

    if (!socket) {
        //创建QLocalSocket：用于本地进程间通信
        //connected：连接成功时触发  disconnected：连接断开时触发
        //readyRead：有数据可读时触发  error：错误处理（Qt版本兼容）
        socket = new QLocalSocket(this);
        connect(socket, &QLocalSocket::connected, this, &BackendInterface::onConnected);
        connect(socket, &QLocalSocket::disconnected, this, &BackendInterface::onDisconnected);
        connect(socket, &QLocalSocket::readyRead, this, &BackendInterface::onReadyRead);

        // Qt 版本兼容的信号连接
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            connect(socket, &QLocalSocket::errorOccurred, this, &BackendInterface::onError);
        #else
            connect(socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),
                    this, &BackendInterface::onError);
        #endif
    }

    qDebug() << "正在连接后端服务..." << serverName;
    //客户端与服务器通信
    socket->connectToServer(serverName);

    // 减少等待时间，快速失败
    if (socket->waitForConnected(9000)) {
        qDebug() << "后端服务连接成功";
        return true;
    } else {
        QString errorString = socket->errorString();
        qDebug() << "后端服务连接失败:" << errorString;

        emit errorOccurred("无法连接到后端服务: " + errorString);
        return false;
    }
}
//安全关闭与后端服务的连接，确保资源正确释放。
void BackendInterface::shutdown()
{
    if (socket) {
        socket->disconnectFromServer();
        if (socket->state() != QLocalSocket::UnconnectedState) {
            socket->waitForDisconnected(500);
        }
        socket->deleteLater();
        socket = nullptr;
    }
}

bool BackendInterface::isConnected() const
{
    return socket && socket->state() == QLocalSocket::ConnectedState;
}
//这是最重要的函数，负责向后端发送请求并获取响应。
QJsonObject BackendInterface::callFunction(
    const QString &function,     // 要调用的后端函数名
    const QJsonObject &params,   // 函数参数
    int timeoutMs               // 超时时间（毫秒）
)
{
    qDebug() << "调用后端函数:" << function << "参数:" << params;

    if (!initialize()) {
        qDebug() << "后端服务未连接";
        return QJsonObject{
            {"success", false},
            {"message", "后端服务未连接"},
            {"function", function}
        };
    }

    // 1. 构造请求JSON
    QJsonObject request;
    request["function"] = function;
    request["params"] = params;

    QJsonDocument doc(request);
    //JSON序列化：将对象转换为JSON字符串
    QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n";

    // 发送请求 socket->write(data) 发送数据到后端,返回-1表示发送失败
    // 2. 通过本地Socket发送到后端
    // 序列化为JSON字符串: {"function":"Login","params":{"username":"张三","password":"123456"}}
    qint64 bytesWritten = socket->write(data);
    if (bytesWritten == -1) {
        qDebug() << "请求发送失败:" << socket->errorString();
        return QJsonObject{
            {"success", false},
            {"message", "请求发送失败: " + socket->errorString()},
            {"function", function}
        };
    }
    //最多等待5秒，防止无限阻塞
    if (!socket->waitForBytesWritten(5000)) {
        qDebug() << "等待写入超时:" << socket->errorString();
        return QJsonObject{
            {"success", false},
            {"message", "请求发送超时"},
            {"function", function}
        };
    }

    qDebug() << "请求发送成功，等待响应...";

    // 等待响应
    QJsonObject response;
    if (waitForResponse(response, timeoutMs)) {
        qDebug() << "收到响应:" << response;
        return response;
    } else {
        qDebug() << "等待响应超时";
        return QJsonObject{
            {"success", false},
            {"message", "等待响应超时"},
            {"function", function}
        };
    }
}

bool BackendInterface::waitForResponse(QJsonObject &result, int timeoutMs)
{
    // 1. 初始化事件循环和定时器
    // 2. 设置信号连接
    // 3. 进入等待状态
    // 4. 处理接收到的数据
    // 5. 返回结果
    QEventLoop loop;//局部事件循环，用于等待异步信号
    QTimer timeoutTimer;//单次触发定时器，用于超时控制
    timeoutTimer.setSingleShot(true);

    bool responseReceived = false;//标记是否收到响应
    QByteArray responseData;//存储接收到的原始数据

    // 连接超时信号
    connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

    // 用于异步处理从服务器接收到的响应数据
    //this：捕获当前类的指针，可以访问类的成员（如socket）
    //&responseReceived：通过引用捕获布尔标志，用于标记是否收到响应
    //&responseData：通过引用捕获字节数组，存储接收到的数据
    //&loop：通过引用捕获事件循环对象
    auto readHandler = [this, &responseReceived, &responseData, &loop]() {
        while (socket->canReadLine()) {//逐步检查是否有完整的一行数据
            QByteArray data = socket->readLine().trimmed();
            qDebug() << "接收到原始数据:" << data;

            if (!data.isEmpty()) {
                responseData = data;
                responseReceived = true;
                loop.quit();
                return;
            }
        }
    };

    // 连接数据可读信号 当socket有数据可读时触发
    connect(socket, &QLocalSocket::readyRead, &loop, readHandler);

    // 如果数据已经到达，立即处理，避免不必要的等待
    if (socket->canReadLine()) {
        readHandler();
    }

    // 启动超时计时器
    timeoutTimer.start(timeoutMs);

    // loop.exec() 阻塞当前线程，等待以下事件：
    //readyRead信号（有数据到达）timeout信号（超时发生）
    if (!responseReceived) {
        loop.exec();
    }

    // 清理 防止已触发的定时器继续运行 清理信号槽连接，避免内存泄漏
    timeoutTimer.stop();
    disconnect(socket, &QLocalSocket::readyRead, &loop, 0);

    // 处理响应数据
    if (responseReceived && !responseData.isEmpty()) {
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        if (doc.isObject()) {
            result = doc.object();
            qDebug() << "响应解析成功";
            return true;
        } else {
            qDebug() << "响应数据格式错误:" << responseData;
        }
    }

    return false;
}
//信号槽机制的回调函数，当socket状态变化时自动触发
void BackendInterface::onConnected()
{
    qDebug() << "已连接到后端服务";
    emit connectionStatusChanged(true);
}

void BackendInterface::onDisconnected()
{
    qDebug() << "与后端服务的连接已断开";
    emit connectionStatusChanged(false);
}

void BackendInterface::onReadyRead()
{
    // 数据读取在 waitForResponse 中处理
}

void BackendInterface::onError(QLocalSocket::LocalSocketError error)
{
    QString errorMsg;
    switch (error) {
    case QLocalSocket::ConnectionRefusedError:
        errorMsg = "连接被拒绝";
        break;
    case QLocalSocket::PeerClosedError:
        errorMsg = "后端服务已关闭";
        break;
    case QLocalSocket::ServerNotFoundError:
        errorMsg = "未找到后端服务";
        break;
    case QLocalSocket::SocketAccessError:
        errorMsg = "套接字访问错误";
        break;
    case QLocalSocket::SocketResourceError:
        errorMsg = "套接字资源错误";
        break;
    case QLocalSocket::SocketTimeoutError:
        errorMsg = "套接字超时";
        break;
    case QLocalSocket::ConnectionError:
        errorMsg = "连接错误";
        break;
    case QLocalSocket::UnsupportedSocketOperationError:
        errorMsg = "不支持的套接字操作";
        break;
    default:
        errorMsg = "未知套接字错误";
        break;
    }

    if (socket) {
        errorMsg += " (" + socket->errorString() + ")";
    }

    qDebug() << "❌ 通信错误:" << errorMsg;
    emit errorOccurred(errorMsg);
}
