#include "mainwindow.h"
#include <QApplication>
#include "Csource/cppincludes.h"

/*
 * 形式上的main函数
 * 启动main窗口就没用了
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
