#include "vegcode_input_dialog.h"
#include "ui_vegcode_input_dialog.h"

VegCodeInputDialog::VegCodeInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VegCodeInputDialog)
{
    ui->setupUi(this);
}

VegCodeInputDialog::~VegCodeInputDialog()
{
    delete ui;
}

void VegCodeInputDialog::on_buttonBox_accepted()
{
    emit sendVegCode(ui->lineEdit->text().toInt());
}
