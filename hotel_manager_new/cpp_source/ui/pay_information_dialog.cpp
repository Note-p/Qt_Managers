#include "pay_information_dialog.h"
#include "ui_pay_information_dialog.h"
#include "QDateTime"
#include <QDate>

PayInformationDialog::PayInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PayInformationDialog)
{
    ui->setupUi(this);
}

PayInformationDialog::~PayInformationDialog()
{
    delete ui;
}

void PayInformationDialog::bind(Room *room, Customer *customer, DatabaseUtil database) {
    this->room = room;
    this->customer = customer;
    this->database = database;

    price = room->price * QDateTime::fromString(customer->checkInTime).date().daysTo(QDate::currentDate());

    ui->number->setText(QString::number(customer->customerID));
    ui->name->setText(customer->userName);
    ui->phone->setText(customer->phone);
    ui->room_number->setText(QString::number(room->roomNumber));
    ui->room_price->setText(QString::number(room->price) + (room->roomType == SPECIALDISCOUNTROOM? "/hour":"/day"));
    ui->checkin->setText(customer->checkInTime);
    ui->price->setText(QString::number(price));

    if (customer->customerType == ORDINARY) {
        ui->deposit_label->hide();
        ui->deposit->hide();
        ui->point->hide();
        ui->point_label->hide();
    }
    else if (customer->customerType == VIP) {
        ui->deposit->hide();
        ui->deposit_label->hide();
        ui->point->setText(QString("%1 + %2").arg(customer->point).arg(price));
    }
    else {
        ui->point->setText(QString("%1 + %2").arg(customer->point).arg(price));
        ui->deposit->setText(QString("%1 - %2").arg(customer->deposit).arg(price));
    }

}



void PayInformationDialog::on_buttonBox_accepted()
{
    database.deleteCustomerData(customer->customerID);
    if (customer->customerType == VIP) {
        customer->checkInTime = "";
        customer->checkOutTime = "";
        customer->point += price;
        customer->roomNumber = "";
        database.insertCustomerData(customer);
    }
    else if (customer->customerType == SVIP) {
        customer->checkInTime = "";
        customer->checkOutTime = "";
        customer->point += price;
        customer->deposit -= price;
        customer->roomNumber = "";
        database.insertCustomerData(customer);
    }
}
