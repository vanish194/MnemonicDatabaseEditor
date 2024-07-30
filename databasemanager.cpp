#include "databasemanager.h"

DatabaseManager::DatabaseManager(DatabaseStorage *storage)
    : dbStorage(storage)
    , model(new QStandardItemModel)
    , treeModel(new QStandardItemModel)
{}

bool DatabaseManager::openDatabase(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Error: Could not open database." << db.lastError().text();
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
    QSqlQuery query("SELECT am.*, c.company_name, u.unit_name, t.type_name "
                    "FROM additional_mnemonics am "
                    "LEFT JOIN companies c ON am.company_id = c.company_id "
                    "LEFT JOIN units u ON am.unit_id = u.unit_id "
                    "LEFT JOIN types_of_units t ON u.type_id = t.type_id");
    while (query.next()) {
        int id = query.value("additional_mnemonic_id").toInt();
        QString name = query.value("additional_mnemonic_name").toString();
        int companyId = query.value("company_id").toInt();
        int mainMnemonicId = query.value("main_mnemonic_id").toInt();
        int unitId = query.value("unit_id").toInt();
        QString companyName = query.value("company_name").toString();
        QString unitName = query.value("unit_name").toString();
        int typeId = query.value("type_id").toInt();
        QString typeName = query.value("type_name").toString();

        dbStorage->addAdditionalMnemonic(AdditionalMnemonic::create(
            id, name, companyId, mainMnemonicId, unitId, companyName, unitName, typeId, typeName));
    }
    return true;
}

bool DatabaseManager::loadConversionFormulas()
{
    QSqlQuery query("SELECT * FROM conversion_formulas");
    if (!query.exec()) {
        qDebug() << "Error loading conversion formulas:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id = query.value("formula_id").toInt();
        QString formula = query.value("formula").toString();
        int initialUnitId = query.value("inital_unit_id").toInt();
        int derivedUnitId = query.value("derived_unit_id").toInt();

        dbStorage->addConversionFormula(
            ConversionFormula::create(id, formula, initialUnitId, derivedUnitId));
    }
    return true;
}

bool DatabaseManager::loadMainMnemonics()
{
    QSqlQuery query("SELECT mm.*, u.unit_name, t.type_name "
                    "FROM main_mnemonics mm "
                    "LEFT JOIN units u ON mm.unit_id = u.unit_id "
                    "LEFT JOIN types_of_units t ON u.type_id = t.type_id");
    while (query.next()) {
        int id = query.value("main_mnemonic_id").toInt();
        QString name = query.value("main_mnemonic_name").toString();
        QString description = query.value("main_mnemonic_description").toString();
        int sensorId = query.value("sensor_id").toInt();
        int unitId = query.value("unit_id").toInt();
        int typeId = query.value("type_id").toInt();
        QString typeName = query.value("type_name").toString();
        QString unitName = query.value("unit_name").toString();

        dbStorage->addMainMnemonic(
            MainMnemonic::create(id, name, description, sensorId, unitId, typeId, typeName, unitName));
    }
    return true;
}

bool DatabaseManager::loadSensors()
{
    QSqlQuery query(
        "SELECT s.*, sd.sensor_description, sd.offset, m.method_name "
        "FROM sensors s "
        "LEFT JOIN sensor_descriptions sd ON s.sensor_description_id = sd.sensor_description_id "
        "LEFT JOIN methods m ON s.method_id = m.method_id");
    while (query.next()) {
        int id = query.value("sensor_id").toInt();
        QString name = query.value("sensor_name").toString();
        int toolId = query.value("tool_id").toInt();
        int methodId = query.value("method_id").toInt();
        int descId = query.value("sensor_description_id").toInt();
        QString desc = query.value("sensor_description").toString();
        QString offset = query.value("offset").toString();
        QString methodName = query.value("method_name").toString();

        dbStorage->addSensor(
            Sensor::create(id, name, toolId, methodId, descId, desc, offset, methodName));
    }
    return true;
}

bool DatabaseManager::loadTools()
{
    QSqlQuery query(
        "SELECT t.*, td.description, td.length, td.outer_diameter, td.inner_diameter, td.image, "
        "p.produser_name "
        "FROM tools t "
        "LEFT JOIN tool_descriptions td ON t.tool_description_id = td.tool_description_id "
        "LEFT JOIN produsers p ON td.produser_id = p.produser_id");
    while (query.next()) {
        int id = query.value("tool_id").toInt();
        QString name = query.value("tool_name").toString();
        int descId = query.value("tool_description_id").toInt();
        QString description = query.value("description").toString();
        QString length = query.value("length").toString();
        QString outerDiameter = query.value("outer_diameter").toString();
        QString innerDiameter = query.value("inner_diameter").toString();
        QByteArray image = query.value("image").toByteArray();
        int produserId = query.value("produser_id").toInt();
        QString produserName = query.value("produser_name").toString();

        dbStorage->addTool(Tool::create(id,
                                        name,
                                        descId,
                                        description,
                                        length,
                                        outerDiameter,
                                        innerDiameter,
                                        image,
                                        produserId,
                                        produserName));
    }
    return true;
}

DatabaseStorage *DatabaseManager::loadDataFromDatabase()
{
    dbStorage->clearAll();
    if (!loadTools())
        return nullptr;
    if (!loadSensors())
        return nullptr;
    if (!loadMainMnemonics())
        return nullptr;
    if (!loadAdditionalMnemonics())
        return nullptr;
    if (!loadConversionFormulas())
        return nullptr;

    originalDataStorage = *dbStorage;
    currentDataStorage = *dbStorage;
    createTreeModel();
    return dbStorage;
}
QStandardItemModel *DatabaseManager::getModel() const
{
    return model;
}

QStandardItemModel *DatabaseManager::getTreeModel() const
{
    return treeModel;
}

void DatabaseManager::createTreeModel()
{
    treeModel->clear();
    QMap<QString, QMap<QString, QMap<QString, QStringList>>> data_hierarchy;

    const QList<Tool> &tools = dbStorage->getToolList();
    const QList<Sensor> &sensors = dbStorage->getSensorList();
    const QList<MainMnemonic> &mainMnemonics = dbStorage->getMainMnemonicList();
    const QList<AdditionalMnemonic> &additionalMnemonics = dbStorage->getAdditionalMnemonicList();

    for (const Tool &tool : tools) {
        QString toolName = tool.getToolName();
        data_hierarchy[toolName]; // Ensure entry for tool exists

        for (const Sensor &sensor : sensors) {
            if (sensor.getToolId() == tool.getToolId()) {
                QString sensorName = sensor.getSensorName();
                data_hierarchy[toolName][sensorName]; // Ensure entry for sensor exists

                for (const MainMnemonic &mainMnemonic : mainMnemonics) {
                    if (mainMnemonic.getSensorId() == sensor.getSensorId()) {
                        QString mainMnemonicName = mainMnemonic.getMainMnemonicName();
                        data_hierarchy[toolName][sensorName]
                                      [mainMnemonicName]; // Ensure entry for main mnemonic exists

                        for (const AdditionalMnemonic &additionalMnemonic : additionalMnemonics) {
                            if (additionalMnemonic.getMainMnemonicId()
                                == mainMnemonic.getMainMnemonicId()) {
                                QString additionalMnemonicName = additionalMnemonic
                                                                     .getAdditionalMnemonicName();
                                data_hierarchy[toolName][sensorName][mainMnemonicName].append(
                                    additionalMnemonicName);
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto tool_iter = data_hierarchy.begin(); tool_iter != data_hierarchy.end(); ++tool_iter) {
        QStandardItem *tool_item = new QStandardItem(tool_iter.key());
        treeModel->appendRow(tool_item);

        for (auto sensor_iter = tool_iter.value().begin(); sensor_iter != tool_iter.value().end();
             ++sensor_iter) {
            QStandardItem *sensor_item = new QStandardItem(sensor_iter.key());
            tool_item->appendRow(sensor_item);

            for (auto main_iter = sensor_iter.value().begin();
                 main_iter != sensor_iter.value().end();
                 ++main_iter) {
                QStandardItem *main_item = new QStandardItem(main_iter.key());
                sensor_item->appendRow(main_item);

                for (const QString &additional : main_iter.value()) {
                    QStandardItem *additional_item = new QStandardItem(additional);
                    main_item->appendRow(additional_item);
                }
            }
        }
    }
}

bool DatabaseManager::isIdOccupied(const QString &tableName, const QString &idColumn, int id)
{
    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(*) FROM %1 WHERE %2 = :id").arg(tableName).arg(idColumn));
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error checking ID occupation:" << query.lastError().text();
        return false;
    }
    query.next();
    return query.value(0).toInt() > 0;
}

int DatabaseManager::generateUniqueId(const QString &tableName, const QString &idColumn)
{
    QSqlQuery query;
    int id = 1;
    query.prepare(QString("SELECT MAX(%1) FROM %2").arg(idColumn).arg(tableName));
    if (query.exec() && query.next()) {
        id = query.value(0).toInt() + 1;
    }
    return id;
}

bool DatabaseManager::addTool(const Tool &tool)
{
    int toolId = tool.getToolId();
    while (isIdOccupied("tools", "tool_id", toolId)) {
        toolId = generateUniqueId("tools", "tool_id");
    }

    QSqlQuery query;

    query.prepare("INSERT OR IGNORE INTO produsers (produser_id, produser_name) VALUES "
                  "(:produser_id, :produser_name)");
    query.bindValue(":produser_id", tool.getProduserId());
    query.bindValue(":produser_name", tool.getProduserName());

    if (!query.exec()) {
        qDebug() << "Error adding produser:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO tool_descriptions (tool_description_id, description, length, "
                  "outer_diameter, inner_diameter, image, produser_id) "
                  "VALUES (:tool_description_id, :description, :length, :outer_diameter, "
                  ":inner_diameter, :image, :produser_id)");
    query.bindValue(":tool_description_id", tool.getToolDescriptionId());
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

    query.prepare("INSERT INTO tools (tool_id, tool_name, tool_description_id) "
                  "VALUES (:tool_id, :tool_name, :tool_description_id)");
    query.bindValue(":tool_id", toolId);
    query.bindValue(":tool_name", tool.getToolName());
    query.bindValue(":tool_description_id", tool.getToolDescriptionId());

    if (!query.exec()) {
        qDebug() << "Error adding tool:" << query.lastError().text();
        return false;
    }

    dbStorage->addTool(Tool::create(toolId,
                                    tool.getToolName(),
                                    tool.getToolDescriptionId(),
                                    tool.getDescription(),
                                    tool.getLength(),
                                    tool.getOuterDiameter(),
                                    tool.getInnerDiameter(),
                                    tool.getImage(),
                                    tool.getProduserId(),
                                    tool.getProduserName()));
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::updateTool(const Tool &tool)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE produsers SET produser_name = :produser_name WHERE produser_id = :produser_id");
    query.bindValue(":produser_id", tool.getProduserId());
    query.bindValue(":produser_name", tool.getProduserName());

    if (!query.exec()) {
        qDebug() << "Error updating produser:" << query.lastError().text();
        return false;
    }

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

    dbStorage->updateTool(tool);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::deleteTool(int toolId)
{
    QSqlQuery query;

    query.prepare("DELETE FROM tool_descriptions WHERE tool_description_id = (SELECT "
                  "tool_description_id FROM tools WHERE tool_id = :tool_id)");
    query.bindValue(":tool_id", toolId);

    if (!query.exec()) {
        qDebug() << "Error deleting tool description:" << query.lastError().text();
        return false;
    }

    query.prepare("DELETE FROM tools WHERE tool_id = :tool_id");
    query.bindValue(":tool_id", toolId);

    if (!query.exec()) {
        qDebug() << "Error deleting tool:" << query.lastError().text();
        return false;
    }

    dbStorage->deleteTool(toolId);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::addSensor(const Sensor &sensor)
{
    int sensorId = sensor.getSensorId();
    while (isIdOccupied("sensors", "sensor_id", sensorId)) {
        sensorId = generateUniqueId("sensors", "sensor_id");
    }

    QSqlQuery query;

    query.prepare(
        "INSERT OR IGNORE INTO methods (method_id, method_name) VALUES (:method_id, :method_name)");
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":method_name", sensor.getMethodName());

    if (!query.exec()) {
        qDebug() << "Error adding method:" << query.lastError().text();
        return false;
    }

    query.prepare(
        "INSERT INTO sensor_descriptions (sensor_description_id, sensor_description, offset) "
        "VALUES (:sensor_description_id, :sensor_description, :offset)");
    query.bindValue(":sensor_description_id", sensor.getSensorDescriptionId());
    query.bindValue(":sensor_description", sensor.getSensorDescription());
    query.bindValue(":offset", sensor.getOffset());

    if (!query.exec()) {
        qDebug() << "Error adding sensor description:" << query.lastError().text();
        return false;
    }

    query.prepare(
        "INSERT INTO sensors (sensor_id, sensor_name, tool_id, method_id, sensor_description_id) "
        "VALUES (:sensor_id, :sensor_name, :tool_id, :method_id, :sensor_description_id)");
    query.bindValue(":sensor_id", sensorId);
    query.bindValue(":sensor_name", sensor.getSensorName());
    query.bindValue(":tool_id", sensor.getToolId());
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":sensor_description_id", sensor.getSensorDescriptionId());

    if (!query.exec()) {
        qDebug() << "Error adding sensor:" << query.lastError().text();
        return false;
    }

    dbStorage->addSensor(Sensor::create(sensorId,
                                        sensor.getSensorName(),
                                        sensor.getToolId(),
                                        sensor.getMethodId(),
                                        sensor.getSensorDescriptionId(),
                                        sensor.getSensorDescription(),
                                        sensor.getOffset(),
                                        sensor.getMethodName()));
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::updateSensor(const Sensor &sensor)
{
    QSqlQuery query;

    query.prepare(
        "INSERT OR IGNORE INTO methods (method_id, method_name) VALUES (:method_id, :method_name)");
    query.bindValue(":method_id", sensor.getMethodId());
    query.bindValue(":method_name", sensor.getMethodName());

    if (!query.exec()) {
        qDebug() << "Error adding method:" << query.lastError().text();
        return false;
    }

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

    dbStorage->updateSensor(sensor);
    currentDataStorage = *dbStorage;
    return true;
}
bool DatabaseManager::deleteSensor(int sensorId)
{
    QSqlQuery query;

    query.prepare("DELETE FROM sensor_descriptions WHERE sensor_description_id = (SELECT "
                  "sensor_description_id FROM sensors WHERE sensor_id = :sensor_id)");
    query.bindValue(":sensor_id", sensorId);

    if (!query.exec()) {
        qDebug() << "Error deleting sensor description:" << query.lastError().text();
        return false;
    }

    query.prepare("DELETE FROM sensors WHERE sensor_id = :sensor_id");
    query.bindValue(":sensor_id", sensorId);

    if (!query.exec()) {
        qDebug() << "Error deleting sensor:" << query.lastError().text();
        return false;
    }

    dbStorage->deleteSensor(sensorId);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::addMainMnemonic(const MainMnemonic &mainMnemonic)
{
    int mainMnemonicId = mainMnemonic.getMainMnemonicId();
    while (isIdOccupied("main_mnemonics", "main_mnemonic_id", mainMnemonicId)) {
        mainMnemonicId = generateUniqueId("main_mnemonics", "main_mnemonic_id");
    }

    QSqlQuery query;

    // Ensure the unit and type exist before adding the main mnemonic
    query.prepare(
        "INSERT OR IGNORE INTO types_of_units (type_id, type_name) VALUES (:type_id, :type_name)");
    query.bindValue(":type_id", mainMnemonic.getTypeId());
    query.bindValue(":type_name", mainMnemonic.getTypeName());

    if (!query.exec()) {
        qDebug() << "Error adding type:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT OR IGNORE INTO units (unit_id, unit_name, type_id) VALUES (:unit_id, "
                  ":unit_name, :type_id)");
    query.bindValue(":unit_id", mainMnemonic.getUnitId());
    query.bindValue(":unit_name", mainMnemonic.getUnitName());
    query.bindValue(":type_id", mainMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error adding unit:" << query.lastError().text();
        return false;
    }

    // Add the main mnemonic
    query.prepare("INSERT INTO main_mnemonics (main_mnemonic_id, main_mnemonic_name, "
                  "main_mnemonic_description, sensor_id, unit_id) "
                  "VALUES (:main_mnemonic_id, :main_mnemonic_name, :main_mnemonic_description, "
                  ":sensor_id, :unit_id)");
    query.bindValue(":main_mnemonic_id", mainMnemonicId);
    query.bindValue(":main_mnemonic_name", mainMnemonic.getMainMnemonicName());
    query.bindValue(":main_mnemonic_description", mainMnemonic.getMainMnemonicDescription());
    query.bindValue(":sensor_id", mainMnemonic.getSensorId());
    query.bindValue(":unit_id", mainMnemonic.getUnitId());

    if (!query.exec()) {
        qDebug() << "Error adding main mnemonic:" << query.lastError().text();
        return false;
    }

    dbStorage->addMainMnemonic(MainMnemonic::create(mainMnemonicId,
                                                    mainMnemonic.getMainMnemonicName(),
                                                    mainMnemonic.getMainMnemonicDescription(),
                                                    mainMnemonic.getSensorId(),
                                                    mainMnemonic.getUnitId(),
                                                    mainMnemonic.getTypeId(),
                                                    mainMnemonic.getTypeName(),
                                                    mainMnemonic.getUnitName()));
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::updateMainMnemonic(const MainMnemonic &mainMnemonic)
{
    QSqlQuery query;

    // Ensure the unit and type exist before updating the main mnemonic
    query.prepare(
        "INSERT OR IGNORE INTO types_of_units (type_id, type_name) VALUES (:type_id, :type_name)");
    query.bindValue(":type_id", mainMnemonic.getTypeId());
    query.bindValue(":type_name", mainMnemonic.getTypeName());

    if (!query.exec()) {
        qDebug() << "Error adding type:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT OR IGNORE INTO units (unit_id, unit_name, type_id) VALUES (:unit_id, "
                  ":unit_name, :type_id)");
    query.bindValue(":unit_id", mainMnemonic.getUnitId());
    query.bindValue(":unit_name", mainMnemonic.getUnitName());
    query.bindValue(":type_id", mainMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error adding unit:" << query.lastError().text();
        return false;
    }

    // Update the main mnemonic
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

    dbStorage->updateMainMnemonic(mainMnemonic);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::deleteMainMnemonic(int mainMnemonicId)
{
    QSqlQuery query;

    query.prepare("DELETE FROM main_mnemonics WHERE main_mnemonic_id = :main_mnemonic_id");
    query.bindValue(":main_mnemonic_id", mainMnemonicId);

    if (!query.exec()) {
        qDebug() << "Error deleting main mnemonic:" << query.lastError().text();
        return false;
    }

    dbStorage->deleteMainMnemonic(mainMnemonicId);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::addAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic)
{
    int additionalMnemonicId = additionalMnemonic.getAdditionalMnemonicId();
    while (isIdOccupied("additional_mnemonics", "additional_mnemonic_id", additionalMnemonicId)) {
        additionalMnemonicId = generateUniqueId("additional_mnemonics", "additional_mnemonic_id");
    }

    QSqlQuery query;

    // Ensure the unit and type exist before adding the additional mnemonic
    query.prepare(
        "INSERT OR IGNORE INTO types_of_units (type_id, type_name) VALUES (:type_id, :type_name)");
    query.bindValue(":type_id", additionalMnemonic.getTypeId());
    query.bindValue(":type_name", additionalMnemonic.getTypeName());

    if (!query.exec()) {
        qDebug() << "Error adding type:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT OR IGNORE INTO units (unit_id, unit_name, type_id) VALUES (:unit_id, "
                  ":unit_name, :type_id)");
    query.bindValue(":unit_id", additionalMnemonic.getUnitId());
    query.bindValue(":unit_name", additionalMnemonic.getUnitName());
    query.bindValue(":type_id", additionalMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error adding unit:" << query.lastError().text();
        return false;
    }

    // Ensure the company exists before adding the additional mnemonic
    query.prepare("INSERT OR IGNORE INTO companies (company_id, company_name) VALUES (:company_id, "
                  ":company_name)");
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());
    query.bindValue(":company_name", additionalMnemonic.getCompanyName());

    if (!query.exec()) {
        qDebug() << "Error adding company:" << query.lastError().text();
        return false;
    }

    // Add the additional mnemonic
    query.prepare("INSERT INTO additional_mnemonics (additional_mnemonic_id, "
                  "additional_mnemonic_name, company_id, main_mnemonic_id, unit_id) "
                  "VALUES (:additional_mnemonic_id, :additional_mnemonic_name, :company_id, "
                  ":main_mnemonic_id, :unit_id)");
    query.bindValue(":additional_mnemonic_id", additionalMnemonicId);
    query.bindValue(":additional_mnemonic_name", additionalMnemonic.getAdditionalMnemonicName());
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());
    query.bindValue(":main_mnemonic_id", additionalMnemonic.getMainMnemonicId());
    query.bindValue(":unit_id", additionalMnemonic.getUnitId());

    if (!query.exec()) {
        qDebug() << "Error adding additional mnemonic:" << query.lastError().text();
        return false;
    }

    dbStorage->addAdditionalMnemonic(
        AdditionalMnemonic::create(additionalMnemonicId,
                                   additionalMnemonic.getAdditionalMnemonicName(),
                                   additionalMnemonic.getCompanyId(),
                                   additionalMnemonic.getMainMnemonicId(),
                                   additionalMnemonic.getUnitId(),
                                   additionalMnemonic.getCompanyName(),
                                   additionalMnemonic.getUnitName(),
                                   additionalMnemonic.getTypeId(),
                                   additionalMnemonic.getTypeName()));
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::updateAdditionalMnemonic(const AdditionalMnemonic &additionalMnemonic)
{
    QSqlQuery query;

    // Ensure the unit and type exist before updating the additional mnemonic
    query.prepare(
        "INSERT OR IGNORE INTO types_of_units (type_id, type_name) VALUES (:type_id, :type_name)");
    query.bindValue(":type_id", additionalMnemonic.getTypeId());
    query.bindValue(":type_name", additionalMnemonic.getTypeName());

    if (!query.exec()) {
        qDebug() << "Error adding type:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT OR IGNORE INTO units (unit_id, unit_name, type_id) VALUES (:unit_id, "
                  ":unit_name, :type_id)");
    query.bindValue(":unit_id", additionalMnemonic.getUnitId());
    query.bindValue(":unit_name", additionalMnemonic.getUnitName());
    query.bindValue(":type_id", additionalMnemonic.getTypeId());

    if (!query.exec()) {
        qDebug() << "Error adding unit:" << query.lastError().text();
        return false;
    }

    // Ensure the company exists before updating the additional mnemonic
    query.prepare("INSERT OR IGNORE INTO companies (company_id, company_name) VALUES (:company_id, "
                  ":company_name)");
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());
    query.bindValue(":company_name", additionalMnemonic.getCompanyName());

    if (!query.exec()) {
        qDebug() << "Error adding company:" << query.lastError().text();
        return false;
    }

    // Update the additional mnemonic
    query.prepare(
        "UPDATE additional_mnemonics SET additional_mnemonic_name = :additional_mnemonic_name, "
        "company_id = :company_id, main_mnemonic_id = :main_mnemonic_id, unit_id = :unit_id "
        "WHERE additional_mnemonic_id = :additional_mnemonic_id");
    query.bindValue(":additional_mnemonic_id", additionalMnemonic.getAdditionalMnemonicId());
    query.bindValue(":additional_mnemonic_name", additionalMnemonic.getAdditionalMnemonicName());
    query.bindValue(":company_id", additionalMnemonic.getCompanyId());
    query.bindValue(":main_mnemonic_id", additionalMnemonic.getMainMnemonicId());
    query.bindValue(":unit_id", additionalMnemonic.getUnitId());

    if (!query.exec()) {
        qDebug() << "Error updating additional mnemonic:" << query.lastError().text();
        return false;
    }

    dbStorage->updateAdditionalMnemonic(additionalMnemonic);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::deleteAdditionalMnemonic(int additionalMnemonicId)
{
    QSqlQuery query;

    query.prepare(
        "DELETE FROM additional_mnemonics WHERE additional_mnemonic_id = :additional_mnemonic_id");
    query.bindValue(":additional_mnemonic_id", additionalMnemonicId);

    if (!query.exec()) {
        qDebug() << "Error deleting additional mnemonic:" << query.lastError().text();
        return false;
    }

    dbStorage->deleteAdditionalMnemonic(additionalMnemonicId);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::addConversionFormula(const ConversionFormula &conversionFormula)
{
    int formulaId = conversionFormula.getFormulaId();
    while (isIdOccupied("conversion_formulas", "formula_id", formulaId)) {
        formulaId = generateUniqueId("conversion_formulas", "formula_id");
    }

    QSqlQuery query;

    query.prepare(
        "INSERT INTO conversion_formulas (formula_id, formula, inital_unit_id, derived_unit_id) "
        "VALUES (:formula_id, :formula, :inital_unit_id, :derived_unit_id)");
    query.bindValue(":formula_id", formulaId);
    query.bindValue(":formula", conversionFormula.getFormula());
    query.bindValue(":inital_unit_id", conversionFormula.getInitialUnitId());
    query.bindValue(":derived_unit_id", conversionFormula.getDerivedUnitId());

    if (!query.exec()) {
        qDebug() << "Error adding conversion formula:" << query.lastError().text();
        return false;
    }

    dbStorage->addConversionFormula(ConversionFormula::create(formulaId,
                                                              conversionFormula.getFormula(),
                                                              conversionFormula.getInitialUnitId(),
                                                              conversionFormula.getDerivedUnitId()));
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::updateConversionFormula(const ConversionFormula &conversionFormula)
{
    QSqlQuery query;

    query.prepare("UPDATE conversion_formulas SET formula = :formula, inital_unit_id = "
                  ":inital_unit_id, derived_unit_id = :derived_unit_id "
                  "WHERE formula_id = :formula_id");
    query.bindValue(":formula_id", conversionFormula.getFormulaId());
    query.bindValue(":formula", conversionFormula.getFormula());
    query.bindValue(":inital_unit_id", conversionFormula.getInitialUnitId());
    query.bindValue(":derived_unit_id", conversionFormula.getDerivedUnitId());

    if (!query.exec()) {
        qDebug() << "Error updating conversion formula:" << query.lastError().text();
        return false;
    }

    dbStorage->updateConversionFormula(conversionFormula);
    currentDataStorage = *dbStorage;
    return true;
}

bool DatabaseManager::deleteConversionFormula(int formulaId)
{
    QSqlQuery query;

    query.prepare("DELETE FROM conversion_formulas WHERE formula_id = :formula_id");
    query.bindValue(":formula_id", formulaId);

    if (!query.exec()) {
        qDebug() << "Error deleting conversion formula:" << query.lastError().text();
        return false;
    }

    dbStorage->deleteConversionFormula(formulaId);
    currentDataStorage = *dbStorage;
    return true;
}
void DatabaseManager::compareData()
{
    const auto &originalTools = originalDataStorage.getToolList();
    const auto &currentTools = currentDataStorage.getToolList();

    for (int i = 0; i < originalTools.size(); ++i) {
        if (!(originalTools[i] == currentTools[i])) {
            qDebug() << "Difference found in Tools at index" << i;
        }
    }

    const auto &originalSensors = originalDataStorage.getSensorList();
    const auto &currentSensors = currentDataStorage.getSensorList();

    for (int i = 0; i < originalSensors.size(); ++i) {
        if (!(originalSensors[i] == currentSensors[i])) {
            qDebug() << "Difference found in Sensors at index" << i;
        }
    }

    // Implement similar comparison for MainMnemonic, AdditionalMnemonic, and ConversionFormula
}
