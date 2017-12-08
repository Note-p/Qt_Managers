#include "../ui/login_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.setFixedSize(w.width(),w.height());                     // 禁止拖动窗口大小
    w.show();

    return a.exec();
}

