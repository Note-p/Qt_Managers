#include "database_util.h"
#include <QFile>

DatabaseUtil::DatabaseUtil()
{
    // check database, if not exist, creat
    if (QSqlDatabase::contains(ROOM_DATABASE_NAME)) {
        roomDatabase = QSqlDatabase::database(ROOM_DATABASE_NAME);
    }
    else {
        roomDatabase = QSqlDatabase::addDatabase("QSQLITE", ROOM_DATABASE_NAME);
        roomDatabase.setDatabaseName(ROOM_DATABASE_FILE);
        roomDatabase.setUserName(DATABASE_USERNAME);
        roomDatabase.setPassword(DATABASE_PASSWORD);
        roomDatabase.open();
        // create table
        QSqlQuery roomSqlQuery(roomDatabase);
        roomSqlQuery.exec("create table standard (id int primary key, price float, "
                          "usage int, clean_situation varchar(20))");
        roomSqlQuery.exec("create table business (id int primary key, price float, "
                          "usage int, clean_situation varchar(20))");
        roomSqlQuery.exec("create table hourly (id int primary key, price float, "
                          "usage int, clean_situation varchar(20))");
        roomSqlQuery.exec("create table discount (id int primary key, price float, "
                          "usage int, clean_situation varchar(20), discount_time varchar(20))");
        roomDatabase.close();
    }
    if (!roomDatabase.open()) {
        qDebug() << "Error: failed to connect to database." << roomDatabase.lastError();
    }

    if (QSqlDatabase::contains(CUSTOMER_DATABASE_NAME)) {
        customerDatabase = QSqlDatabase::database(CUSTOMER_DATABASE_NAME);
    }
    else {
        customerDatabase = QSqlDatabase::addDatabase("QSQLITE", CUSTOMER_DATABASE_NAME);
        customerDatabase.setDatabaseName(CUSTOMER_DATABASE_FILE);
        customerDatabase.setUserName(DATABASE_USERNAME);
        customerDatabase.setPassword(DATABASE_PASSWORD);
        customerDatabase.open();
        // create table
        QSqlQuery customerSqlQuery(customerDatabase);
        customerSqlQuery.exec("create table ordinary (id int primary key, user_name varchar(20), "
                          "phone varchar(20), check_in_time varchar(50), check_out_time varchar(50),"
                          "schedule_time varchar(100), room varchar(10))");
        customerSqlQuery.exec("create table vip (id int primary key, user_name varchar(20), "
                          "phone varchar(20), check_in_time varchar(50), check_out_time varchar(50),"
                          "schedule_time varchar(100), room varchar(10), vip_number varchar(20), points int)");
        customerSqlQuery.exec("create table svip (id int primary key, user_name varchar(20), "
                          "phone varchar(20), check_in_time varchar(50), check_out_time varchar(50),"
                          "schedule_time varchar(100), room varchar(10), vip_number varchar(20), point int,"
                          "deposit float)");
        customerDatabase.close();
    }
    if (!customerDatabase.open()) {
        qDebug() << "Error: failed to connect to database." << customerDatabase.lastError();
    }
}

bool DatabaseUtil::insertRoomData(int roomType, float price, int usage,
                                  QString clean, QString discount_time, int roomID) {
    QSqlQuery roomSqlQuery(roomDatabase);
    // get max id from all tables
    int max_id = roomID == -1? getMaxRoomID():roomID - 1;
    switch (roomType) {
    case STANDARDROOM:
        roomSqlQuery.prepare("insert into standard values(?, ?, ?, ?)");
        roomSqlQuery.addBindValue(max_id + 1);
        roomSqlQuery.addBindValue(price);
        roomSqlQuery.addBindValue(usage);
        roomSqlQuery.addBindValue(clean);
        break;
    case BUSINESSSUIT:
        roomSqlQuery.prepare("insert into business values(?, ?, ?, ?)");
        roomSqlQuery.addBindValue(max_id + 1);
        roomSqlQuery.addBindValue(price);
        roomSqlQuery.addBindValue(usage);
        roomSqlQuery.addBindValue(clean);
        break;
    case HOURLYRATEROOM:
        roomSqlQuery.prepare("insert into hourly values(?, ?, ?, ?)");
        roomSqlQuery.addBindValue(max_id + 1);
        roomSqlQuery.addBindValue(price);
        roomSqlQuery.addBindValue(usage);
        roomSqlQuery.addBindValue(clean);
        break;
    case SPECIALDISCOUNTROOM:
        roomSqlQuery.prepare("insert into discount values(?, ?, ?, ?, ?)");
        roomSqlQuery.addBindValue(max_id + 1);
        roomSqlQuery.addBindValue(price);
        roomSqlQuery.addBindValue(usage);
        roomSqlQuery.addBindValue(clean);
        roomSqlQuery.addBindValue(discount_time);
        break;
    default:
        return false;
    }

    if (!roomSqlQuery.exec()) {
        qDebug() << "ERROR" << roomSqlQuery.lastError();
        return false;
    }
    return true;
}

int DatabaseUtil::getMaxRoomID() {
    QSqlQuery roomSqlQuery(roomDatabase);
    // get max id from all tables
    int max_id = 0;
    roomSqlQuery.exec("select max(id) from standard");
    while (roomSqlQuery.next()) {
        max_id = roomSqlQuery.value(0).toInt();
    }
    // room two
    roomSqlQuery.exec("select max(id) from business");
    while (roomSqlQuery.next()) {
        int id = roomSqlQuery.value(0).toInt();
        max_id = max_id < id ? id:max_id;
    }
    // room three
    roomSqlQuery.exec("select max(id) from hourly");
    while (roomSqlQuery.next()) {
        int id = roomSqlQuery.value(0).toInt();
        max_id = max_id < id ? id:max_id;
    }
    // room four
    roomSqlQuery.exec("select max(id) from discount");
    while (roomSqlQuery.next()) {
        int id = roomSqlQuery.value(0).toInt();
        max_id = max_id < id ? id:max_id;
    }
    return max_id;
}

Room* DatabaseUtil::getRoomData(int roomId) {
    QSqlQuery roomSqlQuery(roomDatabase);
    // standard
    QString str = QString("select * from standard where id = %1").arg(roomId);
    roomSqlQuery.exec(str);
    while (roomSqlQuery.next()) {
        return new StandardRoom(STANDARDROOM, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                    roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString());
    }

    // business
    str = QString("select * from business where id = %1").arg(roomId);
    roomSqlQuery.exec(str);
    while (roomSqlQuery.next()) {
        return new BusinessRoom(BUSINESSSUIT, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                    roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString());
    }

    // hourly
    str = QString("select * from hourly where id = %1").arg(roomId);
    roomSqlQuery.exec(str);
    while (roomSqlQuery.next()) {
        return new HourlyRateRoom(HOURLYRATEROOM, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                    roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString());
    }

    // discount
    str = QString("select * from discount where id = %1").arg(roomId);
    roomSqlQuery.exec(str);
    while (roomSqlQuery.next()) {
        return new SpecialDiscountRoom(SPECIALDISCOUNTROOM, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                    roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString(), roomSqlQuery.value(4).toString());
    }

    return NULL;
}

void DatabaseUtil::deleteRoomData(int roomId) {
    QSqlQuery roomSqlQuery(roomDatabase);
    // standard
    roomSqlQuery.prepare("delete from standard where id = ?");
    roomSqlQuery.addBindValue(roomId);
    if (roomSqlQuery.exec()) {
        //return true;
    }

    // business
    roomSqlQuery.prepare("delete from business where id = ?");
    roomSqlQuery.addBindValue(roomId);
    if (roomSqlQuery.exec()) {
        //return true;
    }

    // hourly
    roomSqlQuery.prepare("delete from hourly where id = ?");
    roomSqlQuery.addBindValue(roomId);
    if (roomSqlQuery.exec()) {
        //return true;
    }

    // discount
    roomSqlQuery.prepare("delete from discount where id = ?");
    roomSqlQuery.addBindValue(roomId);
    if (roomSqlQuery.exec()) {
        //return true;
    }
    qDebug() << "not found";
    //return false;
}

RoomList* DatabaseUtil::getRoomDataList() {
    QSqlQuery roomSqlQuery(roomDatabase);
    RoomList* roomList = new RoomList();
    // standard
    roomSqlQuery.exec("select * from standard");
    while (roomSqlQuery.next()) {
        Room* room = new StandardRoom(STANDARDROOM, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                              roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString());
        roomList->add(room);
    }

    // business
    roomSqlQuery.exec("select * from business");
    while (roomSqlQuery.next()) {
        Room* room = new BusinessRoom(BUSINESSSUIT, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                              roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString());
        roomList->add(room);
    }

    // hourly
    roomSqlQuery.exec("select * from hourly");
    while (roomSqlQuery.next()) {
        Room* room = new HourlyRateRoom(HOURLYRATEROOM, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                              roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString());
        roomList->add(room);
    }

    // discount
    roomSqlQuery.exec("select * from discount");
    while (roomSqlQuery.next()) {
        Room* room = new SpecialDiscountRoom(SPECIALDISCOUNTROOM, roomSqlQuery.value(0).toInt(), roomSqlQuery.value(1).toFloat(),
                              roomSqlQuery.value(2).toInt(), roomSqlQuery.value(3).toString(), roomSqlQuery.value(4).toString());
        roomList->add(room);
    }
    return roomList;
}


bool DatabaseUtil::insertCustomerData(int customerType, QString userName, QString phone,
                                      QString checkInTime, QString checkOutTime,
                                      QString scheduleTime, QString vipNumber,
                                      int point, float deposit, int customerID, QString roomNumber) {
    QSqlQuery customerSqlQuery(customerDatabase);
    // get max id from all tables
    int max_id = customerID == -1? getMaxCustomerID():customerID - 1;
    switch (customerType) {
    case ORDINARY:
        customerSqlQuery.prepare("insert into ordinary values(?, ?, ?, ?, ?, ?, ?)");
        customerSqlQuery.addBindValue(max_id + 1);
        customerSqlQuery.addBindValue(userName);
        customerSqlQuery.addBindValue(phone);
        customerSqlQuery.addBindValue(checkInTime);
        customerSqlQuery.addBindValue(checkOutTime);
        customerSqlQuery.addBindValue(scheduleTime);
        customerSqlQuery.addBindValue(roomNumber);
        break;
    case VIP:
        customerSqlQuery.prepare("insert into vip values(?, ?, ?, ?, ?, ?, ?, ?, ?)");
        customerSqlQuery.addBindValue(max_id + 1);
        customerSqlQuery.addBindValue(userName);
        customerSqlQuery.addBindValue(phone);
        customerSqlQuery.addBindValue(checkInTime);
        customerSqlQuery.addBindValue(checkOutTime);
        customerSqlQuery.addBindValue(scheduleTime);
        customerSqlQuery.addBindValue(roomNumber);
        customerSqlQuery.addBindValue(vipNumber);
        customerSqlQuery.addBindValue(point);

        break;
    case SVIP:
        customerSqlQuery.prepare("insert into svip values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        customerSqlQuery.addBindValue(max_id + 1);
        customerSqlQuery.addBindValue(userName);
        customerSqlQuery.addBindValue(phone);
        customerSqlQuery.addBindValue(checkInTime);
        customerSqlQuery.addBindValue(checkOutTime);
        customerSqlQuery.addBindValue(scheduleTime);
        customerSqlQuery.addBindValue(roomNumber);
        customerSqlQuery.addBindValue(vipNumber);
        customerSqlQuery.addBindValue(point);
        customerSqlQuery.addBindValue(deposit);
        break;
    default:
        return false;
    }

    if (!customerSqlQuery.exec()) {
        qDebug() << "ERROR" << customerSqlQuery.lastError();
        return false;
    }
    return true;
}

int DatabaseUtil::getMaxCustomerID() {
    QSqlQuery customerSqlQuery(customerDatabase);
    // get max id from all tables
    int max_id = 0;
    customerSqlQuery.exec("select max(id) from ordinary");
    while (customerSqlQuery.next()) {
        max_id = customerSqlQuery.value(0).toInt();
    }
    // customer two
    customerSqlQuery.exec("select max(id) from vip");
    while (customerSqlQuery.next()) {
        int id = customerSqlQuery.value(0).toInt();
        max_id = max_id < id ? id:max_id;
    }
    // customer three
    customerSqlQuery.exec("select max(id) from svip");
    while (customerSqlQuery.next()) {
        int id = customerSqlQuery.value(0).toInt();
        max_id = max_id < id ? id:max_id;
    }
    return max_id;
}

Customer* DatabaseUtil::getCustomerData(int customerId) {
    QSqlQuery customerSqlQuery(customerDatabase);
    // ordinary
    QString str = QString("select * from ordinary where id = %1").arg(customerId);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new OrdinaryCustomer(ORDINARY, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString());
    }

    // vip
    str = QString("select * from vip where id = %1").arg(customerId);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new VIPCustomer(VIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                            customerSqlQuery.value(8).toInt()
                            );
    }

    // svip
    str = QString("select * from svip where id = %1").arg(customerId);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new SVIPCustomer(SVIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                            customerSqlQuery.value(8).toInt(), customerSqlQuery.value(9).toFloat()
                            );
    }

    return NULL;
}


Customer* DatabaseUtil::getCustomerDataByRoom(int roomID) {
    QSqlQuery customerSqlQuery(customerDatabase);
    // ordinary
    QString str = QString("select * from ordinary where room = %1").arg(roomID);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new OrdinaryCustomer(ORDINARY, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString());
    }

    // vip
    str = QString("select * from vip where room = %1").arg(roomID);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new VIPCustomer(VIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                            customerSqlQuery.value(8).toInt()
                            );
    }

    // svip
    str = QString("select * from svip where room = %1").arg(roomID);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new SVIPCustomer(SVIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                            customerSqlQuery.value(8).toInt(), customerSqlQuery.value(9).toFloat()
                            );
    }

    return NULL;
}


void DatabaseUtil::deleteCustomerData(int customerId) {
    QSqlQuery customerSqlQuery(customerDatabase);
    // ordinary
    customerSqlQuery.prepare("delete from ordinary where id = ?");
    customerSqlQuery.addBindValue(customerId);
    if (customerSqlQuery.exec()) {
        //return true;
    }

    // vip
    customerSqlQuery.prepare("delete from vip where id = ?");
    customerSqlQuery.addBindValue(customerId);
    if (customerSqlQuery.exec()) {
        //return true;
    }

    // svip
    customerSqlQuery.prepare("delete from svip where id = ?");
    customerSqlQuery.addBindValue(customerId);
    if (customerSqlQuery.exec()) {
        //return true;
    }

    //return false;
}

CustomerList* DatabaseUtil::getCustomerDataList() {
    QSqlQuery customerSqlQuery(customerDatabase);
    CustomerList* customerList = new CustomerList();
    // ordinary
    customerSqlQuery.exec("select * from ordinary");
    while (customerSqlQuery.next()) {
        Customer *customer = new OrdinaryCustomer(ORDINARY, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                                          customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                                          customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                                          customerSqlQuery.value(6).toString());
        customerList->add(customer);
    }

    // vip
    customerSqlQuery.exec("select * from vip");
    while (customerSqlQuery.next()) {
        Customer *customer = new VIPCustomer(VIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                                          customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                                          customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                                          customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                                          customerSqlQuery.value(8).toInt()
                                          );
        customerList->add(customer);
    }

    // svip
    customerSqlQuery.exec("select * from svip");
    while (customerSqlQuery.next()) {
        Customer *customer = new SVIPCustomer(SVIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                                          customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                                          customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                                          customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                                          customerSqlQuery.value(8).toInt(), customerSqlQuery.value(9).toFloat()
                                          );
        customerList->add(customer);
    }


    return customerList;
}


bool DatabaseUtil::insertRoomData(Room* room) {
    return insertRoomData(room->roomType, room->price, room->usage,
                   room->cleanSituation, room->addiction, room->roomNumber);
}

void DatabaseUtil::updateRoomData(int roomID, int roomType, float price,
                                  int usage, QString clean, QString addiction) {
    // to be simple, just get room then delete it then insert a new room with the same id
    Room* room = getRoomData(roomID);
    deleteRoomData(roomID);
    if (roomType != -1) {
        room->roomType = roomType;
    }
    if (price != -1) {
        room->price = price;
    }
    if (usage != -1) {
        room->usage = usage;
    }
    if (clean != "null") {
        room->cleanSituation = clean;
    }
    if (addiction != "null" && room->roomType == SPECIALDISCOUNTROOM) {
        room->addiction = addiction;
    }
    insertRoomData(room);
}


bool DatabaseUtil::insertCustomerData(Customer *customer) {
    return insertCustomerData(customer->customerType, customer->userName, customer->phone,
                       customer->checkInTime, customer->checkOutTime, customer->scheduleTime,
                       customer->vipNumber, customer->point, customer->deposit, customer->customerID, customer->roomNumber);
}


void DatabaseUtil::updateCustomerData(int customerID, int customerType, QString userName,
                                      QString phone, QString checkInTime, QString checkOutTime,
                                      QString scheduleTime, QString vipNumber, int point,
                                      float deposit, QString roomNumber) {
    Customer* customer = getCustomerData(customerID);
    deleteCustomerData(customerID);
    if (customerType != -1) {
        customer->customerType = customerType;
    }
    if (userName != NULL) {
        customer->userName = userName;
    }
    if (phone != NULL) {
        customer->phone = phone;
    }
    if (checkInTime != NULL) {
        customer->checkInTime = checkInTime;
    }
    if (checkOutTime != NULL) {
        customer->checkOutTime = checkOutTime;
    }
    if (scheduleTime != NULL) {
        customer->scheduleTime = scheduleTime;
    }
    if (vipNumber != NULL) {
        customer->vipNumber = vipNumber;
    }
    if (point != -1) {
        customer->point = point;
    }
    if (deposit != -1) {
        customer->deposit = deposit;
    }
    if (roomNumber != NULL) {
        customer->roomNumber = roomNumber;
    }
    insertCustomerData(customer);
}


Customer* DatabaseUtil::getCustomerDataByVIP(int vipNumber) {
    QSqlQuery customerSqlQuery(customerDatabase);
    // ordinary
    QString str = QString("select * from ordinary where vip_number = %1").arg(vipNumber);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new OrdinaryCustomer(ORDINARY, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString());
    }

    // vip
    str = QString("select * from vip where vip_number = %1").arg(vipNumber);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new VIPCustomer(VIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                            customerSqlQuery.value(8).toInt()
                            );
    }

    // svip
    str = QString("select * from svip where vip_number = %1").arg(vipNumber);
    customerSqlQuery.exec(str);
    while (customerSqlQuery.next()) {
        return new SVIPCustomer(SVIP, customerSqlQuery.value(0).toInt(), customerSqlQuery.value(1).toString(),
                            customerSqlQuery.value(2).toString(), customerSqlQuery.value(3).toString(),
                            customerSqlQuery.value(4).toString(), customerSqlQuery.value(5).toString(),
                            customerSqlQuery.value(6).toString(), customerSqlQuery.value(7).toString(),
                            customerSqlQuery.value(8).toInt(), customerSqlQuery.value(9).toFloat()
                            );
    }

    return NULL;
}















