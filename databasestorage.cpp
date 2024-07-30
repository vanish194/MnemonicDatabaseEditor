#include "databasestorage.h"

DatabaseStorage::DatabaseStorage() {}

// Methods for Tool
void DatabaseStorage::addTool(Tool *tool)
{
    Tool *existingTool = findToolById(tool->getToolId());
    if (existingTool) {
        toolList.removeOne(existingTool);
        delete existingTool;
    }
    toolList.append(tool);
}

bool DatabaseStorage::removeTool(int toolId)
{
    Tool *tool = findToolById(toolId);
    if (tool) {
        toolList.removeOne(tool);
        delete tool;
        return true;
    }
    return false;
}

Tool *DatabaseStorage::findToolById(int toolId)
{
    for (Tool *tool : toolList) {
        if (tool->getToolId() == toolId) {
            return tool;
        }
    }
    return nullptr;
}

// Methods for Sensor
void DatabaseStorage::addSensor(Sensor *sensor)
{
    Sensor *existingSensor = findSensorById(sensor->getSensorId());
    if (existingSensor) {
        sensorList.removeOne(existingSensor);
        delete existingSensor;
    }
    sensorList.append(sensor);
}

bool DatabaseStorage::removeSensor(int sensorId)
{
    Sensor *sensor = findSensorById(sensorId);
    if (sensor) {
        sensorList.removeOne(sensor);
        delete sensor;
        return true;
    }
    return false;
}

Sensor *DatabaseStorage::findSensorById(int sensorId)
{
    for (Sensor *sensor : sensorList) {
        if (sensor->getSensorId() == sensorId) {
            return sensor;
        }
    }
    return nullptr;
}

// Methods for MainMnemonic
void DatabaseStorage::addMainMnemonic(MainMnemonic *mainMnemonic)
{
    MainMnemonic *existingMainMnemonic = findMainMnemonicById(mainMnemonic->getMainMnemonicId());
    if (existingMainMnemonic) {
        mainMnemonicList.removeOne(existingMainMnemonic);
        delete existingMainMnemonic;
    }
    mainMnemonicList.append(mainMnemonic);
}

bool DatabaseStorage::removeMainMnemonic(int mainMnemonicId)
{
    MainMnemonic *mainMnemonic = findMainMnemonicById(mainMnemonicId);
    if (mainMnemonic) {
        mainMnemonicList.removeOne(mainMnemonic);
        delete mainMnemonic;
        return true;
    }
    return false;
}

MainMnemonic *DatabaseStorage::findMainMnemonicById(int mainMnemonicId)
{
    for (MainMnemonic *mainMnemonic : mainMnemonicList) {
        if (mainMnemonic->getMainMnemonicId() == mainMnemonicId) {
            return mainMnemonic;
        }
    }
    return nullptr;
}

// Methods for AdditionalMnemonic
void DatabaseStorage::addAdditionalMnemonic(AdditionalMnemonic *additionalMnemonic)
{
    AdditionalMnemonic *existingAdditionalMnemonic = findAdditionalMnemonicById(
        additionalMnemonic->getAdditionalMnemonicId());
    if (existingAdditionalMnemonic) {
        additionalMnemonicList.removeOne(existingAdditionalMnemonic);
        delete existingAdditionalMnemonic;
    }
    additionalMnemonicList.append(additionalMnemonic);
}

bool DatabaseStorage::removeAdditionalMnemonic(int additionalMnemonicId)
{
    AdditionalMnemonic *additionalMnemonic = findAdditionalMnemonicById(additionalMnemonicId);
    if (additionalMnemonic) {
        additionalMnemonicList.removeOne(additionalMnemonic);
        delete additionalMnemonic;
        return true;
    }
    return false;
}

AdditionalMnemonic *DatabaseStorage::findAdditionalMnemonicById(int additionalMnemonicId)
{
    for (AdditionalMnemonic *additionalMnemonic : additionalMnemonicList) {
        if (additionalMnemonic->getAdditionalMnemonicId() == additionalMnemonicId) {
            return additionalMnemonic;
        }
    }
    return nullptr;
}

// Methods for ConversionFormula
void DatabaseStorage::addConversionFormula(ConversionFormula *conversionFormula)
{
    ConversionFormula *existingConversionFormula = findConversionFormulaById(
        conversionFormula->getFormulaId());
    if (existingConversionFormula) {
        conversionFormulaList.removeOne(existingConversionFormula);
        delete existingConversionFormula;
    }
    conversionFormulaList.append(conversionFormula);
}

bool DatabaseStorage::removeConversionFormula(int formulaId)
{
    ConversionFormula *conversionFormula = findConversionFormulaById(formulaId);
    if (conversionFormula) {
        conversionFormulaList.removeOne(conversionFormula);
        delete conversionFormula;
        return true;
    }
    return false;
}

ConversionFormula *DatabaseStorage::findConversionFormulaById(int formulaId)
{
    for (ConversionFormula *conversionFormula : conversionFormulaList) {
        if (conversionFormula->getFormulaId() == formulaId) {
            return conversionFormula;
        }
    }
    return nullptr;
}
