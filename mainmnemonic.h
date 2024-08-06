#ifndef MAINMNEMONIC_H
#define MAINMNEMONIC_H

#include <QString>

class MainMnemonic
{
public:
    // Default constructor
    MainMnemonic();

    // Parameterized constructor
    MainMnemonic(int id,
                 const QString &name,
                 const QString &desc,
                 int sensorId,
                 int unitId,
                 int typeId,
                 const QString &typeName,
                 const QString &unitName);

    // Getters
    int getMainMnemonicId() const;
    QString getMainMnemonicName() const;
    QString getMainMnemonicDescription() const;
    int getSensorId() const;
    int getUnitId() const;
    int getTypeId() const;
    QString getTypeName() const;
    QString getUnitName() const;

    // Setters
    void setMainMnemonicId(int id);
    void setMainMnemonicName(const QString &name);
    void setMainMnemonicDescription(const QString &desc);
    void setSensorId(int id);
    void setUnitId(int id);
    void setTypeId(int id);
    void setTypeName(const QString &name);
    void setUnitName(const QString &name);

    // Equality operator
    bool operator==(const MainMnemonic &other) const;

private:
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
