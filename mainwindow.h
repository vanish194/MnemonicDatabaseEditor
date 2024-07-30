#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "customtreeview.h"
#include "databasemanager.h"
#include "databasestorage.h"

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
    void on_actionOpenDatabase_triggered();
    void on_actionCompareWithDatabase_triggered();

private:
    void populateTree();
    void compareData(DatabaseStorage *newStorage);

    Ui::MainWindow *ui;
    DatabaseStorage *dbStorage;
    DatabaseManager *dbManager;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
