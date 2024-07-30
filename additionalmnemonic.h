#ifndef ADDITIONALMNEMONIC_H
#define ADDITIONALMNEMONIC_H

#include <QString>

class AdditionalMnemonic
{
public:
    static AdditionalMnemonic create(int id,
                                     const QString &name,
                                     int companyId,
                                     int mainMnemonicId,
                                     int unitId,
                                     const QString &companyName,
                                     const QString &unitName,
                                     int typeId,
                                     const QString &typeName)
    {
        return AdditionalMnemonic(id,
                                  name,
                                  companyId,
                                  mainMnemonicId,
                                  unitId,
                                  companyName,
                                  unitName,
                                  typeId,
                                  typeName);
    }

    int getAdditionalMnemonicId() const;
    QString getAdditionalMnemonicName() const;
    int getCompanyId() const;
    int getMainMnemonicId() const;
    int getUnitId() const;
    QString getCompanyName() const;
    QString getUnitName() const;
    int getTypeId() const;
    QString getTypeName() const;

    void setAdditionalMnemonicId(int id);
    void setAdditionalMnemonicName(const QString &name);
    void setCompanyId(int id);
    void setMainMnemonicId(int id);
    void setUnitId(int id);
    void setCompanyName(const QString &name);
    void setUnitName(const QString &name);
    void setTypeId(int id);
    void setTypeName(const QString &name);

    bool operator==(const AdditionalMnemonic &other) const;

private:
    AdditionalMnemonic(int id,
                       const QString &name,
                       int companyId,
                       int mainMnemonicId,
                       int unitId,
                       const QString &companyName,
                       const QString &unitName,
                       int typeId,
                       const QString &typeName);
    int additionalMnemonicId;
    QString additionalMnemonicName;
    int companyId;
    int mainMnemonicId;
    int unitId;
    QString companyName;
    QString unitName;
    int typeId;
    QString typeName;
};

#endif // ADDITIONALMNEMONIC_H
