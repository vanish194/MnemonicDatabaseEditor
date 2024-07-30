#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "customtreeview.h"
#include "databasemanager.h"

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
    Ui::MainWindow *ui;
    DatabaseStorage *dbStorage;
    DatabaseManager *dbManager;
};

#endif // MAINWINDOW_H
