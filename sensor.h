#ifndef SENSOR_H
#define SENSOR_H

#include <QString>

class Sensor
{
public:
    static Sensor create(int sensorId,
                         const QString &sensorName,
                         int toolId,
                         int methodId,
                         int sensorDescriptionId,
                         const QString &sensorDescription,
                         const QString &offset,
                         const QString &methodName);

    int getSensorId() const;
    void setSensorId(int value);

    QString getSensorName() const;
    void setSensorName(const QString &value);

    int getToolId() const;
    void setToolId(int value);

    int getMethodId() const;
    void setMethodId(int value);

    int getSensorDescriptionId() const;
    void setSensorDescriptionId(int value);

    QString getSensorDescription() const;
    void setSensorDescription(const QString &value);

    QString getOffset() const;
    void setOffset(const QString &value);

    QString getMethodName() const;
    void setMethodName(const QString &value);

    bool operator==(const Sensor &other) const;

private:
    Sensor(int sensorId,
           const QString &sensorName,
           int toolId,
           int methodId,
           int sensorDescriptionId,
           const QString &sensorDescription,
           const QString &offset,
           const QString &methodName);

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
