#include "edit_plantinfo_dialog.h"
#include "ui_edit_plantinfo_dialog.h"
#include "Csource/cppincludes.h"
#include "notfound_dialog.h"
#include "mainwindow.h"

EditPlantInfoDialog::EditPlantInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPlantInfoDialog)
{
    ui->setupUi(this);
}

EditPlantInfoDialog::~EditPlantInfoDialog()
{
    delete ui;
}

void EditPlantInfoDialog::on_buttonBox_accepted()
{
    /*读取种植信息*/
    plantStructInfo plantSInfo = loadPlantInfoFromFile();
    /*获取到符合的种植信息*/
    plantInfo info = getPlantInfoByVegCode(plantSInfo->head ,ui->vegCode->text().toInt());
    /*如果存在，一个个修改*/
    if (info != NULL){
        if (!ui->weight->text().isEmpty()){
         info->weight = ui->weight->text().toFloat();
        }
        if (!ui->area->text().isEmpty()) {
            info->area = ui->area->text().toInt();
        }
        if (!ui->year->text().isEmpty()) {
            strcpy(info->year, ui->year->text().toUtf8().data());
        }
        /*保存到文件*/
        savePlantInfoToFile(plantSInfo->head);
        /*刷新表格*/
        emit sendBoolean(true);
    }
    else {
        /*不存在弹出未找到窗口*/
        NotFoundDialog *dialog = new NotFoundDialog(this);
        dialog->show();
    }
    /*释放内存*/
    freePlantInfo(plantSInfo->head);
}
