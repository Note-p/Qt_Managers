#include "edit_type_dialog.h"
#include "ui_edit_type_dialog.h"
#include "Csource/cppincludes.h"
#include "notfound_dialog.h"

EditTypeDialog::EditTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTypeDialog)
{
    ui->setupUi(this);
}

EditTypeDialog::~EditTypeDialog()
{
    delete ui;
}

void EditTypeDialog::on_buttonBox_accepted()
{
    typeInfo tInfo = loadFarmListFromFile();
    if (editTypeInfo(tInfo, ui->lineEdit->text().toUtf8().data()[0], ui->lineEdit_2->text().toUtf8().data())) {
        /*修改成功--保存--刷新*/
        saveTypeInfoToFile(tInfo);
        emit sendBoolean(true);
    }
    else {
        /*没找到*/
        NotFoundDialog *dlg = new NotFoundDialog(this);
        dlg->show();
    }
}
