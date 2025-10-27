#include "Receiver.h"

Receiver::Receiver(quint16 port, QObject *parent)
    : QObject(parent) {
    m_socket = new QUdpSocket(this);
    connect(m_socket, &QUdpSocket::readyRead, this, &Receiver::onReadyRead);

    if (!m_socket->bind(QHostAddress::Any, port)) {
        qDebug() << "Bind error:" << m_socket->errorString();
    } else {
        qDebug() << "UDP receiver bound to port" << port;
    }
}

void Receiver::onReadyRead() {
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
