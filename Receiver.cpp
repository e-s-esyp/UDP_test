#include "Receiver.h"

Receiver::Receiver(quint16 port, QObject *parent)
    : QObject(parent), m_port(port)
{
    m_socket = new QUdpSocket(this);
    connect(m_socket, &QUdpSocket::readyRead, this, &Receiver::onReadyRead);
}

Receiver::~Receiver()
{
    stop();
    qDebug() << "Receiver destroyed";
}

void Receiver::start() const {
    if (m_socket->state() == QAbstractSocket::BoundState) {
        return;
    }

    if (!m_socket->bind(QHostAddress::Any, m_port)) {
        qDebug() << "Bind error:" << m_socket->errorString();
    } else {
        qDebug() << "UDP receiver bound to port" << m_port;
    }
}

void Receiver::stop() const {
    m_socket->close();
    qDebug() << "UDP receiver stopped";
}

void Receiver::onReadyRead() const {
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "Received from" << sender.toString() << ":" << senderPort
                 << "-" << datagram;
    }
}
