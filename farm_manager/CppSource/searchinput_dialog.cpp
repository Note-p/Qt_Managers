#include "searchinput_dialog.h"
#include "ui_searchinput_dialog.h"


SearchInputDialog::SearchInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchInputDialog)
{
    ui->setupUi(this);
}

void SearchInputDialog::prepareShow() {
    ui->label->setText(searchLabel);
}


SearchInputDialog::~SearchInputDialog()
{
    delete ui;
}

void SearchInputDialog::on_buttonBox_accepted()
{
    emit sendSearch(ui->lineEdit->text());
}
