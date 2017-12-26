#ifndef ROOM_DIALOG_H
#define ROOM_DIALOG_H

#include <QDialog>
#include "../core/database_util.h"

namespace Ui {
class RoomDialog;
}

class RoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoomDialog(QWidget *parent = 0);
    ~RoomDialog();

    void bindDatabase (DatabaseUtil database);

signals:
    void refresh();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RoomDialog *ui;
    DatabaseUtil database;
};

#endif // ROOM_DIALOG_H
