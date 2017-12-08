#ifndef YEARINPUTDIALOG_H
#define YEARINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class YearInputDialog;
}

/*输入年份的窗口*/

class YearInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YearInputDialog(QWidget *parent = 0);
    ~YearInputDialog();
signals:
    /*发送结果给主窗口*/
    void sendYear(int year);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::YearInputDialog *ui;
};

#endif // YEARINPUTDIALOG_H
