#include "edit_room_data.h"
#include "ui_edit_room_data.h"
#include <QDateTime>

EditRoomData::EditRoomData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRoomData)
{
    ui->setupUi(this);
    currentDateTime = QDateTime::currentDateTime();
    ui->discount->setDateTime(currentDateTime);
}

EditRoomData::~EditRoomData()
{
    delete ui;
}

void EditRoomData::bindDatabase(DatabaseUtil database) {
    this->database = database;
}

void EditRoomData::on_buttonBox_accepted()
{
    database.updateRoomData(ui->room_number->text().toInt(),
                            ui->type->text().isEmpty()? -1:ui->type->text().toInt(),
                            ui->price->text().isEmpty()? -1:ui->price->text().toFloat(),
                            ui->usage->isChecked()? 1:0,
                            ui->clean->text().isEmpty()? "null":ui->clean->text(),
                            ui->discount->dateTime() == currentDateTime? "null":ui->discount->dateTime().toString()
                            );
    emit refresh();
}
