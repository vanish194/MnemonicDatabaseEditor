#include "additionalmnemonic.h"

// Default constructor
AdditionalMnemonic::AdditionalMnemonic()
    : additionalMnemonicId(0)
    , companyId(0)
    , mainMnemonicId(0)
    , unitId(0)
    , typeId(0)
{}

AdditionalMnemonic::AdditionalMnemonic(int id,
                                       const QString &name,
                                       int companyId,
                                       int mainMnemonicId,
                                       int unitId,
                                       const QString &companyName,
                                       const QString &unitName,
                                       int typeId,
                                       const QString &typeName)
    : additionalMnemonicId(id)
    , additionalMnemonicName(name)
    , companyId(companyId)
    , mainMnemonicId(mainMnemonicId)
    , unitId(unitId)
    , companyName(companyName)
    , unitName(unitName)
    , typeId(typeId)
    , typeName(typeName)
{}
int AdditionalMnemonic::getAdditionalMnemonicId() const
{
    return additionalMnemonicId;
}
QString AdditionalMnemonic::getAdditionalMnemonicName() const
{
    return additionalMnemonicName;
}
int AdditionalMnemonic::getCompanyId() const
{
    return companyId;
}
int AdditionalMnemonic::getMainMnemonicId() const
{
    return mainMnemonicId;
}
int AdditionalMnemonic::getUnitId() const
{
    return unitId;
}
QString AdditionalMnemonic::getCompanyName() const
{
    return companyName;
}
QString AdditionalMnemonic::getUnitName() const
{
    return unitName;
}
int AdditionalMnemonic::getTypeId() const
{
    return typeId;
}
QString AdditionalMnemonic::getTypeName() const
{
    return typeName;
}

void AdditionalMnemonic::setAdditionalMnemonicId(int id)
{
    additionalMnemonicId = id;
}
void AdditionalMnemonic::setAdditionalMnemonicName(const QString &name)
{
    additionalMnemonicName = name;
}
void AdditionalMnemonic::setCompanyId(int id)
{
    companyId = id;
}
void AdditionalMnemonic::setMainMnemonicId(int id)
{
    mainMnemonicId = id;
}
void AdditionalMnemonic::setUnitId(int id)
{
    unitId = id;
}
void AdditionalMnemonic::setCompanyName(const QString &name)
{
    companyName = name;
}
void AdditionalMnemonic::setUnitName(const QString &name)
{
    unitName = name;
}
void AdditionalMnemonic::setTypeId(int id)
{
    typeId = id;
}
void AdditionalMnemonic::setTypeName(const QString &name)
{
    typeName = name;
}

bool AdditionalMnemonic::operator==(const AdditionalMnemonic &other) const
{
    return additionalMnemonicId == other.additionalMnemonicId
           && additionalMnemonicName == other.additionalMnemonicName && companyId == other.companyId
           && mainMnemonicId == other.mainMnemonicId && unitId == other.unitId
           && companyName == other.companyName && unitName == other.unitName
           && typeId == other.typeId && typeName == other.typeName;
}
