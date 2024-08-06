#include "mainmnemonicaddwindow.h"
#include "ui_mainmnemonicaddwindow.h"

MainMnemonicAddWindow::MainMnemonicAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMnemonicAddWindow)
{
    ui->setupUi(this);
    connect(ui->button_input, &QPushButton::clicked, this, &MainMnemonicAddWindow::accept);
    connect(ui->button_clean, &QPushButton::clicked, this, &MainMnemonicAddWindow::reject);
}

MainMnemonicAddWindow::~MainMnemonicAddWindow()
{
    delete ui;
}

void MainMnemonicAddWindow::setMainMnemonicData(const QString &name,
                                                const QString &description,
                                                const QString &unitName,
                                                const QString &typeOfUnit,
                                                const QString &sensorName)
{
    ui->lineEdit_mainMnemonicName->setText(name);
    ui->lineEdit_description->setText(description);
    ui->lineEdit_unitName->setText(unitName);
    ui->lineEdit_typeOfUnit->setText(typeOfUnit);
    ui->lineEdit_sensorName->setText(sensorName);
}

MainMnemonic MainMnemonicAddWindow::getMainMnemonicData() const
{
    MainMnemonic mnemonic;
    mnemonic.setMainMnemonicName(ui->lineEdit_mainMnemonicName->text());
    mnemonic.setDescription(ui->lineEdit_description->text());
    mnemonic.setUnitName(ui->lineEdit_unitName->text());
    mnemonic.setTypeName(ui->lineEdit_typeOfUnit->text());
    mnemonic.setSensorName(ui->lineEdit_sensorName->text());
    return mnemonic;
}
