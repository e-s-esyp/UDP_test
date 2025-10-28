#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent)
    : QObject(parent)
    , m_senderThread(nullptr)
    , m_sender(nullptr)
    , m_receiverThread(nullptr)
    , m_receiver(nullptr)
{
}

ThreadManager::~ThreadManager()
{
    stopSender();
    stopReceiver();
}

void ThreadManager::startSender()
{
    if (m_senderThread) {
        return; // Уже запущен
    }

    m_senderThread = new QThread(this);
    m_sender = new Sender(QHostAddress::LocalHost, 1234);
    m_sender->moveToThread(m_senderThread);

    // Соединяем сигналы потока для управления жизненным циклом
    connect(m_senderThread, &QThread::started, m_sender, &Sender::start);
    connect(m_senderThread, &QThread::finished, m_sender, &Sender::stop);
    connect(m_senderThread, &QThread::finished, m_sender, &Sender::deleteLater);
    connect(m_senderThread, &QThread::finished, m_senderThread, &QThread::deleteLater);

    m_senderThread->start();
    qDebug() << "Sender thread started";
}

void ThreadManager::stopSender()
{
    if (!m_senderThread) {
        return;
    }

    m_senderThread->quit();
    m_senderThread->wait(1000); // Ждем до 1 секунды для завершения

    // Обнуляем указатели, так как объекты будут удалены через deleteLater
    m_sender = nullptr;
    m_senderThread = nullptr;
    qDebug() << "Sender thread stopped";
}

void ThreadManager::startReceiver()
{
    if (m_receiverThread) {
        return;
    }

    m_receiverThread = new QThread(this);
    m_receiver = new Receiver(1234);
    m_receiver->moveToThread(m_receiverThread);

    connect(m_receiverThread, &QThread::started, m_receiver, &Receiver::start);
    connect(m_receiverThread, &QThread::finished, m_receiver, &Receiver::stop);
    connect(m_receiverThread, &QThread::finished, m_receiver, &Receiver::deleteLater);
    connect(m_receiverThread, &QThread::finished, m_receiverThread, &QThread::deleteLater);

    m_receiverThread->start();
    qDebug() << "Receiver thread started";
}

void ThreadManager::stopReceiver()
{
    if (!m_receiverThread) {
        return;
    }

    m_receiverThread->quit();
    m_receiverThread->wait(1000);

    m_receiver = nullptr;
    m_receiverThread = nullptr;
    qDebug() << "Receiver thread stopped";
}