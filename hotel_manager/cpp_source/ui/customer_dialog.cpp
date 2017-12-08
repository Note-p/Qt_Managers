#include "customer_dialog.h"
#include "ui_customer_dialog.h"
#include "../core/customer.h"
#include <QDateTime>

CustomerDialog::CustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerDialog)
{
    ui->setupUi(this);
    ui->checkin->setDateTime(QDateTime::currentDateTime());
    ui->checkout->setDateTime(QDateTime::currentDateTime());
    ui->schedule->setDateTime(QDateTime::currentDateTime());
}

CustomerDialog::~CustomerDialog()
{
    delete ui;
}


void CustomerDialog::bindDatabase(DatabaseUtil database) {
    this->database = database;
}

void CustomerDialog::on_buttonBox_accepted()
{
    if (ui->vip->text().isEmpty()) {
        database.insertCustomerData(ORDINARY, ui->user_name->text(), ui->phone->text(),
                                    ui->checkin->dateTime().toString(),
                                    ui->checkout->dateTime().toString(),
                                    ui->schedule->dateTime().toString(),NULL,0,0,-1,ui->room->text());
    }
    else {
        if (ui->deposit->text().isEmpty()) {
            database.insertCustomerData(VIP, ui->user_name->text(), ui->phone->text(),
                                        ui->checkin->dateTime().toString(),
                                        ui->checkout->dateTime().toString(),
                                        ui->schedule->dateTime().toString(),
                                        ui->vip->text(), 0,0,-1,ui->room->text());
        }
        else {
            database.insertCustomerData(SVIP, ui->user_name->text(), ui->phone->text(),
                                        ui->checkin->dateTime().toString(),
                                        ui->checkout->dateTime().toString(),
                                        ui->schedule->dateTime().toString(),
                                        ui->vip->text(), 0, ui->deposit->text().toFloat(),-1,ui->room->text());
        }
    }
    emit refresh();
}
