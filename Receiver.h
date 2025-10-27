#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QDebug>

class Receiver : public QObject
{
    Q_OBJECT

public:
    explicit Receiver(quint16 port = 1234, QObject *parent = nullptr);

private slots:
    void onReadyRead();

private:
    QUdpSocket *m_socket;
};

#endif // RECEIVER_H