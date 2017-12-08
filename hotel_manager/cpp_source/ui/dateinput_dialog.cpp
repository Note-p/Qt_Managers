#include "dateinput_dialog.h"
#include "ui_dateinput_dialog.h"

DateInputDialog::DateInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateInputDialog)
{
    ui->setupUi(this);
    QDateTime dateTime = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(dateTime);
    ui->dateTimeEdit_2->setDateTime(dateTime);
}

DateInputDialog::~DateInputDialog()
{
    delete ui;
}

void DateInputDialog::on_buttonBox_accepted()
{
    DateRange dateRange = (DateRange) malloc(sizeof(struct date_range));
    dateRange->from = ui->dateTimeEdit->dateTime();
    dateRange->to = ui->dateTimeEdit_2->dateTime();
    emit sendDate(dateRange);
}
