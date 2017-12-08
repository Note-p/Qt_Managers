#include "main_window.h"
#include "ui_main_window.h"
#include "../core/database_util.h"
#include "../core/room.h"
#include <QDebug>
#include <QStandardItem>
#include "customer_dialog.h"
#include "room_dialog.h"
#include "edit_room_data.h"
#include "edit_customerdata_dialog.h"
#include "delete_dialog.h"
#include "number_input_dialog.h"
#include "pay_information_dialog.h"
#include "vip_checkin_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    database = DatabaseUtil();
    currentTable = ROOMTABLE;
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showRoomTable(RoomList* roomList) {
    currentTable = ROOMTABLE;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, QString("number"));
    model->setHeaderData(1, Qt::Horizontal, QString("type"));
    model->setHeaderData(2, Qt::Horizontal, QString("price"));
    model->setHeaderData(3, Qt::Horizontal, QString("usage"));
    model->setHeaderData(4, Qt::Horizontal, QString("clean situation"));
    model->setHeaderData(5, Qt::Horizontal, QString("addiction"));
    ui->tableView->setModel(model);
    if (roomList == NULL) {
        return ;
    }
    Room* room = roomList->get(true);
    for (int i = 0; room != NULL; room = roomList->get(), i++) {
        model->setItem(i, 0, new QStandardItem(QString::number(room->roomNumber)));
        model->setItem(i, 1, new QStandardItem(getRoomTypeName(room->roomType)));
        model->setItem(i, 2, new QStandardItem(QString::number(room->price)));
        model->setItem(i, 3, new QStandardItem(QString(room->usage == 0? "no":"yes")));
        model->setItem(i, 4, new QStandardItem(room->cleanSituation));
        model->setItem(i, 5, new QStandardItem(room->addiction));
        for (int j = 0; j < 6; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableView->resizeColumnsToContents();
    ui->statusbar->showMessage(QString("Room list load compelete, number = %1").arg(roomList->size));
}

void MainWindow::showCustomerTable(CustomerList *customerList) {
    currentTable = CUSTOMERTABLE;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(11);
    model->setHeaderData(0, Qt::Horizontal, QString("ID"));
    model->setHeaderData(1, Qt::Horizontal, QString("type"));
    model->setHeaderData(2, Qt::Horizontal, QString("user name"));
    model->setHeaderData(3, Qt::Horizontal, QString("phone number"));
    model->setHeaderData(4, Qt::Horizontal, QString("room number"));
    model->setHeaderData(5, Qt::Horizontal, QString("check in time"));
    model->setHeaderData(6, Qt::Horizontal, QString("check out time"));
    model->setHeaderData(7, Qt::Horizontal, QString("schedule time"));
    model->setHeaderData(8, Qt::Horizontal, QString("vip number"));
    model->setHeaderData(9, Qt::Horizontal, QString("point"));
    model->setHeaderData(10, Qt::Horizontal, QString("deposit"));
    ui->tableView->setModel(model);
    if (customerList == NULL) {
        return ;
    }
    Customer* customer = customerList->get(true);
    for (int i = 0; customer != NULL; customer = customerList->get(), i++) {
        model->setItem(i, 0, new QStandardItem(QString::number(customer->customerID)));
        model->setItem(i, 1, new QStandardItem(getCustomerTypeName(customer->customerType)));
        model->setItem(i, 2, new QStandardItem(QString(customer->userName)));
        model->setItem(i, 3, new QStandardItem(QString(customer->phone)));
        model->setItem(i, 4, new QStandardItem(QString(customer->roomNumber)));
        model->setItem(i, 5, new QStandardItem(customer->checkInTime));
        model->setItem(i, 6, new QStandardItem(customer->checkOutTime));
        model->setItem(i, 7, new QStandardItem(customer->scheduleTime));
        model->setItem(i, 8, new QStandardItem(customer->vipNumber));
        model->setItem(i, 9, new QStandardItem(QString::number(customer->point)));
        model->setItem(i, 10, new QStandardItem(QString::number(customer->deposit)));
        for (int j = 0; j < 11; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableView->resizeColumnsToContents();
    ui->statusbar->showMessage(QString("Customer list load compelete, number = %1").arg(customerList->size));
}

void MainWindow::showAllTable(RoomList *roomList) {
    currentTable = ALLTABLE;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(16);
    model->setHeaderData(0, Qt::Horizontal, QString("number"));
    model->setHeaderData(1, Qt::Horizontal, QString("type"));
    model->setHeaderData(2, Qt::Horizontal, QString("price"));
    model->setHeaderData(3, Qt::Horizontal, QString("usage"));
    model->setHeaderData(4, Qt::Horizontal, QString("clean situation"));
    model->setHeaderData(5, Qt::Horizontal, QString("addiction"));
    /* customer info */
    model->setHeaderData(6, Qt::Horizontal, QString("customer ID"));
    model->setHeaderData(7, Qt::Horizontal, QString("type"));
    model->setHeaderData(8, Qt::Horizontal, QString("user name"));
    model->setHeaderData(9, Qt::Horizontal, QString("phone number"));
    model->setHeaderData(10, Qt::Horizontal, QString("check in time"));
    model->setHeaderData(11, Qt::Horizontal, QString("check out time"));
    model->setHeaderData(12, Qt::Horizontal, QString("schedule time"));
    model->setHeaderData(13, Qt::Horizontal, QString("vip number"));
    model->setHeaderData(14, Qt::Horizontal, QString("point"));
    model->setHeaderData(15, Qt::Horizontal, QString("deposit"));

    ui->tableView->setModel(model);
    if (roomList == NULL) {
        return ;
    }
    Room* room = roomList->get(true);
    for (int i = 0; room != NULL; room = roomList->get(), i++) {
        model->setItem(i, 0, new QStandardItem(QString::number(room->roomNumber)));
        model->setItem(i, 1, new QStandardItem(getRoomTypeName(room->roomType)));
        model->setItem(i, 2, new QStandardItem(QString::number(room->price)));
        model->setItem(i, 3, new QStandardItem(QString(room->usage == 0? "no":"yes")));
        model->setItem(i, 4, new QStandardItem(room->cleanSituation));
        model->setItem(i, 5, new QStandardItem(room->addiction));

        /* get customer data */
        Customer* customer = database.getCustomerDataByRoom(room->roomNumber);
        if (customer != NULL) {
            model->setItem(i, 6, new QStandardItem(QString::number(customer->customerID)));
            model->setItem(i, 7, new QStandardItem(getCustomerTypeName(customer->customerType)));
            model->setItem(i, 8, new QStandardItem(QString(customer->userName)));
            model->setItem(i, 9, new QStandardItem(QString(customer->phone)));
            model->setItem(i, 10, new QStandardItem(customer->checkInTime));
            model->setItem(i, 11, new QStandardItem(customer->checkOutTime));
            model->setItem(i, 12, new QStandardItem(customer->scheduleTime));
            model->setItem(i, 13, new QStandardItem(customer->vipNumber));
            model->setItem(i, 14, new QStandardItem(QString::number(customer->point)));
            model->setItem(i, 15, new QStandardItem(QString::number(customer->deposit)));
        }

        else {
            model->setItem(i, 6, new QStandardItem(QString("")));
            model->setItem(i, 7, new QStandardItem(QString("")));
            model->setItem(i, 8, new QStandardItem(QString("")));
            model->setItem(i, 9, new QStandardItem(QString("")));
            model->setItem(i, 10, new QStandardItem(QString("")));
            model->setItem(i, 11, new QStandardItem(QString("")));
            model->setItem(i, 12, new QStandardItem(QString("")));
            model->setItem(i, 13, new QStandardItem(QString("")));
            model->setItem(i, 14, new QStandardItem(QString("")));
            model->setItem(i, 15, new QStandardItem(QString("")));

        }

        for (int j = 0; j < 16; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableView->resizeColumnsToContents();
    ui->statusbar->showMessage(QString("Room list load compelete, number = %1").arg(roomList->size));
}

void MainWindow::refresh() {
    switch (currentTable) {
    case ROOMTABLE: {
        RoomList* list = database.getRoomDataList();
        showRoomTable(!list? NULL:list->sort());
        break;
    }
    case CUSTOMERTABLE: {
        CustomerList* list = database.getCustomerDataList();
        showCustomerTable(list? list->sort(CSORTBYID):NULL);
        break;
    }
    case ALLTABLE: {
        RoomList* list = database.getRoomDataList();
        showAllTable(!list? NULL:list->sort());
        break;
    }
    default:
        break;
    }
}


void MainWindow::checkOutHandler(int number) {
    Customer* customer = database.getCustomerData(number);
    if (!customer)
        return ;
    Room* room = database.getRoomData(customer->roomNumber.toInt());
    if (!room)
        return;
    PayInformationDialog* dlg = new PayInformationDialog(this);
    dlg->bind(room, customer, database);
    dlg->show();
}

void MainWindow::dateRangeHandler(DateRange dateRange) {

    RoomList* roomList = database.getRoomDataList();
    RoomListStruct current = roomList->getHead();
    RoomListStruct prev = current;
    current = current->next;
    while (current != NULL) {
        Customer* customer = database.getCustomerDataByRoom
                (current->room->roomNumber);
        if (customer != NULL) {
            /* if the room in this time range has person living, delete it */
            if (!((QDateTime::fromString(customer->checkInTime) > dateRange->from &&
                   QDateTime::fromString(customer->checkInTime) > dateRange->to) ||
                  (QDateTime::fromString(customer->checkOutTime) < dateRange->to &&
                   QDateTime::fromString(customer->checkOutTime) > dateRange->from)
                    )) {
                prev->next = current->next;
                free(current);
                current = prev->next;
                continue;
            }
        }
        prev = current;
        current = current->next;
    }
    showRoomTable(roomList);
}

void MainWindow::on_actionadd_customer_triggered()
{
    CustomerDialog *dlg = new CustomerDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDatabase(database);
    dlg->show();
}

void MainWindow::on_actionshow_customer_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYID):NULL);
}

void MainWindow::on_actionshow_room_triggered()
{
    RoomList* list = database.getRoomDataList();
    showRoomTable(!list? NULL:list->sort());
}

void MainWindow::on_actionadd_room_triggered()
{
    RoomDialog *dlg = new RoomDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDatabase(database);
    dlg->show();
}

void MainWindow::on_actionordinary_customer_triggered()
{
    CustomerDialog *dlg = new CustomerDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDatabase(database);
    dlg->show();
}

void MainWindow::on_actionedit_room_triggered()
{
    EditRoomData *dlg = new EditRoomData(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDatabase(database);
    dlg->show();
}

void MainWindow::on_actionedit_customer_triggered()
{
    EditCustomerDataDialog *dlg = new EditCustomerDataDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDatabase(database);
    dlg->show();
}

void MainWindow::on_actionby_number_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYID):NULL);
}

void MainWindow::on_actionby_name_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYNAME):NULL);
}

void MainWindow::on_actionby_type_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYTYPE):NULL);
}

void MainWindow::on_actionby_check_in_time_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYCHECKIN):NULL);
}

void MainWindow::on_actionby_check_out_time_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYCHECKOUT):NULL);
}

void MainWindow::on_actionby_point_triggered()
{
    CustomerList* list = database.getCustomerDataList();
    showCustomerTable(list? list->sort(CSORTBYPOINT):NULL);
}

void MainWindow::on_actiondelete_customer_triggered()
{
    DeleteDialog *dlg = new DeleteDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDeleteType(DELETECUSTOMER, database);
    dlg->show();
}

void MainWindow::on_actiondelete_room_triggered()
{
    DeleteDialog *dlg = new DeleteDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDeleteType(DELETEROOM, database);
    dlg->show();
}

void MainWindow::on_actionby_number_2_triggered()
{
    RoomList* list = database.getRoomDataList();
    showRoomTable(!list? NULL:list->sort());
}

void MainWindow::on_actionby_type_2_triggered()
{
    RoomList* list = database.getRoomDataList();
    showRoomTable(!list? NULL:list->sort(RSORTTYPE));
}

void MainWindow::on_actionby_price_triggered()
{
    RoomList* list = database.getRoomDataList();
    showRoomTable(!list? NULL:list->sort(RSORTPRICE));
}

void MainWindow::on_actionby_usage_triggered()
{
    RoomList* list = database.getRoomDataList();
    showRoomTable(!list? NULL:list->sort(RSORTUSAGE));
}

void MainWindow::on_actionby_clean_situation_triggered()
{
    RoomList* list = database.getRoomDataList();
    showRoomTable(!list? NULL:list->sort(RSORTCLEAN));
}

void MainWindow::on_action_triggered()
{
    NumberInputDialog* dlg = new NumberInputDialog(this);
    connect(dlg, SIGNAL(sendNumber(int)), this, SLOT(checkOutHandler(int)));
    dlg->bind(database);
    dlg->show();
}



void MainWindow::on_actionVIP_SVIP_triggered()
{
    VipCheckInDialog *dlg = new VipCheckInDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bind(database);
    dlg->show();
}

void MainWindow::on_actionordinary_triggered()
{
    CustomerDialog *dlg = new CustomerDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bindDatabase(database);
    dlg->show();
}

void MainWindow::on_actionVIP_SVIP_2_triggered()
{
    VipCheckInDialog *dlg = new VipCheckInDialog(this);
    connect(dlg, SIGNAL(refresh()), this, SLOT(refresh()));
    dlg->bind(database);
    dlg->show();
}

void MainWindow::on_actionshow_available_room_triggered()
{
    DateInputDialog* dlg = new DateInputDialog(this);
    connect(dlg, SIGNAL(sendDate(DateRange)), this, SLOT(dateRangeHandler(DateRange)));
    dlg->show();
}

void MainWindow::on_actionshow_all_triggered()
{
    RoomList* list = database.getRoomDataList();
    showAllTable(!list? NULL:list->sort());
}
