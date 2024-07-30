#ifndef ADDITIONALMNEMONIC_H
#define ADDITIONALMNEMONIC_H

#include <QString>

class AdditionalMnemonic
{
public:
    static AdditionalMnemonic *create(int additionalMnemonicId,
                                      int mainMnemonicId,
                                      int companyId,
                                      int unitId,
                                      int typeId,
                                      const QString &typeName,
                                      const QString &unitName,
                                      const QString &additionalMnemonicName,
                                      const QString &mainMnemonicName,
                                      const QString &companyName);

    AdditionalMnemonic(int additionalMnemonicId,
                       int mainMnemonicId,
                       int companyId,
                       int unitId,
                       int typeId,
                       const QString &typeName,
                       const QString &unitName,
                       const QString &additionalMnemonicName,
                       const QString &mainMnemonicName,
                       const QString &companyName);

    // Getters
    int getAdditionalMnemonicId() const;
    int getMainMnemonicId() const;
    int getCompanyId() const;
    int getUnitId() const;
    int getTypeId() const;
    QString getTypeName() const;
    QString getUnitName() const;
    QString getAdditionalMnemonicName() const;
    QString getMainMnemonicName() const;
    QString getCompanyName() const;

    // Setters
    void setAdditionalMnemonicId(int newAdditionalMnemonicId);
    void setMainMnemonicId(int newMainMnemonicId);
    void setCompanyId(int newCompanyId);
    void setUnitId(int newUnitId);
    void setTypeId(int newTypeId);
    void setTypeName(const QString &newTypeName);
    void setUnitName(const QString &newUnitName);
    void setAdditionalMnemonicName(const QString &newAdditionalMnemonicName);
    void setMainMnemonicName(const QString &newMainMnemonicName);
    void setCompanyName(const QString &newCompanyName);

    // Comparison operator
    bool operator==(const AdditionalMnemonic &other) const;

private:
    int additionalMnemonicId;
    int mainMnemonicId;
    int companyId;
    int unitId;
    int typeId;
    QString typeName;
    QString unitName;
    QString additionalMnemonicName;
    QString mainMnemonicName;
    QString companyName;
};

#endif // ADDITIONALMNEMONIC_H
