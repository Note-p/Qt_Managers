#include "delete_veginfo_dialog.h"
#include "ui_delete_veginfo_dialog.h"
#include "Csource/cppincludes.h"
#include "notfound_dialog.h"

DeleteVegInfoDialog::DeleteVegInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteVegInfoDialog)
{
    ui->setupUi(this);
}

DeleteVegInfoDialog::~DeleteVegInfoDialog()
{
    delete ui;
}

void DeleteVegInfoDialog::on_buttonBox_accepted()
{
    QString str = ui->lineEdit->text();
    vegStructInfo info = loadVegInfoFromFile();
    //vegInfo current = info->head;
    /*删除多项*/
    if (str.contains(',')){
        for(int i = 0; i< str.count(',') + 1; i++) {
            vegInfo veginfo = getVegInfoByCode(info->head, str.section(',',i,i).toInt());
            if (veginfo == NULL){
                NotFoundDialog *dlg = new NotFoundDialog(this);
                dlg->show();
            }
            else
                removeVegInfoItems(veginfo);
        }
        renameVegInfoID(info->head);
    }
    /*删除一项*/
    else {
        vegInfo veginfo = getVegInfoByCode(info->head, str.toInt());
        if (veginfo == NULL){
            NotFoundDialog *dlg = new NotFoundDialog(this);
            dlg->show();
        }
        else
            removeVegInfoItem(veginfo);
    }
    saveVegInfoToFile(info->head);
    emit sendBoolean(true);
    freeVegInfo(info->head);
}
