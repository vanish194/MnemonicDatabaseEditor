#include "mainmnemonic.h"

MainMnemonic *MainMnemonic::create(int sensorId,
                                   int mainMnemonicId,
                                   int unitId,
                                   int typeId,
                                   const QString &typeName,
                                   const QString &unitName,
                                   const QString &mainMnemonicName,
                                   const QString &mainMnemonicDescription,
                                   const QString &sensorName)
{
    return new MainMnemonic(sensorId,
                            mainMnemonicId,
                            unitId,
                            typeId,
                            typeName,
                            unitName,
                            mainMnemonicName,
                            mainMnemonicDescription,
                            sensorName);
}

MainMnemonic::MainMnemonic(int sensorId,
                           int mainMnemonicId,
                           int unitId,
                           int typeId,
                           const QString &typeName,
                           const QString &unitName,
                           const QString &mainMnemonicName,
                           const QString &mainMnemonicDescription,
                           const QString &sensorName)
    : sensorId(sensorId)
    , mainMnemonicId(mainMnemonicId)
    , unitId(unitId)
    , typeId(typeId)
    , typeName(typeName)
    , unitName(unitName)
    , mainMnemonicName(mainMnemonicName)
    , mainMnemonicDescription(mainMnemonicDescription)
    , sensorName(sensorName)
{}

// Getters
int MainMnemonic::getSensorId() const
{
    return sensorId;
}
int MainMnemonic::getMainMnemonicId() const
{
    return mainMnemonicId;
}
int MainMnemonic::getUnitId() const
{
    return unitId;
}
int MainMnemonic::getTypeId() const
{
    return typeId;
}
QString MainMnemonic::getTypeName() const
{
    return typeName;
}
QString MainMnemonic::getUnitName() const
{
    return unitName;
}
QString MainMnemonic::getMainMnemonicName() const
{
    return mainMnemonicName;
}
QString MainMnemonic::getMainMnemonicDescription() const
{
    return mainMnemonicDescription;
}
QString MainMnemonic::getSensorName() const
{
    return sensorName;
}

// Setters
void MainMnemonic::setSensorId(int newSensorId)
{
    sensorId = newSensorId;
}
void MainMnemonic::setMainMnemonicId(int newMainMnemonicId)
{
    mainMnemonicId = newMainMnemonicId;
}
void MainMnemonic::setUnitId(int newUnitId)
{
    unitId = newUnitId;
}
void MainMnemonic::setTypeId(int newTypeId)
{
    typeId = newTypeId;
}
void MainMnemonic::setTypeName(const QString &newTypeName)
{
    typeName = newTypeName;
}
void MainMnemonic::setUnitName(const QString &newUnitName)
{
    unitName = newUnitName;
}
void MainMnemonic::setMainMnemonicName(const QString &newMainMnemonicName)
{
    mainMnemonicName = newMainMnemonicName;
}
void MainMnemonic::setMainMnemonicDescription(const QString &newMainMnemonicDescription)
{
    mainMnemonicDescription = newMainMnemonicDescription;
}
void MainMnemonic::setSensorName(const QString &newSensorName)
{
    sensorName = newSensorName;
}

// Comparison operator
bool MainMnemonic::operator==(const MainMnemonic &other) const
{
    return sensorId == other.sensorId && mainMnemonicId == other.mainMnemonicId
           && unitId == other.unitId && typeId == other.typeId && typeName == other.typeName
           && unitName == other.unitName && mainMnemonicName == other.mainMnemonicName
           && mainMnemonicDescription == other.mainMnemonicDescription
           && sensorName == other.sensorName;
}
