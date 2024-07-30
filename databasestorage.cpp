#include "databasestorage.h"

void DatabaseStorage::clearAll()
{
    toolList.clear();
    sensorList.clear();
    mainMnemonicList.clear();
    additionalMnemonicList.clear();
    conversionFormulaList.clear();
}

Tool *DatabaseStorage::findToolById(int toolId)
{
    for (Tool &tool : toolList) {
        if (tool.getToolId() == toolId) {
            return &tool;
        }
    }
    return nullptr;
}

Sensor *DatabaseStorage::findSensorById(int sensorId)
{
    for (Sensor &sensor : sensorList) {
        if (sensor.getSensorId() == sensorId) {
            return &sensor;
        }
    }
    return nullptr;
}

MainMnemonic *DatabaseStorage::findMainMnemonicById(int mainMnemonicId)
{
    for (MainMnemonic &mainMnemonic : mainMnemonicList) {
        if (mainMnemonic.getMainMnemonicId() == mainMnemonicId) {
            return &mainMnemonic;
        }
    }
    return nullptr;
}

AdditionalMnemonic *DatabaseStorage::findAdditionalMnemonicById(int additionalMnemonicId)
{
    for (AdditionalMnemonic &additionalMnemonic : additionalMnemonicList) {
        if (additionalMnemonic.getAdditionalMnemonicId() == additionalMnemonicId) {
            return &additionalMnemonic;
        }
    }
    return nullptr;
}

ConversionFormula *DatabaseStorage::findConversionFormulaById(int formulaId)
{
    for (ConversionFormula &conversionFormula : conversionFormulaList) {
        if (conversionFormula.getFormulaId() == formulaId) {
            return &conversionFormula;
        }
    }
    return nullptr;
}

bool DatabaseStorage::addTool(const Tool &tool)
{
    Tool *existingTool = findToolById(tool.getToolId());
    if (existingTool) {
        *existingTool = tool;
    } else {
        toolList.append(tool);
    }
    return true;
}

bool DatabaseStorage::updateTool(const Tool &tool)
{
    for (int i = 0; i < toolList.size(); ++i) {
        if (toolList[i].getToolId() == tool.getToolId()) {
            toolList[i] = tool;
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::deleteTool(int toolId)
{
    for (int i = 0; i < toolList.size(); ++i) {
        if (toolList[i].getToolId() == toolId) {
            toolList.removeAt(i);
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::addSensor(const Sensor &sensor)
{
    Sensor *existingSensor = findSensorById(sensor.getSensorId());
    if (existingSensor) {
        *existingSensor = sensor;
    } else {
        sensorList.append(sensor);
    }
    return true;
}

bool DatabaseStorage::updateSensor(const Sensor &sensor)
{
    for (int i = 0; i < sensorList.size(); ++i) {
        if (sensorList[i].getSensorId() == sensor.getSensorId()) {
            sensorList[i] = sensor;
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::deleteSensor(int sensorId)
{
    for (int i = 0; i < sensorList.size(); ++i) {
        if (sensorList[i].getSensorId() == sensorId) {
            sensorList.removeAt(i);
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::addMainMnemonic(const MainMnemonic &mainMnemonic)
{
    MainMnemonic *existingMainMnemonic = findMainMnemonicById(mainMnemonic.getMainMnemonicId());
    if (existingMainMnemonic) {
        *existingMainMnemonic = mainMnemonic;
    } else {
        mainMnemonicList.append(mainMnemonic);
    }
    return true;
}

bool DatabaseStorage::updateMainMnemonic(const MainMnemonic &mainMnemonic)
{
    for (int i = 0; i < mainMnemonicList.size(); ++i) {
        if (mainMnemonicList[i].getMainMnemonicId() == mainMnemonic.getMainMnemonicId()) {
            mainMnemonicList[i] = mainMnemonic;
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::deleteMainMnemonic(int mainMnemonicId)
{
    for (int i = 0; i < mainMnemonicList.size(); ++i) {
        if (mainMnemonicList[i].getMainMnemonicId() == mainMnemonicId) {
            mainMnemonicList.removeAt(i);
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::addAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic)
{
    AdditionalMnemonic *existingAdditionalMnemonic = findAdditionalMnemonicById(
        additionalMnemonic.getAdditionalMnemonicId());
    if (existingAdditionalMnemonic) {
        *existingAdditionalMnemonic = additionalMnemonic;
    } else {
        additionalMnemonicList.append(additionalMnemonic);
    }
    return true;
}

bool DatabaseStorage::updateAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic)
{
    for (int i = 0; i < additionalMnemonicList.size(); ++i) {
        if (additionalMnemonicList[i].getAdditionalMnemonicId()
            == additionalMnemonic.getAdditionalMnemonicId()) {
            additionalMnemonicList[i] = additionalMnemonic;
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::deleteAdditionalMnemonic(int additionalMnemonicId)
{
    for (int i = 0; i < additionalMnemonicList.size(); ++i) {
        if (additionalMnemonicList[i].getAdditionalMnemonicId() == additionalMnemonicId) {
            additionalMnemonicList.removeAt(i);
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::addConversionFormula(const ConversionFormula &conversionFormula)
{
    ConversionFormula *existingConversionFormula = findConversionFormulaById(
        conversionFormula.getFormulaId());
    if (existingConversionFormula) {
        *existingConversionFormula = conversionFormula;
    } else {
        conversionFormulaList.append(conversionFormula);
    }
    return true;
}

bool DatabaseStorage::updateConversionFormula(const ConversionFormula &conversionFormula)
{
    for (int i = 0; i < conversionFormulaList.size(); ++i) {
        if (conversionFormulaList[i].getFormulaId() == conversionFormula.getFormulaId()) {
            conversionFormulaList[i] = conversionFormula;
            return true;
        }
    }
    return false;
}

bool DatabaseStorage::deleteConversionFormula(int formulaId)
{
    for (int i = 0; i < conversionFormulaList.size(); ++i) {
        if (conversionFormulaList[i].getFormulaId() == formulaId) {
            conversionFormulaList.removeAt(i);
            return true;
        }
    }
    return false;
}

const QList<Tool> &DatabaseStorage::getToolList() const
{
    return toolList;
}

const QList<Sensor> &DatabaseStorage::getSensorList() const
{
    return sensorList;
}

const QList<MainMnemonic> &DatabaseStorage::getMainMnemonicList() const
{
    return mainMnemonicList;
}

const QList<AdditionalMnemonic> &DatabaseStorage::getAdditionalMnemonicList() const
{
    return additionalMnemonicList;
}

const QList<ConversionFormula> &DatabaseStorage::getConversionFormulaList() const
{
    return conversionFormulaList;
}
