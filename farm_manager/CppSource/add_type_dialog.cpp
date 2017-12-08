#include "add_type_dialog.h"
#include "ui_add_type_dialog.h"
#include "Csource/cppincludes.h"

AddTypeDialog::AddTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTypeDialog)
{
    ui->setupUi(this);
}

AddTypeDialog::~AddTypeDialog()
{
    delete ui;
}

void AddTypeDialog::on_buttonBox_accepted()
{
    /*从文件读取蔬菜种类信息*/
    typeInfo tInfo = loadFarmListFromFile();
    /*增加蔬菜种类信息到链表*/
    addTypeInfoItem(tInfo, ui->lineEdit->text().toUtf8().data());
    /*保存蔬菜种类信息到文件*/
    saveTypeInfoToFile(tInfo);
    /*发送刷新表格信号量signal*/
    emit sendBoolean(true);
}
