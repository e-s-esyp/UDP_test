#include "Sender.h"

#include <QThread>

Sender::Sender(const QHostAddress &address, quint16 port, QObject *parent)
    : QObject(parent), m_targetAddress(address), m_targetPort(port)
{
    m_socket = new QUdpSocket(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000); // 1 секунда
    
    connect(m_timer, &QTimer::timeout, this, &Sender::sendDatagram);
}

Sender::~Sender()
{
    stop();
    qDebug() << "Sender destroyed";
}

void Sender::start()
{
    if (m_timer->isActive()) {
        return;
    }
    
    qDebug() << "Starting UDP sender to" << m_targetAddress.toString() << ":" << m_targetPort;
    m_timer->start();
}

void Sender::stop()
{
    m_timer->stop();
    qDebug() << "UDP sender stopped";
}

void Sender::sendDatagram()
{
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