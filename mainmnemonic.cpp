#include "mainmnemonic.h"

// Default constructor
MainMnemonic::MainMnemonic()
    : mainMnemonicId(0)
    , sensorId(0)
    , unitId(0)
    , typeId(0)
{}

// Constructor with parameters
MainMnemonic::MainMnemonic(int id,
                           const QString &name,
                           const QString &desc,
                           int sensorId,
                           int unitId,
                           int typeId,
                           const QString &typeName,
                           const QString &unitName)
    : mainMnemonicId(id)
    , mainMnemonicName(name)
    , mainMnemonicDescription(desc)
    , sensorId(sensorId)
    , unitId(unitId)
    , typeId(typeId)
    , typeName(typeName)
    , unitName(unitName)
{}

// Getters
int MainMnemonic::getMainMnemonicId() const
{
    return mainMnemonicId;
}

QString MainMnemonic::getMainMnemonicName() const
{
    return mainMnemonicName;
}

QString MainMnemonic::getMainMnemonicDescription() const
{
    return mainMnemonicDescription;
}

int MainMnemonic::getSensorId() const
{
    return sensorId;
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

// Setters
void MainMnemonic::setMainMnemonicId(int id)
{
    mainMnemonicId = id;
}

void MainMnemonic::setMainMnemonicName(const QString &name)
{
    mainMnemonicName = name;
}

void MainMnemonic::setMainMnemonicDescription(const QString &desc)
{
    mainMnemonicDescription = desc;
}

void MainMnemonic::setSensorId(int id)
{
    sensorId = id;
}

void MainMnemonic::setUnitId(int id)
{
    unitId = id;
}

void MainMnemonic::setTypeId(int id)
{
    typeId = id;
}

void MainMnemonic::setTypeName(const QString &name)
{
    typeName = name;
}

void MainMnemonic::setUnitName(const QString &name)
{
    unitName = name;
}

// Equality operator
bool MainMnemonic::operator==(const MainMnemonic &other) const
{
    return mainMnemonicId == other.mainMnemonicId && mainMnemonicName == other.mainMnemonicName
           && mainMnemonicDescription == other.mainMnemonicDescription && sensorId == other.sensorId
           && unitId == other.unitId && typeId == other.typeId && typeName == other.typeName
           && unitName == other.unitName;
}
