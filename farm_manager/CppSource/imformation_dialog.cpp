#include "imformation_dialog.h"
#include "ui_imformation_dialog.h"

ImformationDialog::ImformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImformationDialog)
{
    ui->setupUi(this);
}

void ImformationDialog::prepareShow() {
    /*显示之前调用，只是修改label显示文本*/
    ui->label->setText(imformation);
}

ImformationDialog::~ImformationDialog()
{
    delete ui;
}
