#ifndef ADDPLANTINFODIALOG_H
#define ADDPLANTINFODIALOG_H

#include <QDialog>

/*新增蔬菜种植信息窗口*/

namespace Ui {
class AddPlantInfoDialog;
}

class AddPlantInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlantInfoDialog(QWidget *parent = 0);
    ~AddPlantInfoDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool isChanged);
private slots:
    /*OK按钮点击槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::AddPlantInfoDialog *ui;
};

#endif // ADDPLANTINFODIALOG_H
