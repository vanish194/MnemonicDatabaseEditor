#include "databasemanager.h"

DatabaseManager::DatabaseManager(DatabaseStorage *storage)
    : dbStorage(storage)
{}

bool DatabaseManager::openDatabase(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Error: Could not open database.";
        return false;
    }

    return true;
}

void DatabaseManager::closeDatabase()
{
    db.close();
}

bool DatabaseManager::loadAdditionalMnemonics()
{
    QSqlQuery query;
    QString queryString = R"(
        SELECT
            additional_mnemonics.additional_mnemonic_id,
            main_mnemonics.main_mnemonic_id,
            companies.company_id,
            units.unit_id,
            types_of_units.type_id,
            types_of_units.type_name,
            units.unit_name,
            additional_mnemonics.additional_mnemonic_name,
            main_mnemonics.main_mnemonic_name,
            companies.company_name
        FROM
            additional_mnemonics
            LEFT OUTER JOIN companies ON (additional_mnemonics.company_id = companies.company_id)
            LEFT OUTER JOIN main_mnemonics ON (additional_mnemonics.main_mnemonic_id = main_mnemonics.main_mnemonic_id)
            LEFT OUTER JOIN units ON (additional_mnemonics.unit_id = units.unit_id)
            LEFT OUTER JOIN types_of_units ON (units.type_id = types_of_units.type_id)
    )";

    if (!query.exec(queryString)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int additionalMnemonicId = query.value(0).toInt();
        int mainMnemonicId = query.value(1).toInt();
        int companyId = query.value(2).toInt();
        int unitId = query.value(3).toInt();
        int typeId = query.value(4).toInt();
        QString typeName = query.value(5).toString();
        QString unitName = query.value(6).toString();
        QString additionalMnemonicName = query.value(7).toString();
        QString mainMnemonicName = query.value(8).toString();
        QString companyName = query.value(9).toString();

        AdditionalMnemonic *additionalMnemonic = AdditionalMnemonic::create(additionalMnemonicId,
                                                                            mainMnemonicId,
                                                                            companyId,
                                                                            unitId,
                                                                            typeId,
                                                                            typeName,
                                                                            unitName,
                                                                            additionalMnemonicName,
                                                                            mainMnemonicName,
                                                                            companyName);
        dbStorage->addAdditionalMnemonic(additionalMnemonic);
    }

    return true;
}

bool DatabaseManager::loadConversionFormulas()
{
    QSqlQuery query;
    QString queryString = R"(
        SELECT
            conversion_formulas.formula_id,
            conversion_formulas.inital_unit_id,
            conversion_formulas.derived_unit_id,
            conversion_formulas.formula,
            u1.unit_name AS inital_unit_name,
            u2.unit_name AS derived_unit_name
        FROM
            conversion_formulas
            INNER JOIN units u1 ON conversion_formulas.inital_unit_id = u1.unit_id
            INNER JOIN units u2 ON conversion_formulas.derived_unit_id = u2.unit_id
    )";

    if (!query.exec(queryString)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int formulaId = query.value(0).toInt();
        int initalUnitId = query.value(1).toInt();
        int derivedUnitId = query.value(2).toInt();
        QString formula = query.value(3).toString();
        QString initalUnitName = query.value(4).toString();
        QString derivedUnitName = query.value(5).toString();

        ConversionFormula *conversionFormula = ConversionFormula::create(formulaId,
                                                                         initalUnitId,
                                                                         derivedUnitId,
                                                                         formula,
                                                                         initalUnitName,
                                                                         derivedUnitName);
        dbStorage->addConversionFormula(conversionFormula);
    }

    return true;
}

bool DatabaseManager::loadMainMnemonics()
{
    QSqlQuery query;
    QString queryString = R"(
        SELECT
            sensors.sensor_id,
            main_mnemonics.main_mnemonic_id,
            units.unit_id,
            types_of_units.type_id,
            types_of_units.type_name,
            units.unit_name,
            main_mnemonics.main_mnemonic_name,
            main_mnemonics.main_mnemonic_description,
            sensors.sensor_name
        FROM
            units
            INNER JOIN types_of_units ON (units.type_id = types_of_units.type_id)
            INNER JOIN main_mnemonics ON (units.unit_id = main_mnemonics.unit_id)
            INNER JOIN sensors ON (main_mnemonics.sensor_id = sensors.sensor_id)
    )";

    if (!query.exec(queryString)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int sensorId = query.value(0).toInt();
        int mainMnemonicId = query.value(1).toInt();
        int unitId = query.value(2).toInt();
        int typeId = query.value(3).toInt();
        QString typeName = query.value(4).toString();
        QString unitName = query.value(5).toString();
        QString mainMnemonicName = query.value(6).toString();
        QString mainMnemonicDescription = query.value(7).toString();
        QString sensorName = query.value(8).toString();

        MainMnemonic *mainMnemonic = MainMnemonic::create(sensorId,
                                                          mainMnemonicId,
                                                          unitId,
                                                          typeId,
                                                          typeName,
                                                          unitName,
                                                          mainMnemonicName,
                                                          mainMnemonicDescription,
                                                          sensorName);
        dbStorage->addMainMnemonic(mainMnemonic);
    }

    return true;
}

bool DatabaseManager::loadSensors()
{
    QSqlQuery query;
    QString queryString = R"(
        SELECT
            sensors.sensor_id,
            sensors.tool_id,
            methods.method_id,
            sensor_descriptions.sensor_description_id,
            sensors.sensor_name,
            methods.method_name,
            tools.tool_name,
            sensor_descriptions.sensor_description,
            sensor_descriptions.offset
        FROM
            sensors
            INNER JOIN sensor_descriptions ON (sensors.sensor_description_id = sensor_descriptions.sensor_description_id)
            INNER JOIN methods ON (sensors.method_id = methods.method_id)
            INNER JOIN tools ON (sensors.tool_id = tools.tool_id)
    )";

    if (!query.exec(queryString)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int sensorId = query.value(0).toInt();
        int toolId = query.value(1).toInt();
        int methodId = query.value(2).toInt();
        int sensorDescriptionId = query.value(3).toInt();
        QString sensorName = query.value(4).toString();
        QString methodName = query.value(5).toString();
        QString toolName = query.value(6).toString();
        QString sensorDescription = query.value(7).toString();
        QString offset = query.value(8).toString();

        Sensor *sensor = Sensor::create(sensorId,
                                        toolId,
                                        methodId,
                                        sensorDescriptionId,
                                        sensorName,
                                        methodName,
                                        toolName,
                                        sensorDescription,
                                        offset);
        dbStorage->addSensor(sensor);
    }

    return true;
}

bool DatabaseManager::loadTools()
{
    QSqlQuery query;
    QString queryString = R"(
        SELECT
            tools.tool_id,
            produsers.produser_id,
            tools.tool_description_id,
            tools.tool_name,
            produsers.produser_name,
            tool_descriptions.description,
            tool_descriptions."length",
            tool_descriptions.outer_diameter,
            tool_descriptions.inner_diameter,
            tool_descriptions.image
        FROM
            tools
            LEFT OUTER JOIN tool_descriptions ON (tools.tool_description_id = tool_descriptions.tool_description_id)
            LEFT OUTER JOIN produsers ON (tool_descriptions.produser_id = produsers.produser_id)
    )";

    if (!query.exec(queryString)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int toolId = query.value(0).toInt();
        int produserId = query.value(1).toInt();
        int toolDescriptionId = query.value(2).toInt();
        QString toolName = query.value(3).toString();
        QString produserName = query.value(4).toString();
        QString description = query.value(5).toString();
        QString length = query.value(6).toString();
        QString outerDiameter = query.value(7).toString();
        QString innerDiameter = query.value(8).toString();
        QByteArray image = query.value(9).toByteArray();

        Tool *tool = Tool::create(toolId,
                                  produserId,
                                  toolDescriptionId,
                                  toolName,
                                  produserName,
                                  description,
                                  length,
                                  outerDiameter,
                                  innerDiameter,
                                  image);
        dbStorage->addTool(tool);
    }

    return true;
}

DatabaseStorage *DatabaseManager::loadDataFromDatabase()
{
    DatabaseStorage *newStorage = new DatabaseStorage();

    // Load data into newStorage
    // Note: We assume the database is already opened

    QSqlQuery query;

    // Load additional mnemonics
    QString queryString = R"(
        SELECT
            additional_mnemonics.additional_mnemonic_id,
            main_mnemonics.main_mnemonic_id,
            companies.company_id,
            units.unit_id,
            types_of_units.type_id,
            types_of_units.type_name,
            units.unit_name,
            additional_mnemonics.additional_mnemonic_name,
            main_mnemonics.main_mnemonic_name,
            companies.company_name
        FROM
            additional_mnemonics
            LEFT OUTER JOIN companies ON (additional_mnemonics.company_id = companies.company_id)
            LEFT OUTER JOIN main_mnemonics ON (additional_mnemonics.main_mnemonic_id = main_mnemonics.main_mnemonic_id)
            LEFT OUTER JOIN units ON (additional_mnemonics.unit_id = units.unit_id)
            LEFT OUTER JOIN types_of_units ON (units.type_id = types_of_units.type_id)
    )";

    if (!query.exec(queryString)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        delete newStorage;
        return nullptr;
    }

    while (query.next()) {
        int additionalMnemonicId = query.value(0).toInt();
        int mainMnemonicId = query.value(1).toInt();
        int companyId = query.value(2).toInt();
        int unitId = query.value(3).toInt();
        int typeId = query.value(4).toInt();
        QString typeName = query.value(5).toString();
        QString unitName = query.value(6).toString();
        QString additionalMnemonicName = query.value(7).toString();
        QString mainMnemonicName = query.value(8).toString();
        QString companyName = query.value(9).toString();

        AdditionalMnemonic *additionalMnemonic = AdditionalMnemonic::create(additionalMnemonicId,
                                                                            mainMnemonicId,
                                                                            companyId,
                                                                            unitId,
                                                                            typeId,
                                                                            typeName,
                                                                            unitName,
                                                                            additionalMnemonicName,
                                                                            mainMnemonicName,
                                                                            companyName);
        newStorage->addAdditionalMnemonic(additionalMnemonic);
    }

    // Load other data (sensors, tools, main mnemonics, conversion formulas) in similar manner

    return newStorage;
}
// Methods for adding, updating, and deleting Tools
bool DatabaseManager::addTool(const Tool &tool)
{
    QSqlQuery query;

    // Add produser if not exists
    query.prepare("INSERT OR IGNORE INTO produsers (produser_id, produser_name) VALUES "
                  "(:produser_id, :produser_name)");
    query.bindValue(":produser_id", tool.getProduserId());
    query.bindValue(":produser_name", tool.getProduserName());

    if (!query.exec()) {
        qDebug() << "Error adding produser:" << query.lastError().text();
        return false;
    }

    // Add tool description first
    query.prepare(
        "INSERT INTO tool_descriptions (description, length, outer_diameter, inner_diameter, "
        "image, produser_id) "
        "VALUES (:description, :length, :outer_diameter, :inner_diameter, :image, :produser_id)");
    query.bindValue(":description", tool.getDescription());
    query.bindValue(":length", tool.getLength());
    query.bindValue(":outer_diameter", tool.getOuterDiameter());
    query.bindValue(":inner_diameter", tool.getInnerDiameter());
    query.bindValue(":image", tool.getImage());
    query.bindValue(":produser_id", tool.getProduserId());

    if (!query.exec()) {
        qDebug() << "Error adding tool description:" << query.lastError().text();
        return false;
    }

    int toolDescriptionId = query.lastInsertId().toInt();

    // Add tool
    query.prepare("INSERT INTO tools (tool_name, tool_description_id) "
                  "VALUES (:tool_name, :tool_description_id)");
    query.bindValue(":tool_name", tool.getToolName());
    query.bindValue(":tool_description_id", toolDescriptionId);

    if (!query.exec()) {
        qDebug() << "Error adding tool:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateTool(const Tool &tool)
{
    QSqlQuery query;

    // Update produser if necessary
    query.prepare(
        "UPDATE produsers SET produser_name = :produser_name WHERE produser_id = :produser_id");
    query.bindValue(":produser_id", tool.getProduserId());
    query.bindValue(":produser_name", tool.getProduserName());

    if (!query.exec()) {
        qDebug() << "Error updating produser:" << query.lastError().text();
        return false;
    }

    // Update tool description first
    query.prepare("UPDATE tool_descriptions SET description = :description, length = :length, "
                  "outer_diameter = :outer_diameter, inner_diameter = :inner_diameter, image = "
                  ":image, produser_id = :produser_id "
                  "WHERE tool_description_id = :tool_description_id");
    query.bindValue(":tool_description_id", tool.getToolDescriptionId());
    query.bindValue(":description", tool.getDescription());
    query.bindValue(":length", tool.getLength());
    query.bindValue(":outer_diameter", tool.getOuterDiameter());
    query.bindValue(":inner_diameter", tool.getInnerDiameter());
    query.bindValue(":image", tool.getImage());
    query.bindValue(":produser_id", tool.getProduserId());

    if (!query.exec()) {
        qDebug() << "Error updating tool description:" << query.lastError().text();
        return false;
    }

    // Update tool
    query.prepare(
        "UPDATE tools SET tool_name = :tool_name, tool_description_id = :tool_description_id "
        "WHERE tool_id = :tool_id");
    query.bindValue(":tool_id", tool.getToolId());
    query.bindValue(":tool_name", tool.getToolName());
    query.bindValue(":tool_description_id", tool.getToolDescriptionId());

    if (!query.exec()) {
        qDebug() << "Error updating tool:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteTool(int toolId)
{
    QSqlQuery query;

    // Delete tool description first
    query.prepare("DELETE FROM tool_descriptions WHERE tool_description_id = (SELECT "
                  "tool_description_id FROM tools WHERE tool_id = :tool_id)");
    query.bindValue(":tool_id", toolId);

    if (!query.exec()) {
        qDebug() << "Error deleting tool description:" << query.lastError().text();
        return false;
    }

    // Delete tool
    query.prepare("DELETE FROM tools WHERE tool_id = :tool_id");
    query.bindValue(":tool_id", toolId);

    if (!query.exec()) {
        qDebug() << "Error deleting tool:" << query.lastError().text();
        return false;
    }

    return true;
}

// Methods for adding, updating, and deleting Sensors
bool DatabaseManager::addSensor(const Sensor &sensor)
{
    QSqlQuery query;

    // Add method if not exists
    query.prepare(
        "INSERT OR IGNORE INTO methods (method_id, method_name) VALUES (:method_id, :method_name)");
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":method_name", sensor.getMethodName());

    if (!query.exec()) {
        qDebug() << "Error adding method:" << query.lastError().text();
        return false;
    }

    // Add sensor description first
    query.prepare("INSERT INTO sensor_descriptions (sensor_description, offset) "
                  "VALUES (:sensor_description, :offset)");
    query.bindValue(":sensor_description", sensor.getSensorDescription());
    query.bindValue(":offset", sensor.getOffset());

    if (!query.exec()) {
        qDebug() << "Error adding sensor description:" << query.lastError().text();
        return false;
    }

    int sensorDescriptionId = query.lastInsertId().toInt();

    // Add sensor
    query.prepare("INSERT INTO sensors (sensor_name, tool_id, method_id, sensor_description_id) "
                  "VALUES (:sensor_name, :tool_id, :method_id, :sensor_description_id)");
    query.bindValue(":sensor_name", sensor.getSensorName());
    query.bindValue(":tool_id", sensor.getToolId());
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":sensor_description_id", sensorDescriptionId);

    if (!query.exec()) {
        qDebug() << "Error adding sensor:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateSensor(const Sensor &sensor)
{
    QSqlQuery query;

    // Update method if necessary
    query.prepare("UPDATE methods SET method_name = :method_name WHERE method_id = :method_id");
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":method_name", sensor.getMethodName());

    if (!query.exec()) {
        qDebug() << "Error updating method:" << query.lastError().text();
        return false;
    }

    // Update sensor description first
    query.prepare(
        "UPDATE sensor_descriptions SET sensor_description = :sensor_description, offset = :offset "
        "WHERE sensor_description_id = :sensor_description_id");
    query.bindValue(":sensor_description_id", sensor.getSensorDescriptionId());
    query.bindValue(":sensor_description", sensor.getSensorDescription());
    query.bindValue(":offset", sensor.getOffset());

    if (!query.exec()) {
        qDebug() << "Error updating sensor description:" << query.lastError().text();
        return false;
    }

    // Update sensor
    query.prepare("UPDATE sensors SET sensor_name = :sensor_name, tool_id = :tool_id, method_id = "
                  ":method_id, sensor_description_id = :sensor_description_id "
                  "WHERE sensor_id = :sensor_id");
    query.bindValue(":sensor_id", sensor.getSensorId());
    query.bindValue(":sensor_name", sensor.getSensorName());
    query.bindValue(":tool_id", sensor.getToolId());
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":sensor_description_id", sensor.getSensorDescriptionId());

    if (!query.exec()) {
        qDebug() << "Error updating sensor:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteSensor(int sensorId)
{
    QSqlQuery query;

    // Delete sensor description first
    query.prepare("DELETE FROM sensor_descriptions WHERE sensor_description_id = (SELECT "
                  "sensor_description_id FROM sensors WHERE sensor_id = :sensor_id)");
    query.bindValue(":sensor_id", sensorId);

    if (!query.exec()) {
        qDebug() << "Error deleting sensor description:" << query.lastError().text();
        return false;
    }

    // Delete sensor
    query.prepare("DELETE FROM sensors WHERE sensor_id = :sensor_id");
    query.bindValue(":sensor_id", sensorId);

    if (!query.exec()) {
        qDebug() << "Error deleting sensor:" << query.lastError().text();
        return false;
    }

    return true;
}

// Methods for adding, updating, and deleting Main Mnemonics
bool DatabaseManager::addMainMnemonic(const MainMnemonic &mainMnemonic)
{
    QSqlQuery query;

    // Add type of unit if not exists
    query.prepare(
        "INSERT OR IGNORE INTO types_of_units (type_id, type_name) VALUES (:type_id, :type_name)");
    query.bindValue(":type_id", mainMnemonic.getTypeId());
    query.bindValue(":type_name", mainMnemonic.getTypeName());

    if (!query.exec()) {
        qDebug() << "Error adding type of unit:" << query.lastError().text();
        return false;
    }

    // Add unit
    query.prepare("INSERT INTO units (unit_name, type_id) VALUES (:unit_name, :type_id)");
    query.bindValue(":unit_name", mainMnemonic.getUnitName());
    query.bindValue(":type_id", mainMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error adding unit:" << query.lastError().text();
        return false;
    }

    int unitId = query.lastInsertId().toInt();

    // Add main mnemonic
    query.prepare("INSERT INTO main_mnemonics (main_mnemonic_name, main_mnemonic_description, "
                  "sensor_id, unit_id) "
                  "VALUES (:main_mnemonic_name, :main_mnemonic_description, :sensor_id, :unit_id)");
    query.bindValue(":main_mnemonic_name", mainMnemonic.getMainMnemonicName());
    query.bindValue(":main_mnemonic_description", mainMnemonic.getMainMnemonicDescription());
    query.bindValue(":sensor_id", mainMnemonic.getSensorId());
    query.bindValue(":unit_id", unitId);

    if (!query.exec()) {
        qDebug() << "Error adding main mnemonic:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateMainMnemonic(const MainMnemonic &mainMnemonic)
{
    QSqlQuery query;

    // Update type of unit if necessary
    query.prepare("UPDATE types_of_units SET type_name = :type_name WHERE type_id = :type_id");
    query.bindValue(":type_id", mainMnemonic.getTypeId());
    query.bindValue(":type_name", mainMnemonic.getTypeName());

    if (!query.exec()) {
        qDebug() << "Error updating type of unit:" << query.lastError().text();
        return false;
    }

    // Update unit
    query.prepare(
        "UPDATE units SET unit_name = :unit_name, type_id = :type_id WHERE unit_id = :unit_id");
    query.bindValue(":unit_id", mainMnemonic.getUnitId());
    query.bindValue(":unit_name", mainMnemonic.getUnitName());
    query.bindValue(":type_id", mainMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error updating unit:" << query.lastError().text();
        return false;
    }

    // Update main mnemonic
    query.prepare("UPDATE main_mnemonics SET main_mnemonic_name = :main_mnemonic_name, "
                  "main_mnemonic_description = :main_mnemonic_description, sensor_id = :sensor_id, "
                  "unit_id = :unit_id "
                  "WHERE main_mnemonic_id = :main_mnemonic_id");
    query.bindValue(":main_mnemonic_id", mainMnemonic.getMainMnemonicId());
    query.bindValue(":main_mnemonic_name", mainMnemonic.getMainMnemonicName());
    query.bindValue(":main_mnemonic_description", mainMnemonic.getMainMnemonicDescription());
    query.bindValue(":sensor_id", mainMnemonic.getSensorId());
    query.bindValue(":unit_id", mainMnemonic.getUnitId());

    if (!query.exec()) {
        qDebug() << "Error updating main mnemonic:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteMainMnemonic(int mainMnemonicId)
{
    QSqlQuery query;

    // Delete unit first
    query.prepare("DELETE FROM units WHERE unit_id = (SELECT unit_id FROM main_mnemonics WHERE "
                  "main_mnemonic_id = :main_mnemonic_id)");
    query.bindValue(":main_mnemonic_id", mainMnemonicId);

    if (!query.exec()) {
        qDebug() << "Error deleting unit:" << query.lastError().text();
        return false;
    }

    // Delete main mnemonic
    query.prepare("DELETE FROM main_mnemonics WHERE main_mnemonic_id = :main_mnemonic_id");
    query.bindValue(":main_mnemonic_id", mainMnemonicId);

    if (!query.exec()) {
        qDebug() << "Error deleting main mnemonic:" << query.lastError().text();
        return false;
    }

    return true;
}

// Methods for adding, updating, and deleting Additional Mnemonics
bool DatabaseManager::addAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic)
{
    QSqlQuery query;

    // Add company if not exists
    query.prepare("INSERT OR IGNORE INTO companies (company_id, company_name) VALUES (:company_id, "
                  ":company_name)");
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());
    query.bindValue(":company_name", additionalMnemonic.getCompanyName());

    if (!query.exec()) {
        qDebug() << "Error adding company:" << query.lastError().text();
        return false;
    }

    // Add unit
    query.prepare("INSERT INTO units (unit_name, type_id) VALUES (:unit_name, :type_id)");
    query.bindValue(":unit_name", additionalMnemonic.getUnitName());
    query.bindValue(":type_id", additionalMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error adding unit:" << query.lastError().text();
        return false;
    }

    int unitId = query.lastInsertId().toInt();

    // Add additional mnemonic
    query.prepare("INSERT INTO additional_mnemonics (additional_mnemonic_name, main_mnemonic_id, "
                  "unit_id, company_id) "
                  "VALUES (:additional_mnemonic_name, :main_mnemonic_id, :unit_id, :company_id)");
    query.bindValue(":additional_mnemonic_name", additionalMnemonic.getAdditionalMnemonicName());
    query.bindValue(":main_mnemonic_id", additionalMnemonic.getMainMnemonicId());
    query.bindValue(":unit_id", unitId);
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());

    if (!query.exec()) {
        qDebug() << "Error adding additional mnemonic:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic)
{
    QSqlQuery query;

    // Update company if necessary
    query.prepare(
        "UPDATE companies SET company_name = :company_name WHERE company_id = :company_id");
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());
    query.bindValue(":company_name", additionalMnemonic.getCompanyName());

    if (!query.exec()) {
        qDebug() << "Error updating company:" << query.lastError().text();
        return false;
    }

    // Update unit
    query.prepare(
        "UPDATE units SET unit_name = :unit_name, type_id = :type_id WHERE unit_id = :unit_id");
    query.bindValue(":unit_id", additionalMnemonic.getUnitId());
    query.bindValue(":unit_name", additionalMnemonic.getUnitName());
    query.bindValue(":type_id", additionalMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error updating unit:" << query.lastError().text();
        return false;
    }

    // Update additional mnemonic
    query.prepare(
        "UPDATE additional_mnemonics SET additional_mnemonic_name = :additional_mnemonic_name, "
        "main_mnemonic_id = :main_mnemonic_id, unit_id = :unit_id, company_id = :company_id "
        "WHERE additional_mnemonic_id = :additional_mnemonic_id");
    query.bindValue(":additional_mnemonic_id", additionalMnemonic.getAdditionalMnemonicId());
    query.bindValue(":additional_mnemonic_name", additionalMnemonic.getAdditionalMnemonicName());
    query.bindValue(":main_mnemonic_id", additionalMnemonic.getMainMnemonicId());
    query.bindValue(":unit_id", additionalMnemonic.getUnitId());
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());

    if (!query.exec()) {
        qDebug() << "Error updating additional mnemonic:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteAdditionalMnemonic(int additionalMnemonicId)
{
    QSqlQuery query;

    // Delete unit first
    query.prepare("DELETE FROM units WHERE unit_id = (SELECT unit_id FROM additional_mnemonics "
                  "WHERE additional_mnemonic_id = :additional_mnemonic_id)");
    query.bindValue(":additional_mnemonic_id", additionalMnemonicId);

    if (!query.exec()) {
        qDebug() << "Error deleting unit:" << query.lastError().text();
        return false;
    }

    // Delete additional mnemonic
    query.prepare(
        "DELETE FROM additional_mnemonics WHERE additional_mnemonic_id = :additional_mnemonic_id");
    query.bindValue(":additional_mnemonic_id", additionalMnemonicId);

    if (!query.exec()) {
        qDebug() << "Error deleting additional mnemonic:" << query.lastError().text();
        return false;
    }

    return true;
}

// Methods for adding, updating, and deleting Conversion Formulas
bool DatabaseManager::addConversionFormula(const ConversionFormula &conversionFormula)
{
    QSqlQuery query;

    // Add conversion formula
    query.prepare("INSERT INTO conversion_formulas (formula, inital_unit_id, derived_unit_id) "
                  "VALUES (:formula, :inital_unit_id, :derived_unit_id)");
    query.bindValue(":formula", conversionFormula.getFormula());
    query.bindValue(":inital_unit_id", conversionFormula.getInitalUnitId());
    query.bindValue(":derived_unit_id", conversionFormula.getDerivedUnitId());

    if (!query.exec()) {
        qDebug() << "Error adding conversion formula:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateConversionFormula(const ConversionFormula &conversionFormula)
{
    QSqlQuery query;

    // Update conversion formula
    query.prepare("UPDATE conversion_formulas SET formula = :formula, inital_unit_id = "
                  ":inital_unit_id, derived_unit_id = :derived_unit_id "
                  "WHERE formula_id = :formula_id");
    query.bindValue(":formula_id", conversionFormula.getFormulaId());
    query.bindValue(":formula", conversionFormula.getFormula());
    query.bindValue(":inital_unit_id", conversionFormula.getInitalUnitId());
    query.bindValue(":derived_unit_id", conversionFormula.getDerivedUnitId());

    if (!query.exec()) {
        qDebug() << "Error updating conversion formula:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteConversionFormula(int formulaId)
{
    QSqlQuery query;

    // Delete conversion formula
    query.prepare("DELETE FROM conversion_formulas WHERE formula_id = :formula_id");
    query.bindValue(":formula_id", formulaId);

    if (!query.exec()) {
        qDebug() << "Error deleting conversion formula:" << query.lastError().text();
        return false;
    }

    return true;
}
