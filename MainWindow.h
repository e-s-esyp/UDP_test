#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "threadmanager.h"
#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

class MainWindow final : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
    QVBoxLayout *layout;
public:
    explicit MainWindow(ThreadManager *threadManager, QWidget *parent = nullptr)
        : QMainWindow(parent), m_threadManager(threadManager) {
        // Создаем центральный виджет
        centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Создаем layout
        layout = new QVBoxLayout(centralWidget);

        // Создаем информационную метку
        m_infoLabel = new QLabel(this);
        m_infoLabel->setAlignment(Qt::AlignCenter);
        m_infoLabel->setText(
            "UDP Test Application\n\n"
            "Controls:\n"
            "1 - Start Sender\n"
            "2 - Stop Sender\n"
            "3 - Start Receiver\n"
            "4 - Stop Receiver\n"
            "Q - Quit\n\n"
            "Press keys to control threads..."
        );

        layout->addWidget(m_infoLabel);

        // Настраиваем окно
        setWindowTitle("UDP Test Application");
        resize(400, 300);

        qDebug() << "Main thread:" << reinterpret_cast<quintptr>(QThread::currentThreadId());
        qDebug() << "=== UDP Test Application ===";
        qDebug() <<
                "Controls: 1-Start Sender, 2-Stop Sender, 3-Start Receiver, 4-Stop Receiver, Q-Quit";
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_1:
                qDebug() << "Key 1 pressed - Starting sender...";
                m_threadManager->startSender();
                break;
            case Qt::Key_2:
                qDebug() << "Key 2 pressed - Stopping sender...";
                m_threadManager->stopSender();
                break;
            case Qt::Key_3:
                qDebug() << "Key 3 pressed - Starting receiver...";
                m_threadManager->startReceiver();
                break;
            case Qt::Key_4:
                qDebug() << "Key 4 pressed - Stopping receiver...";
                m_threadManager->stopReceiver();
                break;
            case Qt::Key_Q:
                qDebug() << "Key Q pressed - Exiting application...";
                QApplication::quit();
                break;
            default:
                QMainWindow::keyPressEvent(event);
                break;
        }
    }

private:
    ThreadManager *m_threadManager;
    QLabel *m_infoLabel;
};


#endif //MAINWINDOW_H
