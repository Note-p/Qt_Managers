#ifndef ADD_TYPE_DIALOG_H
#define ADD_TYPE_DIALOG_H

#include <QDialog>

/*新增蔬菜种类信息窗口*/

namespace Ui {
class AddTypeDialog;
}

class AddTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTypeDialog(QWidget *parent = 0);
    ~AddTypeDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool isChanged);
private slots:
    /*点击OK按钮槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::AddTypeDialog *ui;
};

#endif // ADD_TYPE_DIALOG_H
