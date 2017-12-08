#include "room_dialog.h"
#include "ui_room_dialog.h"
#include "../core/room.h"
#include "QDateTime"

RoomDialog::RoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomDialog)
{
    ui->setupUi(this);
    ui->discount->setDateTime(QDateTime::currentDateTime());
}

RoomDialog::~RoomDialog()
{
    delete ui;
}

void RoomDialog::bindDatabase(DatabaseUtil database) {
    this->database = database;
}

void RoomDialog::on_buttonBox_accepted()
{
    if (ui->room_type->text().contains("standard")) {
        database.insertRoomData(STANDARDROOM, ui->price->text().toFloat(), 0, "no need");
    }
    else if (ui->room_type->text().contains("business")) {
        database.insertRoomData(BUSINESSSUIT, ui->price->text().toFloat(), 0, "no need");
    }
    else if (ui->room_type->text().contains("hourly")) {
        database.insertRoomData(HOURLYRATEROOM, ui->price->text().toFloat(), 0, "no need");
    }
    else if (ui->room_type->text().contains("discount")) {
        database.insertRoomData(SPECIALDISCOUNTROOM, ui->price->text().toFloat(), 0, "no need",
                                ui->discount->dateTime().toString());
    }
    emit refresh();
}
