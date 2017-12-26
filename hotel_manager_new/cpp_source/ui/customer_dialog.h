#ifndef CUSTOMER_DIALOG_H
#define CUSTOMER_DIALOG_H

#include <QDialog>
#include "../core/database_util.h"

namespace Ui {
class CustomerDialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = 0);
    void bindDatabase(DatabaseUtil database);
    ~CustomerDialog();

signals:
    void refresh();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CustomerDialog *ui;
    DatabaseUtil  database;
};

#endif // CUSTOMER_DIALOG_H
