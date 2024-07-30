#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItem>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbStorage(new DatabaseStorage())
    , dbManager(new DatabaseManager(dbStorage))
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->treeView->setModel(model);

    connect(ui->treeView,
            &CustomTreeView::contextMenuRequested,
            this,
            [](const QPoint &pos, const QModelIndex &index) {
                qDebug() << "Context menu requested at:" << pos
                         << "for item:" << index.data().toString();
            });
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

    if (!dbManager->loadAdditionalMnemonics()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load additional mnemonics."));
    }

    if (!dbManager->loadConversionFormulas()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load conversion formulas."));
    }

    if (!dbManager->loadMainMnemonics()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load main mnemonics."));
    }

    if (!dbManager->loadSensors()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load sensors."));
    }

    if (!dbManager->loadTools()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load tools."));
    }

    populateTree();
    QMessageBox::information(this, tr("Success"), tr("Database loaded successfully."));
}

void MainWindow::on_actionCompareWithDatabase_triggered()
{
    DatabaseStorage *newStorage = dbManager->loadDataFromDatabase();

    if (newStorage) {
        compareData(newStorage);
        delete newStorage;
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load data for comparison."));
    }
}

void MainWindow::populateTree()
{
    model->clear();
    model->setHorizontalHeaderLabels({"Name"});

    // Tools
    for (const auto &tool : dbStorage->toolList) {
        QStandardItem *toolItem = new QStandardItem(tool->getToolName());

        // Sensors
        for (const auto &sensor : dbStorage->sensorList) {
            if (sensor->getToolId() == tool->getToolId()) {
                QStandardItem *sensorItem = new QStandardItem(sensor->getSensorName());
                toolItem->appendRow(sensorItem);

                // Main Mnemonics
                for (const auto &mainMnemonic : dbStorage->mainMnemonicList) {
                    if (mainMnemonic->getSensorId() == sensor->getSensorId()) {
                        QStandardItem *mainMnemonicItem = new QStandardItem(
                            mainMnemonic->getMainMnemonicName());
                        sensorItem->appendRow(mainMnemonicItem);

                        // Additional Mnemonics
                        for (const auto &additionalMnemonic : dbStorage->additionalMnemonicList) {
                            if (additionalMnemonic->getMainMnemonicId()
                                == mainMnemonic->getMainMnemonicId()) {
                                QStandardItem *additionalMnemonicItem = new QStandardItem(
                                    additionalMnemonic->getAdditionalMnemonicName());
                                mainMnemonicItem->appendRow(additionalMnemonicItem);
                            }
                        }
                    }
                }
            }
        }

        model->appendRow(toolItem);
    }

    ui->treeView->expandAll(); // Automatically expand all items
}

void MainWindow::compareData(DatabaseStorage *newStorage)
{
    QStringList differences;

    // Compare tools
    for (const auto &newTool : newStorage->toolList) {
        bool found = false;
        for (const auto &existingTool : dbStorage->toolList) {
            if (*newTool == *existingTool) {
                found = true;
                break;
            }
        }
        if (!found) {
            differences.append(QString("Tool changed or added: %1").arg(newTool->getToolName()));
        }
    }

    // Compare sensors
    for (const auto &newSensor : newStorage->sensorList) {
        bool found = false;
        for (const auto &existingSensor : dbStorage->sensorList) {
            if (*newSensor == *existingSensor) {
                found = true;
                break;
            }
        }
        if (!found) {
            differences.append(
                QString("Sensor changed or added: %1").arg(newSensor->getSensorName()));
        }
    }

    // Compare main mnemonics
    for (const auto &newMainMnemonic : newStorage->mainMnemonicList) {
        bool found = false;
        for (const auto &existingMainMnemonic : dbStorage->mainMnemonicList) {
            if (*newMainMnemonic == *existingMainMnemonic) {
                found = true;
                break;
            }
        }
        if (!found) {
            differences.append(QString("Main mnemonic changed or added: %1")
                                   .arg(newMainMnemonic->getMainMnemonicName()));
        }
    }

    // Compare additional mnemonics
    for (const auto &newAdditionalMnemonic : newStorage->additionalMnemonicList) {
        bool found = false;
        for (const auto &existingAdditionalMnemonic : dbStorage->additionalMnemonicList) {
            if (*newAdditionalMnemonic == *existingAdditionalMnemonic) {
                found = true;
                break;
            }
        }
        if (!found) {
            differences.append(QString("Additional mnemonic changed or added: %1")
                                   .arg(newAdditionalMnemonic->getAdditionalMnemonicName()));
        }
    }

    // Compare conversion formulas
    for (const auto &newConversionFormula : newStorage->conversionFormulaList) {
        bool found = false;
        for (const auto &existingConversionFormula : dbStorage->conversionFormulaList) {
            if (*newConversionFormula == *existingConversionFormula) {
                found = true;
                break;
            }
        }
        if (!found) {
            differences.append(QString("Conversion formula changed or added: %1")
                                   .arg(newConversionFormula->getFormula()));
        }
    }

    if (differences.isEmpty()) {
        QMessageBox::information(
            this,
            tr("No Differences"),
            tr("No differences found between the current state and the database."));
    } else {
        QMessageBox::information(this,
                                 tr("Differences Found"),
                                 tr("Differences:\n%1").arg(differences.join("\n")));
    }
}
