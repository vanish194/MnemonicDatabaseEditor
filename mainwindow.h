#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "additionalmnemonicaddwindow.h"
#include "databasemanager.h"
#include "databasestorage.h"
#include "mainmnemonicaddwindow.h"
#include "sensoraddwindow.h"
#include "tooladdwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleAddItem(int itemType);
    void handleEditItem(int itemType, int itemId);

private:
    Ui::MainWindow *ui;
    DatabaseStorage *dbStorage;
    DatabaseManager *dbManager;

    void openToolAddWindow();
    void openSensorAddWindow();
    void openMainMnemonicAddWindow();
    void openAdditionalMnemonicAddWindow();

    void editTool(int toolId);
    void editSensor(int sensorId);
    void editMainMnemonic(int mainMnemonicId);
    void editAdditionalMnemonic(int additionalMnemonicId);
};

#endif // MAINWINDOW_H
