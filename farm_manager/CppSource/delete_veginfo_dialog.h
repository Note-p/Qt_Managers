#ifndef DELETE_VEGINFO_DIALOG_H
#define DELETE_VEGINFO_DIALOG_H

#include <QDialog>

/*删除蔬菜基本信息窗口---注释同前面的删除*/

namespace Ui {
class DeleteVegInfoDialog;
}

class DeleteVegInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteVegInfoDialog(QWidget *parent = 0);
    ~DeleteVegInfoDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    sendBoolean(bool);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeleteVegInfoDialog *ui;
};

#endif // DELETE_VEGINFO_DIALOG_H
