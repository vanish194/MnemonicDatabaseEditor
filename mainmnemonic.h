#ifndef MAINMNEMONIC_H
#define MAINMNEMONIC_H

#include <QString>

class MainMnemonic
{
public:
    static MainMnemonic create(int id,
                               const QString &name,
                               const QString &desc,
                               int sensorId,
                               int unitId,
                               int typeId,
                               const QString &typeName,
                               const QString &unitName)
    {
        return MainMnemonic(id, name, desc, sensorId, unitId, typeId, typeName, unitName);
    }

    int getMainMnemonicId() const;
    QString getMainMnemonicName() const;
    QString getMainMnemonicDescription() const;
    int getSensorId() const;
    int getUnitId() const;
    int getTypeId() const;
    QString getTypeName() const;
    QString getUnitName() const;

    void setMainMnemonicId(int id);
    void setMainMnemonicName(const QString &name);
    void setMainMnemonicDescription(const QString &desc);
    void setSensorId(int id);
    void setUnitId(int id);
    void setTypeId(int id);
    void setTypeName(const QString &name);
    void setUnitName(const QString &name);

    bool operator==(const MainMnemonic &other) const;

private:
    MainMnemonic(int id,
                 const QString &name,
                 const QString &desc,
                 int sensorId,
                 int unitId,
                 int typeId,
                 const QString &typeName,
                 const QString &unitName);

    int mainMnemonicId;
    QString mainMnemonicName;
    QString mainMnemonicDescription;
    int sensorId;
    int unitId;
    int typeId;
    QString typeName;
    QString unitName;
};

#endif // MAINMNEMONIC_H
