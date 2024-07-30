#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "databasestorage.h"

class DatabaseManager
{
public:
    DatabaseManager(DatabaseStorage *storage);
    bool openDatabase(const QString &dbName);
    void closeDatabase();

    bool loadAdditionalMnemonics();
    bool loadConversionFormulas();
    bool loadMainMnemonics();
    bool loadSensors();
    bool loadTools();

    DatabaseStorage *loadDataFromDatabase();

    // Methods for adding, updating, and deleting data
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

private:
    QSqlDatabase db;
    DatabaseStorage *dbStorage;
};

#endif // DATABASEMANAGER_H
