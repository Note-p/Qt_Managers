#ifndef EDIT_ROOM_DATA_H
#define EDIT_ROOM_DATA_H

#include <QDialog>
#include "../core/database_util.h"
#include <QDateTime>

namespace Ui {
class EditRoomData;
}

class EditRoomData : public QDialog
{
    Q_OBJECT

public:
    explicit EditRoomData(QWidget *parent = 0);
    ~EditRoomData();

    void bindDatabase(DatabaseUtil database);

signals:
    void refresh();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditRoomData *ui;

    DatabaseUtil database;
    QDateTime currentDateTime;
};

#endif // EDIT_ROOM_DATA_H
