#include "delete_dialog.h"
#include "ui_delete_dialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::bindDeleteType(int type, DatabaseUtil database) {
    this->type = type;
    this->database = database;
}



void DeleteDialog::on_buttonBox_accepted()
{
    switch (type) {
    case DELETECUSTOMER:
        database.deleteCustomerData(ui->number->text().toInt());
        break;
    default:
        database.deleteRoomData(ui->number->text().toInt());
        break;
    }
    emit refresh();
}
