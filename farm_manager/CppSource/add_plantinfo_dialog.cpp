#include "add_plantinfo_dialog.h"
#include "ui_add_plantinfo_dialog.h"
#include "Csource/cppincludes.h"

AddPlantInfoDialog::AddPlantInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlantInfoDialog)
{
    ui->setupUi(this);
}

AddPlantInfoDialog::~AddPlantInfoDialog()
{
    delete ui;
}

/*选择 OK */
void AddPlantInfoDialog::on_buttonBox_accepted()
{
    /*读取蔬菜种植信息单链表*/
    plantStructInfo plantStruct = loadPlantInfoFromFile();
    /*将输入框内容发至核心层处理*/
    addPlantInfoItem(plantStruct->tail,
                     createPlantInfoItem(plantStruct->tail->id + 1,
                                         ui->textVegCode->text().toLatin1().data(), ui->textArea->text().toLatin1().data(),
                                         ui->textWeight->text().toLatin1().data(), ui->textYear->text().toLatin1().data()));
    /*保存修改后的链表*/
    savePlantInfoToFile(plantStruct->head);
    /*释放内存*/
    freePlantInfo(plantStruct->head);
    free(plantStruct);
    /*发送刷新表格信号signal*/
    emit sendBoolean(true);
}
