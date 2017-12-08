#ifndef NOTFOUNDDIALOG_H
#define NOTFOUNDDIALOG_H

#include <QDialog>

/*未找到窗口 -- 没有任何东西，就是显示*/


namespace Ui {
class NotFoundDialog;
}

class NotFoundDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotFoundDialog(QWidget *parent = 0);
    ~NotFoundDialog();

private:
    Ui::NotFoundDialog *ui;
};

#endif // NOTFOUNDDIALOG_H
