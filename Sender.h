#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>

class Sender : public QObject
{
    Q_OBJECT

public:
    explicit Sender(const QHostAddress &address = QHostAddress::LocalHost,
                   quint16 port = 1234, QObject *parent = nullptr);

    ~Sender();

public slots:
    void start();   // Запуск отправки
    void stop();    // Остановка отправки

private slots:
    void sendDatagram();

private:
    QUdpSocket *m_socket;
    QTimer *m_timer;
    QHostAddress m_targetAddress;
    quint16 m_targetPort;
};

#endif // SENDER_H