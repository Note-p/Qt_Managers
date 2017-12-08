#ifndef EDITPLANTINFODIALOG_H
#define EDITPLANTINFODIALOG_H

#include <QDialog>
#include "mainwindow.h"

/*修改蔬菜种植信息窗口*/

namespace Ui {
class EditPlantInfoDialog;
}

class EditPlantInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPlantInfoDialog(QWidget *parent = 0);
    ~EditPlantInfoDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool isChanged);
private slots:
    /*点击OK槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::EditPlantInfoDialog *ui;
};

#endif // EDITPLANTINFODIALOG_H
