#include "number_input_dialog.h"
#include "ui_number_input_dialog.h"
#include "../core/customer.h"
#include "../core/room.h"
#include "pay_information_dialog.h"

NumberInputDialog::NumberInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumberInputDialog)
{
    ui->setupUi(this);
}

NumberInputDialog::~NumberInputDialog()
{
    delete ui;
}

void NumberInputDialog::bind(DatabaseUtil database) {
    this->database = database;
}

void NumberInputDialog::on_buttonBox_accepted()
{
    emit sendNumber(ui->number->text().toInt());
}
