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
    ~Receiver();

public slots:
    void start() const;
    void stop() const;
    void onReadyRead() const;

private:
    QUdpSocket *m_socket;
    quint16 m_port;

};

#endif // RECEIVER_H