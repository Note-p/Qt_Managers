#include "delete_type_dialog.h"
#include "ui_delete_type_dialog.h"
#include "Csource/cppincludes.h"
#include "notfound_dialog.h"

DeleteTypeDialog::DeleteTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteTypeDialog)
{
    ui->setupUi(this);
}

DeleteTypeDialog::~DeleteTypeDialog()
{
    delete ui;
}

void DeleteTypeDialog::on_buttonBox_accepted()
{
    /*从文件中读取蔬菜信息十字交叉链表*/
    typeInfo tInfo = loadFarmListFromFile();
    /*删除并判断返回值*/
    if (deleteTypeInfo(tInfo, ui->lineEdit->text().toUtf8().data()[0])) {
        /*成功 -- 保存文件并刷新*/
        saveTypeInfoToFile(tInfo);
        emit sendBoolean(true);
    }
    else {
        /*失败 -- 只能说是没有这个信息 -- 显示未找到窗口*/
        NotFoundDialog *dlg = new NotFoundDialog(this);
        dlg->show();
    }
}
