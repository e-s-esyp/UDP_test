#include <QApplication>
#include "MainWindow.h"
#include "threadmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ThreadManager threadManager;
    MainWindow window(&threadManager);
    window.show();
    return QApplication::exec();
}

// #include "main.moc"