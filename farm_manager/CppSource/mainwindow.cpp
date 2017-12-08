#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_plantinfo_dialog.h"
#include "add_vegtype_dialog.h"
#include "edit_plantinfo_dialog.h"
#include "yearinput_dialog.h"
#include "imformation_dialog.h"
#include "Csource/cppincludes.h"
#include "edit_veginfo_dialog.h"
#include "delete_plantinfo_dialog.h"
#include "delete_veginfo_dialog.h"
#include "searchinput_dialog.h"
#include "add_type_dialog.h"
#include "delete_type_dialog.h"
#include "edit_type_dialog.h"
#include "search2_input_dialog.h"
#include "range_input_dialog.h"
#include "vegcode_input_dialog.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //plantSInfo = loadPlantInfoFromFile();
    //vegSInfo = loadVegInfoFromFile();
    tInfo = loadFarmListFromFile();
    vInfo = VegInfoListMergeSort(getVegInfoFromFarmList(tInfo), VEGSORTDEFAULT);
    pInfo = PlantInfoListMergeSort(getPlantInfoListFromFarmList(tInfo), SORTDEFAULT);
    showPlantInfo(pInfo);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddPlantInfo_triggered()
{
    AddPlantInfoDialog *dlg = new AddPlantInfoDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_action_Quit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAddVegType_triggered()
{
    AddVegTypeDialog *dlg = new AddVegTypeDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_actionPlantInfoAll_triggered()
{
    showPlantInfo(pInfo);
}

void MainWindow::showPlantInfo(plantInfo head)
{
    int i;
    currentTable = PLANTALL;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("种植编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("种植面积/分"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromUtf8("种植年份"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromUtf8("收成/kg"));
    ui->tableView->setModel(model);
    plantInfo current = head;
    for (i = 0; current != NULL; i++, current = current->next) {
        model->setItem(i, 0, new QStandardItem(QString::number(current->id, 10)));
        model->setItem(i, 1, new QStandardItem(QString::number(current->vegCode, 10)));
        model->setItem(i, 2,
                       new QStandardItem(QString(current->father->father->typeName)));
        model->setItem(i, 3,
                       new QStandardItem(QString(current->father->vegName)));
        model->setItem(i, 4, new QStandardItem(QString::number(current->area, 10)));
        model->setItem(i, 5, new QStandardItem(current->year));
        model->setItem(i, 6, new QStandardItem(QString("%1").arg(current->weight)));
        for (int j = 0; j < 7; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString("菜园种植数据读取完成，当前种植数目:%1").arg(i),10000);
}

void MainWindow::showVegInfo(vegInfo info)
{
    int i;
    currentTable = VEGALL;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, QString("蔬菜编号"));
    model->setHeaderData(1, Qt::Horizontal, QString("蔬菜种类"));
    model->setHeaderData(2, Qt::Horizontal, QString("蔬菜名称"));
    model->setHeaderData(3, Qt::Horizontal, QString("营养成分"));
    ui->tableView->setModel(model);
    vegInfo current = info;
    for (i = 0; current != NULL; i++, current = current->next) {
        model->setItem(i, 0, new QStandardItem(QString("%1").arg(current->vegCode)));
        model->setItem(i, 1, new QStandardItem(QString(current->father->typeName)));
        model->setItem(i, 2,
                       new QStandardItem(QString(current->vegName)));
        model->setItem(i, 3, new QStandardItem(QString(current->nutritionFacts)));
        for (int j = 0; j < 4; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString("蔬菜信息数据读取完成，当前存储蔬菜数目:%1").arg(i),10000);
}

void MainWindow::showTypeInfo(typeInfo info) {
    int i;
    currentTable = TYPEALL;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0, Qt::Horizontal, QString("种类编号"));
    model->setHeaderData(1, Qt::Horizontal, QString("种类名称"));
    model->setHeaderData(2, Qt::Horizontal, QString("蔬菜"));
    ui->tableView->setModel(model);
    typeInfo current = info;
    for (i = 0; current != NULL; i++, current = current->next) {
        model->setItem(i, 0, new QStandardItem(QString("%1").arg(current->typeCode)));
        model->setItem(i, 1, new QStandardItem(QString(current->typeName)));
        vegInfo vInfo = current->vInfoList;
        QString vegAll;
        if (vInfo != NULL) {
            vegAll = QString("%1").arg(vInfo->vegName);
            vInfo = vInfo->next;
            for (; vInfo != NULL; vInfo = vInfo->next) {
               vegAll += QString("、%1").arg(vInfo->vegName);
            }
        }
        else {
            vegAll = QString("[该种类下没有蔬菜]");
        }
        model->setItem(i, 2,
                       new QStandardItem(vegAll));
        for (int j = 0; j < 3; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString("蔬菜种类数据读取完成，当前存储种类数目:%1").arg(i),10000);

}

void MainWindow::on_actionVegTypeAll_triggered()
{
    showVegInfo(vInfo);
}


void MainWindow::on_actionEditPlantInfo_triggered()
{
    EditPlantInfoDialog *dialog = new EditPlantInfoDialog(this);
    connect(dialog, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dialog->show();
}

void MainWindow::receiveBoolean(bool isChanged) {
    if (isChanged) {
        //Sleep(1500);
        /*释放内存*/
        freePlantInfo(pInfo);
        freeVegInfo(vInfo);
        /*读取数据*/
        tInfo = loadFarmListFromFile();
        vInfo = VegInfoListMergeSort(getVegInfoFromFarmList(tInfo), VEGSORTDEFAULT);
        pInfo = PlantInfoListMergeSort(getPlantInfoListFromFarmList(tInfo), SORTDEFAULT);
        switch (currentTable) {
        case PLANTALL:
            showPlantInfo(pInfo);
            break;
        case VEGALL:
            showVegInfo(vInfo);
            break;
        case TYPEALL:
            showTypeInfo(tInfo);
            break;
        default:
            showPlantInfo(pInfo);
            break;
        }
    }
}

void MainWindow::receiveYear(int year) {
    switch (currentYearType) {
    case SHOWPLANTINFO:
        showYearPlantInfo(year);
        break;
    case AREA:
        {
            ImformationDialog *dlg = new ImformationDialog(this);
            dlg->imformation = QString("%1年蔬菜种植面积总和为： %2 分地").arg(year).arg(getPlantAreaYear(pInfo, year));
            dlg->prepareShow();
            dlg->show();
            break;
        }
    case WEIGHT:
        {
            ImformationDialog *dlg2 = new ImformationDialog(this);
            dlg2->imformation = QString("%1年所有蔬菜收成总和为： %2 kg").arg(year)
                    .arg(getPlantWeightYear(pInfo, year));
            dlg2->prepareShow();
            dlg2->show();
            break;
        }
    }
}

void MainWindow::on_actionSaveAll_triggered()
{
    savePlantInfoToFile(pInfo);
    saveVegInfoToFile(vInfo);
}

void MainWindow::on_actionSavePlantInfo_triggered()
{
    savePlantInfoToFile(pInfo);
}

void MainWindow::on_actionSaveVegType_triggered()
{
    saveVegInfoToFile(vInfo);
}

void MainWindow::on_actionThisYear_3_triggered()
{
    showYearPlantInfo(2017);
}

void MainWindow::showYearPlantInfo (int year) {
    int i;
    currentTable = PLANTALL;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("种植编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("种植面积/分"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromUtf8("种植年份"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromUtf8("收成/kg"));
    ui->tableView->setModel(model);
    plantInfo current = pInfo;
    for (i = 0; current != NULL; i++, current = current->next) {
        while (current != NULL) {
            if (QString::fromUtf8(current->year).toInt() == year)
                break;
            current = current->next;
        }
        if (current == NULL) {
            break;
        }
        model->setItem(i, 0, new QStandardItem(QString::number(current->id, 10)));
        model->setItem(i, 1, new QStandardItem(QString::number(current->vegCode, 10)));
        model->setItem(i, 2, new QStandardItem(QString(current->father->father->typeName)));
        model->setItem(i, 3, new QStandardItem(QString(current->father->vegName)));
        model->setItem(i, 4, new QStandardItem(QString::number(current->area, 10)));
        model->setItem(i, 5, new QStandardItem(current->year));
        model->setItem(i, 6, new QStandardItem(QString("%1").arg(current->weight)));
        for (int j = 0; j < 7; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString::fromUtf8("菜园种植数据读取完成，该年份种植数目:")+ QString("%1").arg(i), 10000);
}

void MainWindow::showTypePlantInfo(int type) {
    int i;
    currentTable = PLANTTYPE;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("种植编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("种植面积/分"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromUtf8("种植年份"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromUtf8("收成/kg"));
    ui->tableView->setModel(model);
    plantInfo current = pInfo;
    for (i = 0; current != NULL; i++, current = current->next) {
        while (current != NULL) {
            if (getVegInfoByCode(vInfo ,current->vegCode)->vegType - '0' == type)
                break;
            current = current->next;
        }
        if (current == NULL) {
            break;
        }
        model->setItem(i, 0, new QStandardItem(QString::number(current->id, 10)));
        model->setItem(i, 1, new QStandardItem(QString::number(current->vegCode, 10)));
        model->setItem(i, 2, new QStandardItem(QString(current->father->father->typeName)));
        model->setItem(i, 3, new QStandardItem(QString(current->father->vegName)));
        model->setItem(i, 4, new QStandardItem(QString::number(current->area, 10)));
        model->setItem(i, 5, new QStandardItem(current->year));
        model->setItem(i, 6, new QStandardItem(QString("%1").arg(current->weight)));
        for (int j = 0; j < 7; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString::fromUtf8("菜园种植数据读取完成，该种类蔬菜种植数目:")+ QString("%1").arg(i), 10000);
}

void MainWindow::on_actionInputYear_3_triggered()
{
    YearInputDialog *dlg = new YearInputDialog(this);
    currentYearType = SHOWPLANTINFO;
    connect(dlg, SIGNAL(sendYear(int)), this, SLOT(receiveYear(int)));
    dlg->show();
}

void MainWindow::on_actionAreaAllVeg_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("当前蔬菜种植面积总和为： %1 分地").arg(getPlantAreaAll(pInfo));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionInputYear_2_triggered()
{
    YearInputDialog *dlg = new YearInputDialog(this);
    currentYearType = AREA;
    connect(dlg, SIGNAL(sendYear(int)), this, SLOT(receiveYear(int)));
    dlg->show();
}

void MainWindow::on_actionThisYear_2_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("%1年蔬菜种植面积总和为： %2 分地").arg(2017).arg(getPlantAreaYear(pInfo, 2017));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType1_2_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("根茎类蔬菜种植面积总和为： %1 分地")
            .arg(getPlantAreaVegType(pInfo, vInfo, 1));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType2_2_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("果菜类蔬菜种植面积总和为： %1 分地")
            .arg(getPlantAreaVegType(pInfo, vInfo, 2));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType3_2_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("瓜类蔬菜种植面积总和为： %1 分地")
            .arg(getPlantAreaVegType(pInfo, vInfo, 3));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionTyp34_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("叶菜类蔬菜种植面积总和为： %1 分地")
            .arg(getPlantAreaVegType(pInfo, vInfo, 4));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType5_2_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("菌类蔬菜种植面积总和为： %1 分地")
            .arg(getPlantAreaVegType(pInfo, vInfo, 5));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionWeightAll_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("所有蔬菜收成总和为： %1 kg")
            .arg(getPlantWeightAll(pInfo));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionThisYear_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("%1年所有蔬菜收成总和为： %2 kg").arg(2017)
            .arg(getPlantWeightYear(pInfo, 2017));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionInputYear_triggered()
{
    YearInputDialog *dlg = new YearInputDialog(this);
    currentYearType = WEIGHT;
    connect(dlg, SIGNAL(sendYear(int)), this, SLOT(receiveYear(int)));
    dlg->show();
}

void MainWindow::on_actionType1_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("根茎类蔬菜收成总和为： %1 分地")
            .arg(getPlantWeightVegType(pInfo, vInfo, 1));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType2_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("果菜类蔬菜收成总和为： %1 分地")
            .arg(getPlantWeightVegType(pInfo, vInfo, 2));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType3_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("瓜类蔬菜收成总和为： %1 分地")
            .arg(getPlantWeightVegType(pInfo, vInfo, 3));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType4_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("叶菜类蔬菜收成总和为： %1 分地")
            .arg(getPlantWeightVegType(pInfo, vInfo, 4));
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionType5_triggered()
{
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("菌类蔬菜收成总和为： %1 分地")
            .arg(getPlantWeightVegType(pInfo, vInfo, 5));
    dlg->prepareShow();
    dlg->show();
}
void MainWindow::savePlantInfoToFileFromTable() {

}

void MainWindow::on_actionEditVegInfo_triggered()
{
    EditVegInfoDialog *dlg = new EditVegInfoDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_actiondeletePlantInfo_triggered()
{
    DeletePlantInfoDialog *dlg = new DeletePlantInfoDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}


void MainWindow::on_actionPIType1_triggered()
{
    showTypePlantInfo(1);
}

void MainWindow::on_actionPIType2_triggered()
{
    showTypePlantInfo(2);
}

void MainWindow::on_actionPIType3_triggered()
{
    showTypePlantInfo(3);
}

void MainWindow::on_actionPIType4_triggered()
{
    showTypePlantInfo(4);
}

void MainWindow::on_actionPIType5_triggered()
{
    showTypePlantInfo(5);
}

void MainWindow::on_actionReloadPlantInfo_triggered()
{
    /*释放内存*/
    freePlantInfo(pInfo);
    /*读取数据*/
    typeInfo tInfo = loadFarmListFromFile();
    pInfo = getPlantInfoListFromFarmList(tInfo);
    pInfo = PlantInfoListMergeSort(pInfo, SORTDEFAULT);
    if (currentTable == PLANTALL){
        showPlantInfo(pInfo);
    }
}

void MainWindow::on_actionReloadVegInfo_triggered()
{
    freeVegInfo(vInfo);
    typeInfo tInfo = loadFarmListFromFile();
    vInfo = getVegInfoFromFarmList(tInfo);
    if (currentTable == VEGALL){
        showVegInfo(vInfo);
    }
}


void MainWindow::on_actionPlantInfoBySearch_triggered()
{
    currentSearchType = VEGNAME;
    SearchInputDialog *dlg = new SearchInputDialog(this);
    connect(dlg, SIGNAL(sendSearch(QString)), this, SLOT(receiveSearch(QString)));
    dlg->searchLabel = QString("搜索蔬菜名");
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::receiveSearch(QString data) {
    int i;
    searchResult result = NULL;
    switch (currentSearchType) {
    case VEGNAME:
        result = searchVegName(vInfo, data.toUtf8().data());
        break;
    case VEGFACTS:
        result = searchVegFacts(vInfo, data.toUtf8().data());
        break;
    case VEGINFONAME:
        result = searchVegName(vInfo, data.toUtf8().data());
        break;
    case VEGINFOFACTS:
        currentTable = VEGALL;
        QStandardItemModel *model = new QStandardItemModel();
        model->setColumnCount(4);
        model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("营养成分"));
        ui->tableView->setModel(model);
        vegInfo current = vInfo;
        for (i = 0; current != NULL; i++, current = current->next) {
            while (current != NULL) {
                if (strstr(current->nutritionFacts, data.toUtf8().data()) != NULL)
                    break;
                current = current->next;
            }
            if (current == NULL) {
                break;
            }
            model->setItem(i, 0, new QStandardItem(QString("%1").arg(current->vegCode)));
            model->setItem(i, 1, new QStandardItem(QString(current->father->typeName)));
            model->setItem(i, 2, new QStandardItem(QString(current->vegName)));
            model->setItem(i, 3, new QStandardItem(QString(current->nutritionFacts)));
            for (int j = 0; j < 4; j++){
                model->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        ui->statusBar->showMessage(QString("蔬菜品种数据读取完成，当前存储品种数目:%1").arg(i),10000);
        return ;

    }
    if (result == NULL) {
        ImformationDialog *dlg = new ImformationDialog(this);
        dlg->imformation = QString("无法找到: %1").arg(data);
        dlg->prepareShow();
        dlg->show();
    }
    else {
        if (currentSearchType == VEGINFONAME) {
            currentTable = VEGALL;
            QStandardItemModel *model = new QStandardItemModel();
            model->setColumnCount(4);
            model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
            model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
            model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
            model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("营养成分"));
            ui->tableView->setModel(model);
            vegInfo current = vInfo;
            for (i = 0; current != NULL; i++, current = current->next) {
                int j = 0;
                while(1) {
                    if (current == NULL) {
                        ui->statusBar->showMessage(QString("蔬菜品种数据读取完成，当前存储品种数目:%1").arg(i),10000);
                        return ;
                    }
                    for(j = 0; j < result->resultNum; j++) {
                        if(current->vegCode == result->vegCodeArray[j]) {
                            break;
                        }
                    }
                    if (j == result->resultNum) {
                        current = current->next;
                    }
                    else {
                        break;
                    }
                }
                model->setItem(i, 0, new QStandardItem(QString("%1").arg(current->vegCode)));
                model->setItem(i, 1, new QStandardItem(QString(current->father->typeName)));
                model->setItem(i, 2, new QStandardItem(QString(current->vegName)));
                model->setItem(i, 3, new QStandardItem(QString(current->nutritionFacts)));
                for (int j = 0; j < 4; j++){
                    model->item(i, j)->setTextAlignment(Qt::AlignCenter);
                }
            }
            ui->statusBar->showMessage(QString("蔬菜品种数据读取完成，当前存储品种数目:%1").arg(i),10000);
            return ;
        }
        currentTable = PLANTSEARCH;
        QStandardItemModel *model = new QStandardItemModel();
        model->setColumnCount(7);
        model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("种植编号"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("种植面积/分"));
        model->setHeaderData(5, Qt::Horizontal, QString::fromUtf8("种植年份"));
        model->setHeaderData(6, Qt::Horizontal, QString::fromUtf8("收成/kg"));
        ui->tableView->setModel(model);
        plantInfo current = pInfo;
        for (i = 0; current != NULL; i++, current = current->next) {
            int j = 0;
            while(1) {
                if (current == NULL) {
                    ui->statusBar->showMessage(QString("菜园种植数据搜索完成，搜索到的种植数目:")+ QString("%1").arg(i),10000);
                    return ;
                }
                for(j = 0; j < result->resultNum; j++) {
                    if(current->vegCode == result->vegCodeArray[j]) {
                        break;
                    }
                }
                if (j == result->resultNum) {
                    current = current->next;
                }
                else {
                    break;
                }
            }
            model->setItem(i, 0, new QStandardItem(QString::number(current->id, 10)));
            model->setItem(i, 1, new QStandardItem(QString::number(current->vegCode, 10)));
            model->setItem(i, 2, new QStandardItem(QString(current->father->father->typeName)));
            model->setItem(i, 3, new QStandardItem(QString(current->father->vegName)));
            model->setItem(i, 4, new QStandardItem(QString::number(current->area, 10)));
            model->setItem(i, 5, new QStandardItem(current->year));
            model->setItem(i, 6, new QStandardItem(QString("%1").arg(current->weight)));
            for (int j = 0; j < 7; j++){
                model->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        ui->statusBar->showMessage(QString("菜园种植数据搜索完成，搜索到的种植数目:")+ QString("%1").arg(i), 10000);
    }
}



void MainWindow::receiveSearchTwo(searchData data) {
    int i;
    searchResult result = NULL;
    switch (currentSearchType) {
    case PLANTTYPEFACTS:
        result = searchVegFacts(vInfo, data.data2.toUtf8().data());

        break;
    case PLANTYEARFACTS:
        result = searchVegFacts(vInfo, data.data2.toUtf8().data());
        break;
    case VEGTYPEFACTS:
        result = searchVegFacts(vInfo, data.data2.toUtf8().data());
        break;
    }

    if (result == NULL) {
        ImformationDialog *dlg = new ImformationDialog(this);
        dlg->imformation = QString("无法找到: %1").arg(data.data2);
        dlg->prepareShow();
        dlg->show();
        return ;
    }
    if (currentSearchType == VEGTYPEFACTS) {
        currentTable = VEGALL;
        QStandardItemModel *model = new QStandardItemModel();
        model->setColumnCount(4);
        model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("营养成分"));
        ui->tableView->setModel(model);
        vegInfo current = vInfo;
        for (i = 0; current != NULL; i++, current = current->next) {
            int j = 0;
            while(1) {
                if (current == NULL) {
                    ui->statusBar->showMessage(QString("蔬菜信息搜索完成，搜索到的蔬菜数目:")+ QString("%1").arg(i),10000);
                    return ;
                }
                for(j = 0; j < result->resultNum; j++) {
                    if(current->vegCode == result->vegCodeArray[j]
                            && current->vegType == data.data1.toUtf8().data()[0]) {
                        break;
                    }
                }
                if (j == result->resultNum) {
                    current = current->next;
                }
                else {
                    break;
                }
            }
            model->setItem(i, 0, new QStandardItem(QString("%1").arg(current->vegCode)));
            model->setItem(i, 1, new QStandardItem(QString(current->father->typeName)));
            model->setItem(i, 2, new QStandardItem(QString(current->vegName)));
            model->setItem(i, 3, new QStandardItem(QString(current->nutritionFacts)));
            for (int j = 0; j < 4; j++){
                model->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        ui->statusBar->showMessage(QString("蔬菜品种数据读取完成，当前存储品种数目:%1").arg(i),10000);
        return ;
    }
    currentTable = PLANTSEARCH;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("种植编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("种植面积/分"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromUtf8("种植年份"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromUtf8("收成/kg"));
    ui->tableView->setModel(model);
    plantInfo current = pInfo;
    for (i = 0; current != NULL; i++, current = current->next) {
        int j = 0;
        while(1) {
            if (current == NULL) {
                ui->statusBar->showMessage(QString("菜园种植数据搜索完成，搜索到的种植数目:")+ QString("%1").arg(i),10000);
                return ;
            }
            for(j = 0; j < result->resultNum; j++) {
                if(current->vegCode == result->vegCodeArray[j]) {
                    if (currentSearchType == PLANTTYPEFACTS) {
                        if (current->father->vegType == data.data1.toUtf8().data()[0])
                            break;
                    }
                    else if (currentSearchType == PLANTYEARFACTS) {
                        if (strstr(current->year, data.data1.toUtf8().data()) != NULL)
                            break;
                    }
                }
            }
            if (j == result->resultNum) {
                current = current->next;
            }
            else {
                break;
            }
        }
        model->setItem(i, 0, new QStandardItem(QString::number(current->id, 10)));
        model->setItem(i, 1, new QStandardItem(QString::number(current->vegCode, 10)));
        model->setItem(i, 2, new QStandardItem(QString(current->father->father->typeName)));
        model->setItem(i, 3, new QStandardItem(QString(current->father->vegName)));
        model->setItem(i, 4, new QStandardItem(QString::number(current->area, 10)));
        model->setItem(i, 5, new QStandardItem(current->year));
        model->setItem(i, 6, new QStandardItem(QString("%1").arg(current->weight)));
        for (int j = 0; j < 7; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString("菜园种植数据搜索完成，搜索到的种植数目:")+ QString("%1").arg(i), 10000);



}




void MainWindow::on_actionSearchFacts_triggered()
{
    currentSearchType = VEGFACTS;
    SearchInputDialog *dlg = new SearchInputDialog(this);
    connect(dlg, SIGNAL(sendSearch(QString)), this, SLOT(receiveSearch(QString)));
    dlg->searchLabel = QString("搜索蔬菜营养成分");
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionSearchFactsVeginfo_triggered()
{
    currentSearchType = VEGINFOFACTS;
    SearchInputDialog *dlg = new SearchInputDialog(this);
    connect(dlg, SIGNAL(sendSearch(QString)), this, SLOT(receiveSearch(QString)));
    dlg->searchLabel = QString("搜索蔬菜营养成分\n成分间用,隔开");
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::showTypeVegInfo(int type) {
    int i;
    currentTable = VEGALL;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("蔬菜编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("蔬菜种类"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("蔬菜名称"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("营养成分"));
    ui->tableView->setModel(model);
    vegInfo current = vInfo;
    for (i = 0; current != NULL; i++, current = current->next) {
        while (current != NULL) {
            if (current->vegType - '0' == type)
                break;
            current = current->next;
        }
        if (current == NULL) {
            break;
        }
        model->setItem(i, 0, new QStandardItem(QString("%1").arg(current->vegCode)));
        model->setItem(i, 1, new QStandardItem(QString(current->father->typeName)));
        model->setItem(i, 2, new QStandardItem(QString(current->vegName)));
        model->setItem(i, 3, new QStandardItem(QString(current->nutritionFacts)));
        for (int j = 0; j < 4; j++){
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->statusBar->showMessage(QString::fromUtf8("蔬菜品种数据读取完成，当前存储品种数目:")+ QString("%1").arg(i),10000);
}

void MainWindow::on_actionShowVeginfoType1_triggered()
{
    showTypeVegInfo(1);
}

void MainWindow::on_actionShowVeginfoType2_triggered()
{
    showTypeVegInfo(2);
}

void MainWindow::on_actionShowVeginfoType3_triggered()
{
    showTypeVegInfo(3);
}

void MainWindow::on_actionShowVeginfoType2_3_triggered()
{
    showTypeVegInfo(4);
}

void MainWindow::on_actionShowVeginfoType5_triggered()
{
    showTypeVegInfo(5);
}

void MainWindow::on_actiondeleteVegInfo_triggered()
{
    DeleteVegInfoDialog *dlg = new DeleteVegInfoDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_actionSortBySArea_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTAREA);
    showPlantInfo(head);
}



void MainWindow::on_actionSortByYear_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTYEAR);
    showPlantInfo(head);
}

void MainWindow::on_actionSortByWeight_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTWEIGHT);
    showPlantInfo(head);
}

void MainWindow::on_actionSortByType_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTTYPE);
    showPlantInfo(head);
}

void MainWindow::on_actionSortByAreaR_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTAREAR);
    showPlantInfo(head);
}

void MainWindow::on_actionSortByYearR_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTYEARR);
    showPlantInfo(head);
}

void MainWindow::on_actionSortWeightR_triggered()
{
    plantInfo info = PlantInfoListCopy(pInfo);
    plantInfo head = PlantInfoListMergeSort(info, SORTWEIGHTR);
    showPlantInfo(head);
}

void MainWindow::on_actionSortDefault_triggered()
{
    showPlantInfo(pInfo);
}

void MainWindow::on_actionVegSortCode_triggered()
{
    vegInfo info = VegInfoListCopy(vInfo);
    showVegInfo(VegInfoListMergeSort(info, VEGSORTDEFAULT));
}

void MainWindow::on_actionVegSortType_triggered()
{
    vegInfo info = VegInfoListCopy(vInfo);
    showVegInfo(VegInfoListMergeSort(info, VEGSORTDEFAULT));
}

void MainWindow::on_actionVegSortLenth_triggered()
{
    vegInfo info = VegInfoListCopy(vInfo);
    showVegInfo(VegInfoListMergeSort(info, VEGSORTFACTSLENTH));
}

void MainWindow::on_actionShowVegType_triggered()
{
    showTypeInfo(tInfo);
}

void MainWindow::on_actionAddVegType_2_triggered()
{
    AddTypeDialog *dlg = new AddTypeDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_actionDeleteType_triggered()
{
    DeleteTypeDialog *dlg = new DeleteTypeDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_actionEditTypeInfo_triggered()
{
    EditTypeDialog *dlg = new EditTypeDialog(this);
    connect(dlg, SIGNAL(sendBoolean(bool)), this, SLOT(receiveBoolean(bool)));
    dlg->show();
}

void MainWindow::on_actionSearchPlantByTypeFacts_triggered()
{
    currentSearchType = PLANTTYPEFACTS;
    Search2InputDialog *dlg = new Search2InputDialog(this);
    connect(dlg, SIGNAL(sendSearchData(searchData)), this, SLOT(receiveSearchTwo(searchData)));
    dlg->PrepareShow(QString("蔬菜种类编号"), QString("营养成分关键字"));
    dlg->show();
}

void MainWindow::on_actionSearchPlantByYearName_triggered()
{
    currentSearchType = PLANTYEARFACTS;
    Search2InputDialog *dlg = new Search2InputDialog(this);
    connect(dlg, SIGNAL(sendSearchData(searchData)), this, SLOT(receiveSearchTwo(searchData)));
    dlg->PrepareShow(QString("蔬菜种植年份"), QString("营养成分关键字"));
    dlg->show();
}

void MainWindow::on_actionSearchVegInfoTypeFacts_triggered()
{
    currentSearchType = VEGTYPEFACTS;
    Search2InputDialog *dlg = new Search2InputDialog(this);
    connect(dlg, SIGNAL(sendSearchData(searchData)), this, SLOT(receiveSearchTwo(searchData)));
    dlg->PrepareShow(QString("蔬菜种类编号"), QString("营养成分关键字"));
    dlg->show();
}

void MainWindow::on_actionSearchVegInfoName_triggered()
{
    currentSearchType = VEGINFONAME;
    SearchInputDialog *dlg = new SearchInputDialog(this);
    connect(dlg, SIGNAL(sendSearch(QString)), this, SLOT(receiveSearch(QString)));
    dlg->searchLabel = QString("搜索蔬菜名");
    dlg->prepareShow();
    dlg->show();
}

void MainWindow::on_actionShowPlantByYearArea_triggered()
{
    currentRangeType = YEARRANGE;
    RangeInputDialog *dlg = new RangeInputDialog(this);
    connect(dlg, SIGNAL(sendRange(RangeInput)), this, SLOT(receiveRange(RangeInput)));
    dlg->PrepareShow(QString("起始年份"), QString("终止年份"));
    dlg->show();
}


void MainWindow::receiveRange(RangeInput range) {
    switch (currentRangeType) {
    case YEARRANGE: {
        plantInfo current = pInfo, head = NULL, currentNew = NULL;
        for (; current != NULL; current = current->next) {
            if (getIntFromString(current->year) >= range.from && getIntFromString(current->year) <= range.to) {
                if (head == NULL) {
                    head = (plantInfo)malloc(sizeof(struct plant_info));
                    *head = *current;
                    currentNew = head;
                }
                else {
                    currentNew->next = (plantInfo)malloc(sizeof(struct plant_info));
                    currentNew = currentNew->next;
                    *currentNew = *current;
                }
            }
        }
        currentNew->next = NULL;
        showPlantInfo(PlantInfoListMergeSort(head, SORTWEIGHTR));
        freePlantInfo(head);
        break;
    }
    case AREARANGE: {
        plantInfo current = pInfo, head = NULL, currentNew = NULL;
        for (; current != NULL; current = current->next) {
            if (current->area >= range.from && current->area <= range.to) {
                if (head == NULL) {
                    head = (plantInfo)malloc(sizeof(struct plant_info));
                    *head = *current;
                    currentNew = head;
                }
                else {
                    currentNew->next = (plantInfo)malloc(sizeof(struct plant_info));
                    currentNew = currentNew->next;
                    *currentNew = *current;
                }
            }
        }
        currentNew->next = NULL;
        showPlantInfo(PlantInfoListMergeSort(head, SORTAREA));
        freePlantInfo(head);
        break;
    }
    case WEIGHTRANGE: {
        plantInfo current = pInfo, head = NULL, currentNew = NULL;
        for (; current != NULL; current = current->next) {
            if (current->weight >= range.from && current->weight <= range.to) {
                if (head == NULL) {
                    head = (plantInfo)malloc(sizeof(struct plant_info));
                    *head = *current;
                    currentNew = head;
                }
                else {
                    currentNew->next = (plantInfo)malloc(sizeof(struct plant_info));
                    currentNew = currentNew->next;
                    *currentNew = *current;
                }
            }
        }
        currentNew->next = NULL;
        showPlantInfo(PlantInfoListMergeSort(head, SORTWEIGHT));
        freePlantInfo(head);
        break;
    }
    }
}

void MainWindow::on_actionShowPlantByAreaRange_triggered()
{
    currentRangeType = AREARANGE;
    RangeInputDialog *dlg = new RangeInputDialog(this);
    connect(dlg, SIGNAL(sendRange(RangeInput)), this, SLOT(receiveRange(RangeInput)));
    dlg->PrepareShow(QString("起始面积"), QString("终止面积"));
    dlg->show();
}

void MainWindow::on_actionShowPlantByWeightRange_triggered()
{
    currentRangeType = WEIGHTRANGE;
    RangeInputDialog *dlg = new RangeInputDialog(this);
    connect(dlg, SIGNAL(sendRange(RangeInput)), this, SLOT(receiveRange(RangeInput)));
    dlg->PrepareShow(QString("起始收成"), QString("终止收成"));
    dlg->show();
}

void MainWindow::on_actionCountVegPlantNum_triggered()
{
    VegCodeInputDialog *dlg = new VegCodeInputDialog(this);
    connect(dlg, SIGNAL(sendVegCode(int)), this, SLOT(receiveVegCode(int)));
    dlg->show();
}

void MainWindow::receiveVegCode(int vegCode) {
    vegInfo current = vInfo;
    for (; current != NULL; current = current->next) {
        if (current->vegCode == vegCode) {
            plantInfo currentPInfo = current->pInfoList;
            int plantNum = 0;
            for (; currentPInfo != 0; currentPInfo = currentPInfo->next, plantNum++) ;
            ImformationDialog *dlg = new ImformationDialog(this);
            dlg->imformation = QString("目前种植蔬菜 %1 的个数为: %2").arg(current->vegName).arg(plantNum);
            dlg->prepareShow();
            dlg->show();
            return ;
        }
    }
    ImformationDialog *dlg = new ImformationDialog(this);
    dlg->imformation = QString("无法找到编号为 %1 的蔬菜").arg(vegCode);
    dlg->prepareShow();
    dlg->show();
}



void MainWindow::on_actionloadFromBackup_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("打开蔬菜数据备份文件"),
                                                    " ",
                                                    tr("蔬菜数据备份文件(*.bak);;所有文件(*.*)")
                                                    );

    if (getDataFileFromBackupFile(fileName.toUtf8().data())) {
        ui->statusBar->showMessage(QString("读取成功"), 10000);
    }
}

void MainWindow::on_actionbackupData_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("蔬菜数据备份文件要保存到"),
                                                    " ",
                                                    tr("蔬菜数据备份文件(*.bak);;所有文件(*.*)")
                                                    );
    if (backupDataFileTo(fileName.toUtf8().data())) {
        ui->statusBar->showMessage(QString("保存成功"), 10000);
    }
}
