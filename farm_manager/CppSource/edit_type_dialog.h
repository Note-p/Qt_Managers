#ifndef EDIT_TYPE_DIALOG_H
#define EDIT_TYPE_DIALOG_H

#include <QDialog>

/*修改蔬菜种类信息窗口*/

namespace Ui {
class EditTypeDialog;
}

class EditTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTypeDialog(QWidget *parent = 0);
    ~EditTypeDialog();

private slots:
    /*点击OK槽*/
    void on_buttonBox_accepted();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool);
private:
    Ui::EditTypeDialog *ui;
};

#endif // EDIT_TYPE_DIALOG_H
