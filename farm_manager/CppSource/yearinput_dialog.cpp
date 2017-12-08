#include "yearinput_dialog.h"
#include "ui_yearinput_dialog.h"

YearInputDialog::YearInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YearInputDialog)
{
    ui->setupUi(this);
}

YearInputDialog::~YearInputDialog()
{
    delete ui;
}

void YearInputDialog::on_buttonBox_accepted()
{
    emit sendYear(ui->lineEdit->text().toInt());
}
