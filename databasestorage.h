#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H

#include <QList>
#include "additionalmnemonic.h"
#include "conversionformula.h"
#include "mainmnemonic.h"
#include "sensor.h"
#include "tool.h"

class DatabaseStorage
{
public:
    void clearAll();

    Tool *findToolById(int toolId);
    Sensor *findSensorById(int sensorId);
    MainMnemonic *findMainMnemonicById(int mainMnemonicId);
    AdditionalMnemonic *findAdditionalMnemonicById(int additionalMnemonicId);
    ConversionFormula *findConversionFormulaById(int formulaId);

    bool addTool(const Tool &tool);
    bool updateTool(const Tool &tool);
    bool deleteTool(int toolId);

    bool addSensor(const Sensor &sensor);
    bool updateSensor(const Sensor &sensor);
    bool deleteSensor(int sensorId);

    bool addMainMnemonic(const MainMnemonic &mainMnemonic);
    bool updateMainMnemonic(const MainMnemonic &mainMnemonic);
    bool deleteMainMnemonic(int mainMnemonicId);

    bool addAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic);
    bool updateAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic);
    bool deleteAdditionalMnemonic(int additionalMnemonicId);

    bool addConversionFormula(const ConversionFormula &conversionFormula);
    bool updateConversionFormula(const ConversionFormula &conversionFormula);
    bool deleteConversionFormula(int formulaId);

    const QList<Tool> &getToolList() const;
    const QList<Sensor> &getSensorList() const;
    const QList<MainMnemonic> &getMainMnemonicList() const;
    const QList<AdditionalMnemonic> &getAdditionalMnemonicList() const;
    const QList<ConversionFormula> &getConversionFormulaList() const;

private:
    QList<Tool> toolList;
    QList<Sensor> sensorList;
    QList<MainMnemonic> mainMnemonicList;
    QList<AdditionalMnemonic> additionalMnemonicList;
    QList<ConversionFormula> conversionFormulaList;
};

#endif // DATABASESTORAGE_H
