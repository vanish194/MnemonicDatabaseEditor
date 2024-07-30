#ifndef SENSOR_H
#define SENSOR_H

#include <QString>

class Sensor
{
public:
    static Sensor *create(int sensorId,
                          int toolId,
                          int methodId,
                          int sensorDescriptionId,
                          const QString &sensorName,
                          const QString &methodName,
                          const QString &toolName,
                          const QString &sensorDescription,
                          const QString &offset);

    Sensor(int sensorId,
           int toolId,
           int methodId,
           int sensorDescriptionId,
           const QString &sensorName,
           const QString &methodName,
           const QString &toolName,
           const QString &sensorDescription,
           const QString &offset);

    // Getters
    int getSensorId() const;
    int getToolId() const;
    int getMethodId() const;
    int getSensorDescriptionId() const;
    QString getSensorName() const;
    QString getMethodName() const;
    QString getToolName() const;
    QString getSensorDescription() const;
    QString getOffset() const;

    // Setters
    void setSensorId(int newSensorId);
    void setToolId(int newToolId);
    void setMethodId(int newMethodId);
    void setSensorDescriptionId(int newSensorDescriptionId);
    void setSensorName(const QString &newSensorName);
    void setMethodName(const QString &newMethodName);
    void setToolName(const QString &newToolName);
    void setSensorDescription(const QString &newSensorDescription);
    void setOffset(const QString &newOffset);

    // Comparison operator
    bool operator==(const Sensor &other) const;

private:
    int sensorId;
    int toolId;
    int methodId;
    int sensorDescriptionId;
    QString sensorName;
    QString methodName;
    QString toolName;
    QString sensorDescription;
    QString offset;
};

#endif // SENSOR_H
