#ifndef TEST_H
#define TEST_H

#include "Receiver.h"
#include "Sender.h"

#include <QObject>
#include <QThread>
#include <QDebug>

#include "Receiver.h"

class Test: public QObject {
    Q_OBJECT

protected:
    ~Test() = default;

public:
    static QThread * test() {
        qDebug() << "Main thread:" << (quintptr) QThread::currentThreadId();

        // Создаем приемник в главном потоке
        Receiver receiver(1234);

        // Создаем поток для отправителя
        QThread *senderThread = new QThread();
        Sender *sender = new Sender(QHostAddress::LocalHost, 1234);

        // Перемещаем отправителя в отдельный поток
        sender->moveToThread(senderThread);

        // Подключаем сигналы для управления жизненным циклом
        connect(senderThread, &QThread::started, sender, &Sender::startSending);
        connect(senderThread, &QThread::finished, sender, &Sender::stopSending);
        connect(senderThread, &QThread::finished, sender, &Sender::deleteLater);
        connect(senderThread, &QThread::finished, senderThread, &QThread::deleteLater);

        // Запускаем поток
        senderThread->start();

        qDebug() << "Application started. Press Ctrl+C to stop.";

        return senderThread;
    }
};


#endif //TEST_H
