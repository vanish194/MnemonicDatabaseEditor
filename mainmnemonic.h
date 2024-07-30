#ifndef MAINMNEMONIC_H
#define MAINMNEMONIC_H

#include <QString>

class MainMnemonic
{
public:
    static MainMnemonic *create(int sensorId,
                                int mainMnemonicId,
                                int unitId,
                                int typeId,
                                const QString &typeName,
                                const QString &unitName,
                                const QString &mainMnemonicName,
                                const QString &mainMnemonicDescription,
                                const QString &sensorName);

    MainMnemonic(int sensorId,
                 int mainMnemonicId,
                 int unitId,
                 int typeId,
                 const QString &typeName,
                 const QString &unitName,
                 const QString &mainMnemonicName,
                 const QString &mainMnemonicDescription,
                 const QString &sensorName);

    // Getters
    int getSensorId() const;
    int getMainMnemonicId() const;
    int getUnitId() const;
    int getTypeId() const;
    QString getTypeName() const;
    QString getUnitName() const;
    QString getMainMnemonicName() const;
    QString getMainMnemonicDescription() const;
    QString getSensorName() const;

    // Setters
    void setSensorId(int newSensorId);
    void setMainMnemonicId(int newMainMnemonicId);
    void setUnitId(int newUnitId);
    void setTypeId(int newTypeId);
    void setTypeName(const QString &newTypeName);
    void setUnitName(const QString &newUnitName);
    void setMainMnemonicName(const QString &newMainMnemonicName);
    void setMainMnemonicDescription(const QString &newMainMnemonicDescription);
    void setSensorName(const QString &newSensorName);

    // Comparison operator
    bool operator==(const MainMnemonic &other) const;

private:
    int sensorId;
    int mainMnemonicId;
    int unitId;
    int typeId;
    QString typeName;
    QString unitName;
    QString mainMnemonicName;
    QString mainMnemonicDescription;
    QString sensorName;
};

#endif // MAINMNEMONIC_H
