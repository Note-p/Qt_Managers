#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QtSerialPort/QSerialPort>
#include "Csource/cppincludes.h"
#include <QtCore/QtGlobal>
#include "search2_input_dialog.h"
#include "range_input_dialog.h"

#define __RUN_IN_QT

/*主窗口---最复杂最重要的窗口*/


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /*
     * @type:  自定义槽函数
     * @param: 是否改变了数据库
     * @true:  刷新QTable显示内容
     */
    void receiveBoolean(bool isChanged);

    /*
     * @type:  自定义槽函数
     * @param: 年份
     * @usage: 处理指定年份数据
     *         关联:year_type
     */
    void receiveYear(int year);

    /*
     * @type:  自定义槽函数
     * @param: 搜索关键词
     * @usage: 搜索
     *         关联:search_type
     */
    void receiveSearch(QString data);

    /*
     * @type:  自定义槽函数
     * @param: 双项搜索关键词类的对象
     * @usage: 双项搜索
     *         关联:search_type
     */
    void receiveSearchTwo(searchData data);

    /*
     * @type:  自定义槽函数
     * @param: 输入的范围类的对象
     * @usage: 接受用户输入的范围
     *         关联:range_type
     */
    void receiveRange(RangeInput range);

    /*
     * @type:  自定义槽函数
     * @param: 蔬菜基本信息编号
     * @usage: 对输入蔬菜基本信息窗口回调进行处理
     */
    void receiveVegCode (int vegCode);

    /*
     * @type:  QAction
     * @usage: 显示增加种植信息dialog
     */
    void on_actionAddPlantInfo_triggered();

    /*
     * @type:  QAction
     * @usage: 退出程序
     */
    void on_action_Quit_triggered();

    /*
     * @type:  QAction
     * @usage: 显示增加蔬菜品种dialog
     */
    void on_actionAddVegType_triggered();

    /*
     * @type:  QAction
     * @usage: QTable显示所有种植信息
     */
    void on_actionPlantInfoAll_triggered();

    /*
     * @type:  QAction
     * @usage: QTable显示所有蔬菜品种信息
     */
    void on_actionVegTypeAll_triggered();

    /*
     * @type:  QAction
     * @usage: 显示修改种植信息dialog
     */
    void on_actionEditPlantInfo_triggered();

    /*
     * @type:  QAction
     * @usage: 显示修改植物品种信息dialog
     */
    void on_actionEditVegInfo_triggered();

    /*
     * @type:  QAction
     * @usage: 保存当前所有数据到文件中
     */
    void on_actionSaveAll_triggered();

    /*
     * @type:  QAction
     * @usage: 保存种植信息到文件中
     */
    void on_actionSavePlantInfo_triggered();

    /*
     * @type:  QAction
     * @usage: 保存蔬菜品种信息到文件中
     */
    void on_actionSaveVegType_triggered();

    /*
     * @type:  QAction
     * @usage: QTable显示今年[2017]种植信息
     */
    void on_actionThisYear_3_triggered();

    /*
     * @type:  QAction
     * @usage: 显示输入年份对话框、返回年份信号、
     *         QTable显示指定年份种植信息
     */
    void on_actionInputYear_3_triggered();

    /*
     * @type:  QAction
     * @usage: 显示 统计总占地的信息dialog
     */
    void on_actionAreaAllVeg_triggered();

    /*
     * @type:  QAction
     * @usage: 显示输入年份对话框、返回年份信号、
     *         显示 统计指定年份占地的信息dialog
     */
    void on_actionInputYear_2_triggered();

    /*
     * @type:  QAction
     * @usage: 显示输入年份对话框、返回年份信号、
     *         显示 今年[2017]占地的信息dialog
     */
    void on_actionThisYear_2_triggered();

    /*
     * @type:  QAction
     * @usage: 显示 种类占地的信息dialog
     */
    void on_actionType1_2_triggered();
    void on_actionType2_2_triggered();
    void on_actionType3_2_triggered();
    void on_actionTyp34_triggered();
    void on_actionType5_2_triggered();

    /*
     * @type:  QAction
     * @usage: 显示 所有收成的信息dialog
     */
    void on_actionWeightAll_triggered();

    /*
     * @type:  QAction
     * @usage: 显示 今年[2017]占地的信息dialog
     */
    void on_actionThisYear_triggered();

    /*
     * @type:  QAction
     * @usage: 显示 输入年份的dialog
     */
    void on_actionInputYear_triggered();

    /*
     * @type:  QAction
     * @usage: 显示 种类收成的信息dialog
     */
    void on_actionType1_triggered();
    void on_actionType2_triggered();
    void on_actionType3_triggered();
    void on_actionType4_triggered();
    void on_actionType5_triggered();


    /*
     * 以下是各种菜单项对应的槽函数
     * 报告中有详细功能表
     * 本处不再作赘述
     */
    void on_actiondeletePlantInfo_triggered();

    void on_actiondeleteVegInfo_triggered();

    void on_actionPIType1_triggered();

    void on_actionPIType2_triggered();

    void on_actionPIType3_triggered();

    void on_actionPIType4_triggered();

    void on_actionPIType5_triggered();

    void on_actionReloadPlantInfo_triggered();

    void on_actionReloadVegInfo_triggered();

    void on_actionPlantInfoBySearch_triggered();

    void on_actionSearchFacts_triggered();

    void on_actionSearchFactsVeginfo_triggered();

    void on_actionShowVeginfoType1_triggered();

    void on_actionShowVeginfoType2_triggered();

    void on_actionShowVeginfoType3_triggered();

    void on_actionShowVeginfoType2_3_triggered();

    void on_actionShowVeginfoType5_triggered();

    void on_actionSortBySArea_triggered();

    void on_actionSortByYear_triggered();

    void on_actionSortByWeight_triggered();

    void on_actionSortByType_triggered();

    void on_actionSortByAreaR_triggered();

    void on_actionSortByYearR_triggered();

    void on_actionSortWeightR_triggered();

    void on_actionSortDefault_triggered();

    void on_actionVegSortCode_triggered();

    void on_actionVegSortType_triggered();

    void on_actionVegSortLenth_triggered();

    void on_actionShowVegType_triggered();

    void on_actionAddVegType_2_triggered();

    void on_actionDeleteType_triggered();

    void on_actionEditTypeInfo_triggered();

    void on_actionSearchPlantByTypeFacts_triggered();

    void on_actionSearchPlantByYearName_triggered();

    void on_actionSearchVegInfoTypeFacts_triggered();

    void on_actionSearchVegInfoName_triggered();

    void on_actionShowPlantByYearArea_triggered();

    void on_actionShowPlantByAreaRange_triggered();

    void on_actionShowPlantByWeightRange_triggered();

    void on_actionCountVegPlantNum_triggered();

    void on_actionloadFromBackup_triggered();

    void on_actionbackupData_triggered();

private:
    Ui::MainWindow *ui;

    /*蔬菜场信息总链表*/
    typeInfo tInfo;
    /*种植信息*/
    plantInfo pInfo;
    /*蔬菜信息*/
    vegInfo vInfo;
    /*QTable展示内容类型的枚举*/
    enum tableType {
        PLANTALL, PLANTYEAR, PLANTTYPE, PLANTSEARCH, VEGALL,  VEGYEAR, VEGTYPE, TYPEALL
    };
    /*当前QTable展示内容类型*/
    int currentTable = PLANTALL;
    /*当前QTable展示的年份__YEAR时使用*/
    int currentYear;
    /*当前QTable展示蔬菜种类__TYPE时使用*/
    int currentType;

    /*输入年份种类枚举*/
    enum year_type {
        SHOWPLANTINFO, AREA, WEIGHT, AREAWEIGHT
    };
    /*是谁要的输入年份__输入年份dialog回调用*/
    int currentYearType;

    /*搜索种类枚举*/
    enum search_type {
        VEGNAME, VEGFACTS, VEGINFOFACTS, VEGINFONAME, PLANTTYPEFACTS, PLANTYEARFACTS, VEGTYPEFACTS
    };
    /*搜索类型*/
    int currentSearchType;


    /*范围种类枚举*/
    enum range_type {
        YEARRANGE, AREARANGE, WEIGHTRANGE
    };
    /*范围类型*/
    int currentRangeType;

    /*QTable显示所有种植信息*/
    void showPlantInfo(plantInfo head);
    /*QTable显示所有蔬菜信息*/
    void showVegInfo(vegInfo info);
    /*QTable显示种类信息*/
    void showTypeInfo(typeInfo info);
    /*QTable显示指定年份种植信息*/
    void showYearPlantInfo (int year);
    /*QTable显示一类蔬菜种植信息*/
    void showTypePlantInfo (int type);
    /*QTable显示一类蔬菜信息*/
    void showTypeVegInfo(int type);
    /*从QTable读取种植信息保存到文件*/
    void savePlantInfoToFileFromTable();
};
#endif // MAINWINDOW_H
