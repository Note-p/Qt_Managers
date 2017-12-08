#ifndef VEGCODE_INPUT_DIALOG_H
#define VEGCODE_INPUT_DIALOG_H

#include <QDialog>

namespace Ui {
class VegCodeInputDialog;
}

/*输入蔬菜基本信息编号窗口*/

class VegCodeInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VegCodeInputDialog(QWidget *parent = 0);
    ~VegCodeInputDialog();
signals:
    /*发送结果给主窗口*/
    void sendVegCode(int vegCode);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::VegCodeInputDialog *ui;
};

#endif // VEGCODE_INPUT_DIALOG_H
