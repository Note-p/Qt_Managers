#include "login_window.h"
#include "ui_login_window.h"
#include "main_window.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->pushButton->setShortcut(Qt::Key_Enter);
    ui->pushButton->setShortcutEnabled(Qt::Key_Enter, true);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login() {
    MainWindow *mainWindow = new MainWindow();
    //mainWindow->showMaximized();
    mainWindow->show();
    this->close();
}

void LoginWindow::on_pushButton_clicked()
{
    //if (ui->username->text() == QString("test") && ui->password->text() == QString("test")) {
        login();
    //}
}

