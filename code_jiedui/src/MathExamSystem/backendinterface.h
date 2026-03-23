#ifndef BACKENDINTERFACE_H
#define BACKENDINTERFACE_H

#include <QLocalSocket>
#include <QObject>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>

class BackendInterface : public QObject
{
    Q_OBJECT

public:
    static BackendInterface& instance();

    bool initialize();
    void shutdown();
    bool isConnected() const;

    // 同步调用方法
    QJsonObject callFunction(const QString &function,
                            const QJsonObject &params = QJsonObject(),
                            int timeoutMs = 5000);

signals:
    void responseReceived(const QJsonObject &response);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QLocalSocket::LocalSocketError error);  // 确保参数类型正确

private:
    explicit BackendInterface(QObject *parent = nullptr);
    bool waitForResponse(QJsonObject &result, int timeoutMs);

    QLocalSocket *socket;
    QString serverName;
    QByteArray receivedData;
};

#endif
