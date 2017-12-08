#ifndef DELETE_PLANTINFO_DIALOG_H
#define DELETE_PLANTINFO_DIALOG_H

#include <QDialog>
#include "Csource/cppincludes.h"

/*删除蔬菜种植信息窗口*/

namespace Ui {
class DeletePlantInfoDialog;
}

class DeletePlantInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeletePlantInfoDialog(QWidget *parent = 0);
    ~DeletePlantInfoDialog();
signals:
    /*信号量函数，用于发送boolean给槽函数*/
    void sendBoolean(bool isChanged);
private slots:
    /*点击OK槽函数*/
    void on_buttonBox_accepted();

private:
    Ui::DeletePlantInfoDialog *ui;
};

#endif // DELETE_PLANTINFO_DIALOG_H
