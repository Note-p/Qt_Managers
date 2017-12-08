#include "range_input_dialog.h"
#include "ui_range_input_dialog.h"

RangeInputDialog::RangeInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RangeInputDialog)
{
    ui->setupUi(this);
}

RangeInputDialog::~RangeInputDialog()
{
    delete ui;
}

void RangeInputDialog::PrepareShow(QString rangName1, QString rangeName2) {
    /*显示前调用，配置两个范围名称*/
    ui->label->setText(rangName1);
    ui->label_2->setText(rangeName2);
}

void RangeInputDialog::on_buttonBox_accepted()
{
    float num1 = ui->lineEdit->text().toFloat();
    float num2 = ui->lineEdit_2->text().toFloat();
    /*根据大小新建范围对象*/
    RangeInput range = RangeInput(num1 < num2 ? num1:num2, num1 < num2 ? num2:num1);
    /*发送范围信号*/
    emit sendRange(range);
}
