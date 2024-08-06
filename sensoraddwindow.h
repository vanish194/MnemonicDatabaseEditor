#ifndef SENSORADDWINDOW_H
#define SENSORADDWINDOW_H

#include <QDialog>
#include "sensor.h" // Assuming this is the class you are using

namespace Ui {
class SensorAddWindow;
}

class SensorAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SensorAddWindow(QWidget *parent = nullptr);
    ~SensorAddWindow();

    void setSensorData(const QString &name,
                       const QString &description,
                       double offset,
                       int toolIndex,
                       int methodIndex);

    Sensor getSensorData() const; // Assuming you have a Sensor class to return data

    QString getSensorName() const;
    QString getDescription() const;
    double getOffset() const;
    int getToolIndex() const;
    int getMethodIndex() const;

private slots:
    void onInputClicked();
    void onCleanClicked();

private:
    Ui::SensorAddWindow *ui;
};

#endif // SENSORADDWINDOW_H
