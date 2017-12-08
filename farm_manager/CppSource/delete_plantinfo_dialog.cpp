#include "delete_plantinfo_dialog.h"
#include "ui_delete_plantinfo_dialog.h"
#include "notfound_dialog.h"
#include "Csource/cppincludes.h"

DeletePlantInfoDialog::DeletePlantInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeletePlantInfoDialog)
{
    ui->setupUi(this);
}

DeletePlantInfoDialog::~DeletePlantInfoDialog()
{
    delete ui;
}

void DeletePlantInfoDialog::on_buttonBox_accepted()
{
    QString str = ui->lineEdit->text();
    /*读取蔬菜种植信息*/
    plantStructInfo info = loadPlantInfoFromFile();
    /*删除多项*/
    if (str.contains(',')){     //如果是删除多项
        for(int i = 0; i< str.count(',') + 1; i++) {    //一项项删除
            plantInfo plantinfo = getPlantInfoByID(info->head, str.section(',',i,i).toInt());
            if (plantinfo == NULL){
                NotFoundDialog *dlg = new NotFoundDialog(this);
                dlg->show();
            }
            else
                removePlantInfoItems(plantinfo);
        }
        /*删除完之后把编号重新编一次*/
        renamePlantInfoID(info->head);
    }
    /*删除一项*/
    else {
        plantInfo plantinfo = getPlantInfoByID(info->head, str.toInt());
        if (plantinfo == NULL){
            NotFoundDialog *dlg = new NotFoundDialog(this);
            dlg->show();
        }
        else
            removePlantInfoItem(plantinfo);
    }
    /*保存到文件*/
    savePlantInfoToFile(info->head);
    /*发送刷新表格信号signal*/
    emit sendBoolean(true);
    /*释放内存*/
    freePlantInfo(info->head);
}
