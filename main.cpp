#include <QCoreApplication>

#include "Test.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qDebug() << "Hello World"; {
        // const UdpClientWorker udpSocket;
        // udpSocket.getAddr();
        // qDebug() << "getAddr done";
    }
    auto senderThread = Test::test();
    int result = a.exec();

    // Корректно останавливаем поток при выходе
    if (senderThread->isRunning()) {
        senderThread->quit();
        senderThread->wait(1000); // Ждем до 1 секунды для завершения
    }

    return result;
    // return QCoreApplication::exec();
}

#include "main.moc"
