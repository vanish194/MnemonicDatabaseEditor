#include "tooladdwindow.h"
#include "ui_tooladdwindow.h"

ToolAddWindow::ToolAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ToolAddWindow)
{
    ui->setupUi(this);
    connect(ui->button_input, &QPushButton::clicked, this, &ToolAddWindow::onInputClicked);
    connect(ui->button_clean, &QPushButton::clicked, this, &ToolAddWindow::onCleanClicked);
}

ToolAddWindow::~ToolAddWindow()
{
    delete ui;
}

void ToolAddWindow::setToolData(const QString &name,
                                const QString &description,
                                const QString &length,
                                int outerDiameter,
                                int innerDiameter,
                                const QString &imagePath,
                                int producerIndex)
{
    ui->lineEdit_toolName->setText(name);
    ui->lineEdit_description->setText(description);
    ui->lineEdit_length->setText(length);
    ui->spinBox_outerDiameter->setValue(outerDiameter);
    ui->spinBox_innerDiameter->setValue(innerDiameter);
    ui->lineEdit_image->setText(imagePath);
    ui->comboBox_producerName->setCurrentIndex(producerIndex);
}

Tool ToolAddWindow::getToolData() const
{
    Tool tool;
    tool.setToolName(ui->lineEdit_toolName->text());
    tool.setDescription(ui->lineEdit_description->text());
    tool.setLength(ui->lineEdit_length->text());
    tool.setOuterDiameter(ui->spinBox_outerDiameter->value());
    tool.setInnerDiameter(ui->spinBox_innerDiameter->value());
    tool.setImage(ui->lineEdit_image->text().toUtf8()); // Assuming QByteArray conversion
    return tool;
}

void ToolAddWindow::onInputClicked()
{
    accept();
}

void ToolAddWindow::onCleanClicked()
{
    ui->lineEdit_toolName->clear();
    ui->lineEdit_description->clear();
    ui->lineEdit_length->clear();
    ui->spinBox_outerDiameter->setValue(0);
    ui->spinBox_innerDiameter->setValue(0);
    ui->lineEdit_image->clear();
    ui->comboBox_producerName->setCurrentIndex(0);
}
