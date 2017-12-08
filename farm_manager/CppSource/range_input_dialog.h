#ifndef RANGE_INPUT_DIALOG_H
#define RANGE_INPUT_DIALOG_H

#include <QDialog>

/*储存输入的范围的类*/
class RangeInput {
public:
    float from, to;
    /*简单构造函数*/
    RangeInput (float from, float to) {
        this->from = from;
        this->to = to;
    }
};

namespace Ui {
class RangeInputDialog;
}

/*输入范围窗口*/

class RangeInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RangeInputDialog(QWidget *parent = 0);
    ~RangeInputDialog();
    /*显示前准备*/
    void PrepareShow (QString rangName1, QString rangeName2);
signals:
    /*发送给MainWindow的信号*/
    void sendRange (RangeInput);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::RangeInputDialog *ui;
};

#endif // RANGE_INPUT_DIALOG_H
