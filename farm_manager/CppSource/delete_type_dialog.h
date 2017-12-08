#ifndef DELETE_TYPE_DIALOG_H
#define DELETE_TYPE_DIALOG_H

#include <QDialog>

/*删除蔬菜种类信息窗口*/

namespace Ui {
class DeleteTypeDialog;
}

class DeleteTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteTypeDialog(QWidget *parent = 0);
    ~DeleteTypeDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean (bool isChanged);
private slots:
    /*点击OK槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::DeleteTypeDialog *ui;
};

#endif // DELETE_TYPE_DIALOG_H
