#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QThread>
#include "Sender.h"
#include "Receiver.h"

class ThreadManager : public QObject
{
    Q_OBJECT

public:
    explicit ThreadManager(QObject *parent = nullptr);
    ~ThreadManager();

public slots:
    void startSender();
    void stopSender();
    void startReceiver();
    void stopReceiver();

private:
    QThread* m_senderThread;
    Sender* m_sender;
    QThread* m_receiverThread;
    Receiver* m_receiver;
};

#endif // THREADMANAGER_H