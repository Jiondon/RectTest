#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{time process} %{function} %{line} %{threadid}] %{if-category}%{category}: %{endif}%{message}");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
