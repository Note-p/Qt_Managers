#include "vip_checkin_dialog.h"
#include "ui_vip_checkin_dialog.h"
#include "QDateTime"
#include "../core/customer.h"

VipCheckInDialog::VipCheckInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VipCheckInDialog)
{
    ui->setupUi(this);
    QDateTime dateTime = QDateTime::currentDateTime();
    ui->checkin->setDateTime(dateTime);
    ui->checkout->setDateTime(dateTime);
    ui->schedule->setDateTime(dateTime);
}

VipCheckInDialog::~VipCheckInDialog()
{
    delete ui;
}

void VipCheckInDialog::bind(DatabaseUtil database) {
    this->database = database;
}

void VipCheckInDialog::on_buttonBox_accepted()
{
    Customer* customer = database.getCustomerDataByVIP(ui->vip->text().toInt());
    if (!customer)
        return ;
    customer->checkInTime = ui->checkin->dateTime().toString();
    customer->checkOutTime = ui->checkout->dateTime().toString();
    customer->scheduleTime = ui->schedule->dateTime().toString();
    customer->roomNumber = ui->room->text().toInt();
    database.deleteCustomerData(customer->customerID);
    database.insertCustomerData(customer);
    emit refresh();
}
