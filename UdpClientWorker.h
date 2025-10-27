#ifndef UDPCLIENTWORKER_H
#define UDPCLIENTWORKER_H

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpClientWorker final : public QObject {
    Q_OBJECT

public:
    QVector<QString> addresses{};

    explicit UdpClientWorker(QObject *parent = nullptr) : QObject(parent) {
        udpSocket = new QUdpSocket();
        addresses.reserve(10);
        addresses.append("start");
        connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClientWorker::readData);
        connect(this, &UdpClientWorker::responseReceived, this, &UdpClientWorker::saveAddress);
        // Функция для закрытия сокета
        auto closeSocket = [&]() {
            qDebug() << "Closing socket...";
            // udpSocket->disconnect();
            udpSocket->close();
            if (udpSocket->state() == QUdpSocket::UnconnectedState) {
                qDebug() << "Socket closed successfully";
            } else {
                qDebug() << "Close error:" << udpSocket->errorString();
            }
            // udpSocket->deleteLater();
            // udpSocket = nullptr;
            if (!addresses.empty()) {
                qDebug() << addresses;
                for (const auto &a: addresses) {
                    qDebug() << a;
                }
            }
            // 4. Завершаем приложение
            // QCoreApplication::quit();
        };
        QTimer::singleShot(2000, closeSocket);
    }

    ~UdpClientWorker() override {
        qDebug() << "~UdpClientWorker";
        // if (udpSocket != nullptr) {
            // delete udpSocket;
            // udpSocket->deleteLater();
        // }
    }

    void getAddr() const {
        qDebug() << "getAddr";
        if (udpSocket != nullptr) {
            udpSocket->bind(45454);
            udpSocket->writeDatagram(QString("SERVER_DISCOVERY_REQUEST").toUtf8(),
                                     QHostAddress::Broadcast, // Отправка всем в сети
                                     45454);
        }
    }

private slots:
    void bind(const quint16 port) const {
        udpSocket->bind(port);
    }

    void readData() {
        qDebug() << "readData";
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(static_cast<int>(udpSocket->pendingDatagramSize()));
            QHostAddress sender;
            quint16 port = 45454;
            udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &port);
            if (datagram == "SERVER_DISCOVERY_RESPONSE") {
                emit responseReceived(QString::fromUtf8(datagram), sender.toString());
            }
        }
    }

    void saveAddress(const QString &a, const QString &b) {
        qDebug() << "received" << a << b;
        addresses.append(b);
    }

signals:
    void responseReceived(const QString &, const QString &);

private:
    QUdpSocket *udpSocket{};
};

#include "main.moc"

#endif //UDPCLIENTWORKER_H
