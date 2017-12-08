#ifndef IMFORMATIONDIALOG_H
#define IMFORMATIONDIALOG_H

#include <QDialog>

/*显示信息窗口*/

namespace Ui {
class ImformationDialog;
}

class ImformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImformationDialog(QWidget *parent = 0);
    QString imformation;
    ~ImformationDialog();
    /*show前调用，准备显示信息内容*/
    void prepareShow(void);
private:
    Ui::ImformationDialog *ui;
};

#endif // IMFORMATIONDIALOG_H
