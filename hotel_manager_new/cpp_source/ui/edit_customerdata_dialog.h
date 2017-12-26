#ifndef EDIT_CUSTOMERDATA_DIALOG_H
#define EDIT_CUSTOMERDATA_DIALOG_H

#include <QDialog>
#include "../core/database_util.h"
#include <QDateTime>

namespace Ui {
class EditCustomerDataDialog;
}

class EditCustomerDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditCustomerDataDialog(QWidget *parent = 0);
    ~EditCustomerDataDialog();

    void bindDatabase(DatabaseUtil database);

signals:
    void refresh();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditCustomerDataDialog *ui;
    DatabaseUtil database;

    QDateTime currentDateTime;
};

#endif // EDIT_CUSTOMERDATA_DIALOG_H
