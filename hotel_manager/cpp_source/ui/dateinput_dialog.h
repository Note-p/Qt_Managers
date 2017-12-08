#ifndef DATEINPUT_DIALOG_H
#define DATEINPUT_DIALOG_H

#include <QDialog>
#include <QDateTime>

typedef struct date_range {
    QDateTime from;
    QDateTime to;
}*DateRange;

namespace Ui {
class DateInputDialog;
}

class DateInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateInputDialog(QWidget *parent = 0);
    ~DateInputDialog();

signals:
    void sendDate(DateRange dateRange);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DateInputDialog *ui;
};

#endif // DATEINPUT_DIALOG_H
