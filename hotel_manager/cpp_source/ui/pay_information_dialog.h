#ifndef PAY_INFORMATION_DIALOG_H
#define PAY_INFORMATION_DIALOG_H

#include <QDialog>
#include "../core/room.h"
#include "../core/customer.h"
#include "../core/database_util.h"

namespace Ui {
class PayInformationDialog;
}

class PayInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PayInformationDialog(QWidget *parent = 0);
    ~PayInformationDialog();

    void bind(Room* room, Customer* customer, DatabaseUtil database);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PayInformationDialog *ui;

    DatabaseUtil database;
    Room* room;
    Customer* customer;

    float price;
};

#endif // PAY_INFORMATION_DIALOG_H
