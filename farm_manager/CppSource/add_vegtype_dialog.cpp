#include "add_vegtype_dialog.h"
#include "ui_add_vegtype_dialog.h"

AddVegTypeDialog::AddVegTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVegTypeDialog)
{
    ui->setupUi(this);
}

AddVegTypeDialog::~AddVegTypeDialog()
{
    delete ui;
}

void AddVegTypeDialog::on_buttonBox_accepted()
{
    /*从文件中读取蔬菜基本信息*/
    vegStructInfo info = loadVegInfoFromFile();
    /*新增蔬菜基本信息至链表*/
    addVegInfoItem(info->tail,
                   createVegInfoItem(info->tail->vegCode + 1,
                                     ui->vegName->text().toUtf8().data(),
                                     ui->vegType->text().toUtf8().data(),
                                     ui->vegN->toPlainText().toUtf8().data()));
    /*保存蔬菜基本信息至文件*/
    saveVegInfoToFile(info->head);
    /*发送刷新表格信号signal*/
    emit sendBoolean(true);
    /*释放内存*/
    freeVegInfo(info->head);
}
