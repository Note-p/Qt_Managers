#ifndef VIP_CHECKIN_DIALOG_H
#define VIP_CHECKIN_DIALOG_H

#include <QDialog>
#include "../core/database_util.h"

namespace Ui {
class VipCheckInDialog;
}

class VipCheckInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VipCheckInDialog(QWidget *parent = 0);
    ~VipCheckInDialog();

    void bind (DatabaseUtil database);

signals:
    void refresh();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VipCheckInDialog *ui;

    DatabaseUtil database;

};

#endif // VIP_CHECKIN_DIALOG_H
