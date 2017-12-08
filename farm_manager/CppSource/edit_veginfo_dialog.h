#ifndef EDITVEGINFODIALOG_H
#define EDITVEGINFODIALOG_H

#include <QDialog>

/*修改蔬菜基本信息窗口*/

namespace Ui {
class EditVegInfoDialog;
}

class EditVegInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditVegInfoDialog(QWidget *parent = 0);
    ~EditVegInfoDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool isChanged);
private slots:
    /*点击OK槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::EditVegInfoDialog *ui;
};

#endif // EDITVEGINFODIALOG_H
