#include "additionalmnemonicaddwindow.h"
#include "ui_additionalmnemonicaddwindow.h"

AdditionalMnemonicAddWindow::AdditionalMnemonicAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdditionalMnemonicAddWindow)
{
    ui->setupUi(this);

    connect(ui->button_clean,
            &QPushButton::clicked,
            this,
            &AdditionalMnemonicAddWindow::onCleanClicked);
    connect(ui->button_input,
            &QPushButton::clicked,
            this,
            &AdditionalMnemonicAddWindow::onInputClicked);
}

AdditionalMnemonicAddWindow::~AdditionalMnemonicAddWindow()
{
    delete ui;
}

QString AdditionalMnemonicAddWindow::getAdditionalMnemonicName() const
{
    return ui->lineEdit_additionalMnemonic->text();
}

int AdditionalMnemonicAddWindow::getMainMnemonicIndex() const
{
    return ui->comboBox_mainMnemonic->currentIndex();
}

int AdditionalMnemonicAddWindow::getCompanyNameIndex() const
{
    return ui->comboBox_companyName->currentIndex();
}

int AdditionalMnemonicAddWindow::getUnitIndex() const
{
    return ui->comboBox_unit->currentIndex();
}

QString AdditionalMnemonicAddWindow::getConversionFormula() const
{
    return ui->lineEdit_conversionFormula->text();
}

void AdditionalMnemonicAddWindow::setMainMnemonicIndex(int index)
{
    ui->comboBox_mainMnemonic->setCurrentIndex(index);
}

void AdditionalMnemonicAddWindow::setCompanyNameIndex(int index)
{
    ui->comboBox_companyName->setCurrentIndex(index);
}

void AdditionalMnemonicAddWindow::setUnitIndex(int index)
{
    ui->comboBox_unit->setCurrentIndex(index);
}

void AdditionalMnemonicAddWindow::setAdditionalMnemonicName(const QString &name)
{
    ui->lineEdit_additionalMnemonic->setText(name);
}

void AdditionalMnemonicAddWindow::setConversionFormula(const QString &formula)
{
    ui->lineEdit_conversionFormula->setText(formula);
}

void AdditionalMnemonicAddWindow::onCleanClicked()
{
    // Clear all inputs
    ui->lineEdit_additionalMnemonic->clear();
    ui->lineEdit_conversionFormula->clear();
    ui->comboBox_mainMnemonic->setCurrentIndex(-1);
    ui->comboBox_companyName->setCurrentIndex(-1);
    ui->comboBox_unit->setCurrentIndex(-1);
}

void AdditionalMnemonicAddWindow::onInputClicked()
{
    accept(); // Closes the window and signals acceptance of the data entered
}
