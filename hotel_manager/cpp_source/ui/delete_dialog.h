#ifndef DELETE_DIALOG_H
#define DELETE_DIALOG_H

#include <QDialog>
#include "../core/database_util.h"


namespace Ui {
class DeleteDialog;
}

enum delete_type {
    DELETECUSTOMER, DELETEROOM
};

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = 0);
    ~DeleteDialog();

    void bindDeleteType(int type, DatabaseUtil database);

signals:
    void refresh();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeleteDialog *ui;

    int type;
    DatabaseUtil database;
};

#endif // DELETE_DIALOG_H
