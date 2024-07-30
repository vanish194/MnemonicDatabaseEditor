#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbStorage(new DatabaseStorage)
    , dbManager(new DatabaseManager(dbStorage))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbManager;
    delete dbStorage;
}

void MainWindow::on_actionOpenDatabase_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Database"),
                                                    "",
                                                    tr("Database Files (*.db *.sqlite)"));
    if (fileName.isEmpty())
        return;

    if (!dbManager->openDatabase(fileName)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the database."));
        return;
    }

    if (!dbManager->loadDataFromDatabase()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load data from the database."));
        return;
    }

    ui->tableView->setModel(dbManager->getModel());
    ui->treeView->setModel(dbManager->getTreeModel());
}

void MainWindow::on_actionCompareWithDatabase_triggered()
{
    dbManager->compareData();
}
