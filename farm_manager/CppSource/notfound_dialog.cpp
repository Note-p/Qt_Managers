#include "notfound_dialog.h"
#include "ui_notfound_dialog.h"

NotFoundDialog::NotFoundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotFoundDialog)
{
    ui->setupUi(this);
}

NotFoundDialog::~NotFoundDialog()
{
    delete ui;
}
