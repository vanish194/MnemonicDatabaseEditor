#include "sensor.h"

Sensor::Sensor(int sensorId,
               const QString &sensorName,
               int toolId,
               int methodId,
               int sensorDescriptionId,
               const QString &sensorDescription,
               const QString &offset,
               const QString &methodName)
    : sensorId(sensorId)
    , sensorName(sensorName)
    , toolId(toolId)
    , methodId(methodId)
    , sensorDescriptionId(sensorDescriptionId)
    , sensorDescription(sensorDescription)
    , offset(offset)
    , methodName(methodName)
{}

Sensor Sensor::create(int sensorId,
                      const QString &sensorName,
                      int toolId,
                      int methodId,
                      int sensorDescriptionId,
                      const QString &sensorDescription,
                      const QString &offset,
                      const QString &methodName)
{
    return Sensor(sensorId,
                  sensorName,
                  toolId,
                  methodId,
                  sensorDescriptionId,
                  sensorDescription,
                  offset,
                  methodName);
}

int Sensor::getSensorId() const
{
    return sensorId;
}

void Sensor::setSensorId(int value)
{
    sensorId = value;
}

QString Sensor::getSensorName() const
{
    return sensorName;
}

void Sensor::setSensorName(const QString &value)
{
    sensorName = value;
}

int Sensor::getToolId() const
{
    return toolId;
}

void Sensor::setToolId(int value)
{
    toolId = value;
}

int Sensor::getMethodId() const
{
    return methodId;
}

void Sensor::setMethodId(int value)
{
    methodId = value;
}

int Sensor::getSensorDescriptionId() const
{
    return sensorDescriptionId;
}

void Sensor::setSensorDescriptionId(int value)
{
    sensorDescriptionId = value;
}

QString Sensor::getSensorDescription() const
{
    return sensorDescription;
}

void Sensor::setSensorDescription(const QString &value)
{
    sensorDescription = value;
}

QString Sensor::getOffset() const
{
    return offset;
}

void Sensor::setOffset(const QString &value)
{
    offset = value;
}

QString Sensor::getMethodName() const
{
    return methodName;
}

void Sensor::setMethodName(const QString &value)
{
    methodName = value;
}

bool Sensor::operator==(const Sensor &other) const
{
    return sensorId == other.sensorId && sensorName == other.sensorName && toolId == other.toolId
           && methodId == other.methodId && sensorDescriptionId == other.sensorDescriptionId
           && sensorDescription == other.sensorDescription && offset == other.offset
           && methodName == other.methodName;
}
