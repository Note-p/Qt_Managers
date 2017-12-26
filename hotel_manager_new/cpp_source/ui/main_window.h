#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "../core/database_util.h"
#include "dateinput_dialog.h"
namespace Ui {
class MainWindow;
}

// enum the table show type
enum table_type {
    ROOMTABLE, CUSTOMERTABLE, ALLTABLE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /* show tables */
    void showRoomTable(RoomList* roomList);
    void showCustomerTable (CustomerList* customerList);
    void showAllTable(RoomList* roomList);

public slots:
    /* if data changed, need to reload the table */
    void refresh ();
    /* check out handler */
    void checkOutHandler (int number);
    /* handle datarange input */
    void dateRangeHandler (DateRange dateRange);

private slots:
    void on_actionadd_customer_triggered();

    void on_actionshow_customer_triggered();

    void on_actionshow_room_triggered();

    void on_actionadd_room_triggered();

    void on_actionordinary_customer_triggered();

    void on_actionedit_room_triggered();

    void on_actionedit_customer_triggered();

    void on_actionby_number_triggered();

    void on_actionby_name_triggered();

    void on_actionby_type_triggered();

    void on_actionby_check_in_time_triggered();

    void on_actionby_check_out_time_triggered();

    void on_actionby_point_triggered();

    void on_actiondelete_customer_triggered();

    void on_actiondelete_room_triggered();

    void on_actionby_number_2_triggered();

    void on_actionby_type_2_triggered();

    void on_actionby_price_triggered();

    void on_actionby_usage_triggered();

    void on_actionby_clean_situation_triggered();

    void on_action_triggered();

    void on_actionVIP_SVIP_triggered();

    void on_actionordinary_triggered();

    void on_actionVIP_SVIP_2_triggered();

    void on_actionshow_available_room_triggered();

    void on_actionshow_all_triggered();

private:
    Ui::MainWindow *ui;

    /* database -- all file action need to use it */
    DatabaseUtil database;

    /* current table type */
    int currentTable;
};

#endif // MAIN_WINDOW_H
