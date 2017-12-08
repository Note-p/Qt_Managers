#ifndef SEARCH2_INPUT_DIALOG_H
#define SEARCH2_INPUT_DIALOG_H

#include <QDialog>


/*双项搜索数据类--存储数据而已*/
class searchData {
public:
    QString data1, data2;
    searchData(QString data1, QString data2) {
        this->data1 = data1;
        this->data2 = data2;
    }
};


namespace Ui {
class Search2InputDialog;
}

/*双项搜索窗口*/

class Search2InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Search2InputDialog(QWidget *parent = 0);
    ~Search2InputDialog();
    /*显示前调用*/
    void PrepareShow (QString labelOne, QString labelTwo);

signals:
    /*发送数据给主窗口*/
    void sendSearchData (searchData data);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Search2InputDialog *ui;
};

#endif // SEARCH2_INPUT_DIALOG_H
