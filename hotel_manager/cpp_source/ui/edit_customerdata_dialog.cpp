#include "edit_customerdata_dialog.h"
#include "ui_edit_customerdata_dialog.h"
#include "QDateTime"

EditCustomerDataDialog::EditCustomerDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCustomerDataDialog)
{
    ui->setupUi(this);
    currentDateTime = QDateTime::currentDateTime();
    ui->checkin->setDateTime(currentDateTime);
    ui->checkout->setDateTime(currentDateTime);
    ui->schedule->setDateTime(currentDateTime);
}

EditCustomerDataDialog::~EditCustomerDataDialog()
{
    delete ui;
}

void EditCustomerDataDialog::bindDatabase(DatabaseUtil database) {
    this->database = database;
}


void EditCustomerDataDialog::on_buttonBox_accepted()
{
    database.updateCustomerData(ui->id->text().toInt(),
                                ui->type->text().isEmpty()? -1:ui->type->text().toInt(),
                                ui->name->text().isEmpty()? NULL:ui->name->text(),
                                ui->phone->text().isEmpty()? NULL:ui->phone->text(),
                                ui->checkin->dateTime() == currentDateTime? NULL:ui->checkin->dateTime().toString(),
                                ui->checkout->dateTime() == currentDateTime? NULL:ui->checkout->dateTime().toString(),
                                ui->schedule->dateTime() == currentDateTime? NULL:ui->schedule->dateTime().toString(),
                                ui->vip->text().isEmpty()? NULL:ui->vip->text(),
                                ui->point->text().isEmpty()? -1:ui->point->text().toInt(),
                                ui->deposit->text().isEmpty()? -1:ui->deposit->text().toFloat(),
                                ui->room->text().isEmpty()? NULL:ui->room->text());
    emit refresh();
}
