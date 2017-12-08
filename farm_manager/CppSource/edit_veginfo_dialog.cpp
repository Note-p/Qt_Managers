#include "edit_veginfo_dialog.h"
#include "ui_edit_veginfo_dialog.h"
#include "Csource/cppincludes.h"
#include "notfound_dialog.h"

EditVegInfoDialog::EditVegInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditVegInfoDialog)
{
    ui->setupUi(this);

}

EditVegInfoDialog::~EditVegInfoDialog()
{
    delete ui;
}

void EditVegInfoDialog::on_buttonBox_accepted()
{
    /*读取蔬菜基本信息*/
    vegStructInfo vegSInfo = loadVegInfoFromFile();
    /*找到对应基本信息结构体*/
    vegInfo info = getVegInfoByCode(vegSInfo->head ,ui->vegCode->text().toInt());
    if (info != NULL){
        /*存在--一个个修改*/
        if (!ui->vegType->text().isEmpty()) {
            info->vegType = ui->vegType->text().toInt() + '0';
        }
        if (!ui->textEdit->toPlainText().isEmpty()) {
            strcpy(info->nutritionFacts, ui->textEdit->toPlainText().toUtf8().data());
        }
        /*保存文件*/
        saveVegInfoToFile(vegSInfo->head);
        /*刷新表格*/
        emit sendBoolean(true);
    }
    else {
        /*不存在--显示未找到窗口*/
        NotFoundDialog *dialog = new NotFoundDialog(this);
        dialog->show();
    }
    /*释放内存*/
    freeVegInfo(vegSInfo->head);
}
