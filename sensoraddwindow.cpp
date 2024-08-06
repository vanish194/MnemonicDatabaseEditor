#include "sensoraddwindow.h"
#include "ui_sensoraddwindow.h"

SensorAddWindow::SensorAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SensorAddWindow)
{
    ui->setupUi(this);
    connect(ui->button_input, &QPushButton::clicked, this, &SensorAddWindow::onInputClicked);
    connect(ui->button_clean, &QPushButton::clicked, this, &SensorAddWindow::onCleanClicked);
}

SensorAddWindow::~SensorAddWindow()
{
    delete ui;
}

void SensorAddWindow::setSensorData(
    const QString &name, const QString &description, double offset, int toolIndex, int methodIndex)
{
    ui->lineEdit_sensorName->setText(name);
    ui->lineEdit_description->setText(description);
    ui->doubleSpinBox_offset->setValue(offset);
    ui->comboBox_toolName->setCurrentIndex(toolIndex); // Updated to match UI file
    ui->comboBox_method->setCurrentIndex(methodIndex);
}

QString SensorAddWindow::getSensorName() const
{
    return ui->lineEdit_sensorName->text();
}

QString SensorAddWindow::getDescription() const
{
    return ui->lineEdit_description->text();
}

double SensorAddWindow::getOffset() const
{
    return ui->doubleSpinBox_offset->value();
}

int SensorAddWindow::getToolIndex() const
{
    return ui->comboBox_toolName->currentIndex(); // Updated to match UI file
}

int SensorAddWindow::getMethodIndex() const
{
    return ui->comboBox_method->currentIndex();
}

void SensorAddWindow::onInputClicked()
{
    // Логика для сохранения данных
    accept(); // Закрыть диалоговое окно с положительным результатом
}

void SensorAddWindow::onCleanClicked()
{
    ui->lineEdit_sensorName->clear();
    ui->lineEdit_description->clear();
    ui->doubleSpinBox_offset->setValue(0.0);
    ui->comboBox_toolName->setCurrentIndex(0); // Updated to match UI file
    ui->comboBox_method->setCurrentIndex(0);
}
