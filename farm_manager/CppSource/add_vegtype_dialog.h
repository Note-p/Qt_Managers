#ifndef ADDVEGTYPEDIALOG_H
#define ADDVEGTYPEDIALOG_H

#include <QDialog>
#include "Csource/cppincludes.h"

/*新增蔬菜基本信息窗口*/

namespace Ui {
class AddVegTypeDialog;
}

class AddVegTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddVegTypeDialog(QWidget *parent = 0);
    ~AddVegTypeDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool isChanged);
private slots:
    /*OK按钮点击槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::AddVegTypeDialog *ui;
};

#endif // ADDVEGTYPEDIALOG_H
