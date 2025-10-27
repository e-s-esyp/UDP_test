#ifndef SENDER_H
#define SENDER_H


#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QThread>
#include <QDebug>

class Sender final : public QObject
{
    Q_OBJECT

public:
    explicit Sender(const QHostAddress &address = QHostAddress::LocalHost,
                   quint16 port = 1234, QObject *parent = nullptr)
        : QObject(parent), m_targetAddress(address), m_targetPort(port)
    {
        m_socket = new QUdpSocket(this);
        m_timer = new QTimer(this);

        connect(m_timer, &QTimer::timeout, this, &Sender::sendDatagram);
    }

    ~Sender() {
        qDebug() << "Sender destroyed";
    }

public slots:
    void startSending() {
        if (m_timer->isActive()) {
            return;
        }

        qDebug() << "Starting UDP sender to" << m_targetAddress.toString() << ":" << m_targetPort;
        m_timer->start(1000); // Каждую секунду
        sendDatagram(); // Отправить сразу при старте
    }

    void stopSending() {
        m_timer->stop();
        qDebug() << "UDP sender stopped";
    }

    void setTarget(const QHostAddress &address, quint16 port) {
        m_targetAddress = address;
        m_targetPort = port;
    }

private slots:
    void sendDatagram() {
        static int counter = 0;
        QString message = QString("UDP message #%1 from thread: %2")
                             .arg(++counter)
                             .arg((quintptr)QThread::currentThreadId());

        QByteArray datagram = message.toUtf8();

        qint64 bytesSent = m_socket->writeDatagram(datagram, m_targetAddress, m_targetPort);

        if (bytesSent == -1) {
            qDebug() << "Failed to send datagram:" << m_socket->errorString();
        } else {
            qDebug() << "Sent:" << message;
        }
    }

private:
    QUdpSocket *m_socket;
    QTimer *m_timer;
    QHostAddress m_targetAddress;
    quint16 m_targetPort;
};



#endif //SENDER_H
