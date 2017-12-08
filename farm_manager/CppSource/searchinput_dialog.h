#ifndef SEARCHINPUT_DIALOG_H
#define SEARCHINPUT_DIALOG_H

#include <QDialog>

namespace Ui {
class SearchInputDialog;
}

/*输入搜索数据窗口*/

class SearchInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchInputDialog(QWidget *parent = 0);
    ~SearchInputDialog();
    QString searchLabel;
    void prepareShow(void);
signals:
    void sendSearch(QString);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::SearchInputDialog *ui;
};

#endif // SEARCHINPUT_DIALOG_H
