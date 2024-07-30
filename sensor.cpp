#include "sensor.h"

Sensor *Sensor::create(int sensorId,
                       int toolId,
                       int methodId,
                       int sensorDescriptionId,
                       const QString &sensorName,
                       const QString &methodName,
                       const QString &toolName,
                       const QString &sensorDescription,
                       const QString &offset)
{
    return new Sensor(sensorId,
                      toolId,
                      methodId,
                      sensorDescriptionId,
                      sensorName,
                      methodName,
                      toolName,
                      sensorDescription,
                      offset);
}

Sensor::Sensor(int sensorId,
               int toolId,
               int methodId,
               int sensorDescriptionId,
               const QString &sensorName,
               const QString &methodName,
               const QString &toolName,
               const QString &sensorDescription,
               const QString &offset)
    : sensorId(sensorId)
    , toolId(toolId)
    , methodId(methodId)
    , sensorDescriptionId(sensorDescriptionId)
    , sensorName(sensorName)
    , methodName(methodName)
    , toolName(toolName)
    , sensorDescription(sensorDescription)
    , offset(offset)
{}

// Getters
int Sensor::getSensorId() const
{
    return sensorId;
}
int Sensor::getToolId() const
{
    return toolId;
}
int Sensor::getMethodId() const
{
    return methodId;
}
int Sensor::getSensorDescriptionId() const
{
    return sensorDescriptionId;
}
QString Sensor::getSensorName() const
{
    return sensorName;
}
QString Sensor::getMethodName() const
{
    return methodName;
}
QString Sensor::getToolName() const
{
    return toolName;
}
QString Sensor::getSensorDescription() const
{
    return sensorDescription;
}
QString Sensor::getOffset() const
{
    return offset;
}

// Setters
void Sensor::setSensorId(int newSensorId)
{
    sensorId = newSensorId;
}
void Sensor::setToolId(int newToolId)
{
    toolId = newToolId;
}
void Sensor::setMethodId(int newMethodId)
{
    methodId = newMethodId;
}
void Sensor::setSensorDescriptionId(int newSensorDescriptionId)
{
    sensorDescriptionId = newSensorDescriptionId;
}
void Sensor::setSensorName(const QString &newSensorName)
{
    sensorName = newSensorName;
}
void Sensor::setMethodName(const QString &newMethodName)
{
    methodName = newMethodName;
}
void Sensor::setToolName(const QString &newToolName)
{
    toolName = newToolName;
}
void Sensor::setSensorDescription(const QString &newSensorDescription)
{
    sensorDescription = newSensorDescription;
}
void Sensor::setOffset(const QString &newOffset)
{
    offset = newOffset;
}

// Comparison operator
bool Sensor::operator==(const Sensor &other) const
{
    return sensorId == other.sensorId && toolId == other.toolId && methodId == other.methodId
           && sensorDescriptionId == other.sensorDescriptionId && sensorName == other.sensorName
           && methodName == other.methodName && toolName == other.toolName
           && sensorDescription == other.sensorDescription && offset == other.offset;
}
