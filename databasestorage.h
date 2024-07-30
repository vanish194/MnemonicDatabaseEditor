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
    DatabaseStorage();

    // Methods for Tool
    void addTool(Tool *tool);
    bool removeTool(int toolId);
    Tool *findToolById(int toolId);

    // Methods for Sensor
    void addSensor(Sensor *sensor);
    bool removeSensor(int sensorId);
    Sensor *findSensorById(int sensorId);

    // Methods for MainMnemonic
    void addMainMnemonic(MainMnemonic *mainMnemonic);
    bool removeMainMnemonic(int mainMnemonicId);
    MainMnemonic *findMainMnemonicById(int mainMnemonicId);

    // Methods for AdditionalMnemonic
    void addAdditionalMnemonic(AdditionalMnemonic *additionalMnemonic);
    bool removeAdditionalMnemonic(int additionalMnemonicId);
    AdditionalMnemonic *findAdditionalMnemonicById(int additionalMnemonicId);

    // Methods for ConversionFormula
    void addConversionFormula(ConversionFormula *conversionFormula);
    bool removeConversionFormula(int formulaId);
    ConversionFormula *findConversionFormulaById(int formulaId);

    QList<Tool *> toolList;
    QList<Sensor *> sensorList;
    QList<MainMnemonic *> mainMnemonicList;
    QList<AdditionalMnemonic *> additionalMnemonicList;
    QList<ConversionFormula *> conversionFormulaList;
};

#endif // DATABASESTORAGE_H
