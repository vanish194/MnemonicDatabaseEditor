#ifndef SENSOR_H
#define SENSOR_H

#include <QString>

class Sensor
{
public:
    Sensor(); // Default constructor
    Sensor(int sensorId,
           const QString &sensorName,
           int toolId,
           int methodId,
           int sensorDescriptionId,
           const QString &sensorDescription,
           const QString &offset,
           const QString &methodName);

    // Getters
    int getSensorId() const;
    QString getSensorName() const;
    int getToolId() const;
    int getMethodId() const;
    int getSensorDescriptionId() const;
    QString getSensorDescription() const;
    QString getOffset() const;
    QString getMethodName() const;

    // Setters
    void setSensorId(int value);
    void setSensorName(const QString &value);
    void setToolId(int value);
    void setMethodId(int value);
    void setSensorDescriptionId(int value);
    void setSensorDescription(const QString &value);
    void setOffset(const QString &value);
    void setMethodName(const QString &value);

    // Equality operator
    bool operator==(const Sensor &other) const;

private:
    int sensorId;
    QString sensorName;
    int toolId;
    int methodId;
    int sensorDescriptionId;
    QString sensorDescription;
    QString offset;
    QString methodName;
};

#endif // SENSOR_H
