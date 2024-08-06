#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbStorage(new DatabaseStorage)
    , dbManager(new DatabaseManager(dbStorage))
{
    ui->setupUi(this);

    // Connect signals from CustomTreeView to MainWindow slots
    connect(ui->treeView, &CustomTreeView::addItem, this, &MainWindow::handleAddItem);
    connect(ui->treeView, &CustomTreeView::editItem, this, &MainWindow::handleEditItem);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbManager;
    delete dbStorage;
}

void MainWindow::handleAddItem(int itemType)
{
    switch (itemType) {
    case CustomTreeView::ToolType:
        openToolAddWindow();
        break;
    case CustomTreeView::SensorType:
        openSensorAddWindow();
        break;
    case CustomTreeView::MainMnemonicType:
        openMainMnemonicAddWindow();
        break;
    case CustomTreeView::AdditionalMnemonicType:
        openAdditionalMnemonicAddWindow();
        break;
    default:
        QMessageBox::warning(this, tr("Invalid Action"), tr("No item selected."));
        break;
    }
}

void MainWindow::handleEditItem(int itemType, int itemId)
{
    switch (itemType) {
    case CustomTreeView::ToolType:
        editTool(itemId);
        break;
    case CustomTreeView::SensorType:
        editSensor(itemId);
        break;
    case CustomTreeView::MainMnemonicType:
        editMainMnemonic(itemId);
        break;
    case CustomTreeView::AdditionalMnemonicType:
        editAdditionalMnemonic(itemId);
        break;
    default:
        QMessageBox::warning(this, tr("Invalid Action"), tr("No item selected or invalid item."));
        break;
    }
}

void MainWindow::editTool(int toolId)
{
    ToolAddWindow toolDialog(this);
    Tool *tool = dbStorage->findToolById(toolId);
    if (tool) {
        toolDialog.setToolData(tool->getToolName(),
                               tool->getDescription(),
                               tool->getLength(),
                               tool->getOuterDiameter(),
                               tool->getInnerDiameter(),
                               QString(),
                               0); // Set image and index properly
        if (toolDialog.exec() == QDialog::Accepted) {
            Tool updatedTool = toolDialog.getToolData();
            dbManager->updateTool(updatedTool);
        }
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Tool not found."));
    }
}

void MainWindow::editSensor(int sensorId)
{
    SensorAddWindow sensorDialog(this);
    Sensor *sensor = dbStorage->findSensorById(sensorId);
    if (sensor) {
        sensorDialog.setSensorData(sensor->getSensorName(),
                                   sensor->getSensorDescription(),
                                   sensor->getOffset(),
                                   0,
                                   0); // Adjust indices as needed
        if (sensorDialog.exec() == QDialog::Accepted) {
            Sensor updatedSensor = sensorDialog.getSensorData();
            dbManager->updateSensor(updatedSensor);
        }
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Sensor not found."));
    }
}

void MainWindow::editMainMnemonic(int mainMnemonicId)
{
    MainMnemonicAddWindow mainMnemonicDialog(this);
    MainMnemonic *mainMnemonic = dbStorage->findMainMnemonicById(mainMnemonicId);
    if (mainMnemonic) {
        mainMnemonicDialog.setMainMnemonicData(mainMnemonic->getMainMnemonicName(),
                                               mainMnemonic->getMainMnemonicDescription(),
                                               0,
                                               0); // Adjust indices as needed
        if (mainMnemonicDialog.exec() == QDialog::Accepted) {
            MainMnemonic updatedMainMnemonic = mainMnemonicDialog.getMainMnemonicData();
            dbManager->updateMainMnemonic(updatedMainMnemonic);
        }
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Main Mnemonic not found."));
    }
}

void MainWindow::editAdditionalMnemonic(int additionalMnemonicId)
{
    AdditionalMnemonicAddWindow additionalMnemonicDialog(this);
    AdditionalMnemonic *additionalMnemonic = dbStorage->findAdditionalMnemonicById(
        additionalMnemonicId);
    if (additionalMnemonic) {
        additionalMnemonicDialog
            .setAdditionalMnemonicData(additionalMnemonic->getAdditionalMnemonicName(),
                                       0,
                                       0,
                                       0); // Set indices correctly
        if (additionalMnemonicDialog.exec() == QDialog::Accepted) {
            AdditionalMnemonic updatedAdditionalMnemonic = additionalMnemonicDialog
                                                               .getAdditionalMnemonicData();
            dbManager->updateAdditionalMnemonic(updatedAdditionalMnemonic);
        }
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Additional Mnemonic not found."));
    }
}

void MainWindow::openToolAddWindow()
{
    ToolAddWindow toolDialog(this);
    if (toolDialog.exec() == QDialog::Accepted) {
        Tool newTool = toolDialog.getToolData();
        dbManager->addTool(newTool);
    }
}

void MainWindow::openSensorAddWindow()
{
    SensorAddWindow sensorDialog(this);
    if (sensorDialog.exec() == QDialog::Accepted) {
        Sensor newSensor = sensorDialog.getSensorData();
        dbManager->addSensor(newSensor);
    }
}

void MainWindow::openMainMnemonicAddWindow()
{
    MainMnemonicAddWindow mainMnemonicDialog(this);
    if (mainMnemonicDialog.exec() == QDialog::Accepted) {
        MainMnemonic newMainMnemonic = mainMnemonicDialog.getMainMnemonicData();
        dbManager->addMainMnemonic(newMainMnemonic);
    }
}

void MainWindow::openAdditionalMnemonicAddWindow()
{
    AdditionalMnemonicAddWindow additionalMnemonicDialog(this);
    if (additionalMnemonicDialog.exec() == QDialog::Accepted) {
        AdditionalMnemonic newAdditionalMnemonic = additionalMnemonicDialog
                                                       .getAdditionalMnemonicData();
        dbManager->addAdditionalMnemonic(newAdditionalMnemonic);
    }
}
