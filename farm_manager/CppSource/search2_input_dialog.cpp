#include "search2_input_dialog.h"
#include "ui_search2_input_dialog.h"

Search2InputDialog::Search2InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search2InputDialog)
{
    ui->setupUi(this);
}

Search2InputDialog::~Search2InputDialog()
{
    delete ui;
}


void Search2InputDialog::PrepareShow(QString labelOne, QString labelTwo) {
    ui->label->setText(labelOne);
    ui->label_2->setText(labelTwo);
}

void Search2InputDialog::on_buttonBox_accepted()
{
    searchData data = searchData(ui->lineEdit->text(), ui->lineEdit_2->text());
    emit sendSearchData(data);
}
