#include "additionalmnemonic.h"

AdditionalMnemonic *AdditionalMnemonic::create(int additionalMnemonicId,
                                               int mainMnemonicId,
                                               int companyId,
                                               int unitId,
                                               int typeId,
                                               const QString &typeName,
                                               const QString &unitName,
                                               const QString &additionalMnemonicName,
                                               const QString &mainMnemonicName,
                                               const QString &companyName)
{
    return new AdditionalMnemonic(additionalMnemonicId,
                                  mainMnemonicId,
                                  companyId,
                                  unitId,
                                  typeId,
                                  typeName,
                                  unitName,
                                  additionalMnemonicName,
                                  mainMnemonicName,
                                  companyName);
}

AdditionalMnemonic::AdditionalMnemonic(int additionalMnemonicId,
                                       int mainMnemonicId,
                                       int companyId,
                                       int unitId,
                                       int typeId,
                                       const QString &typeName,
                                       const QString &unitName,
                                       const QString &additionalMnemonicName,
                                       const QString &mainMnemonicName,
                                       const QString &companyName)
    : additionalMnemonicId(additionalMnemonicId)
    , mainMnemonicId(mainMnemonicId)
    , companyId(companyId)
    , unitId(unitId)
    , typeId(typeId)
    , typeName(typeName)
    , unitName(unitName)
    , additionalMnemonicName(additionalMnemonicName)
    , mainMnemonicName(mainMnemonicName)
    , companyName(companyName)
{}

// Getters
int AdditionalMnemonic::getAdditionalMnemonicId() const
{
    return additionalMnemonicId;
}
int AdditionalMnemonic::getMainMnemonicId() const
{
    return mainMnemonicId;
}
int AdditionalMnemonic::getCompanyId() const
{
    return companyId;
}
int AdditionalMnemonic::getUnitId() const
{
    return unitId;
}
int AdditionalMnemonic::getTypeId() const
{
    return typeId;
}
QString AdditionalMnemonic::getTypeName() const
{
    return typeName;
}
QString AdditionalMnemonic::getUnitName() const
{
    return unitName;
}
QString AdditionalMnemonic::getAdditionalMnemonicName() const
{
    return additionalMnemonicName;
}
QString AdditionalMnemonic::getMainMnemonicName() const
{
    return mainMnemonicName;
}
QString AdditionalMnemonic::getCompanyName() const
{
    return companyName;
}

// Setters
void AdditionalMnemonic::setAdditionalMnemonicId(int newAdditionalMnemonicId)
{
    additionalMnemonicId = newAdditionalMnemonicId;
}
void AdditionalMnemonic::setMainMnemonicId(int newMainMnemonicId)
{
    mainMnemonicId = newMainMnemonicId;
}
void AdditionalMnemonic::setCompanyId(int newCompanyId)
{
    companyId = newCompanyId;
}
void AdditionalMnemonic::setUnitId(int newUnitId)
{
    unitId = newUnitId;
}
void AdditionalMnemonic::setTypeId(int newTypeId)
{
    typeId = newTypeId;
}
void AdditionalMnemonic::setTypeName(const QString &newTypeName)
{
    typeName = newTypeName;
}
void AdditionalMnemonic::setUnitName(const QString &newUnitName)
{
    unitName = newUnitName;
}
void AdditionalMnemonic::setAdditionalMnemonicName(const QString &newAdditionalMnemonicName)
{
    additionalMnemonicName = newAdditionalMnemonicName;
}
void AdditionalMnemonic::setMainMnemonicName(const QString &newMainMnemonicName)
{
    mainMnemonicName = newMainMnemonicName;
}
void AdditionalMnemonic::setCompanyName(const QString &newCompanyName)
{
    companyName = newCompanyName;
}

// Comparison operator
bool AdditionalMnemonic::operator==(const AdditionalMnemonic &other) const
{
    return additionalMnemonicId == other.additionalMnemonicId
           && mainMnemonicId == other.mainMnemonicId && companyId == other.companyId
           && unitId == other.unitId && typeId == other.typeId && typeName == other.typeName
           && unitName == other.unitName && additionalMnemonicName == other.additionalMnemonicName
           && mainMnemonicName == other.mainMnemonicName && companyName == other.companyName;
}
