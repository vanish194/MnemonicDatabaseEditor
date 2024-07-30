#include "conversionformula.h"

ConversionFormula *ConversionFormula::create(int formulaId,
                                             int initalUnitId,
                                             int derivedUnitId,
                                             const QString &formula,
                                             const QString &initalUnitName,
                                             const QString &derivedUnitName)
{
    return new ConversionFormula(formulaId,
                                 initalUnitId,
                                 derivedUnitId,
                                 formula,
                                 initalUnitName,
                                 derivedUnitName);
}

ConversionFormula::ConversionFormula(int formulaId,
                                     int initalUnitId,
                                     int derivedUnitId,
                                     const QString &formula,
                                     const QString &initalUnitName,
                                     const QString &derivedUnitName)
    : formulaId(formulaId)
    , initalUnitId(initalUnitId)
    , derivedUnitId(derivedUnitId)
    , formula(formula)
    , initalUnitName(initalUnitName)
    , derivedUnitName(derivedUnitName)
{}

// Getters
int ConversionFormula::getFormulaId() const
{
    return formulaId;
}
int ConversionFormula::getInitalUnitId() const
{
    return initalUnitId;
}
int ConversionFormula::getDerivedUnitId() const
{
    return derivedUnitId;
}
QString ConversionFormula::getFormula() const
{
    return formula;
}
QString ConversionFormula::getInitalUnitName() const
{
    return initalUnitName;
}
QString ConversionFormula::getDerivedUnitName() const
{
    return derivedUnitName;
}

// Setters
void ConversionFormula::setFormulaId(int newFormulaId)
{
    formulaId = newFormulaId;
}
void ConversionFormula::setInitalUnitId(int newInitalUnitId)
{
    initalUnitId = newInitalUnitId;
}
void ConversionFormula::setDerivedUnitId(int newDerivedUnitId)
{
    derivedUnitId = newDerivedUnitId;
}
void ConversionFormula::setFormula(const QString &newFormula)
{
    formula = newFormula;
}
void ConversionFormula::setInitalUnitName(const QString &newInitalUnitName)
{
    initalUnitName = newInitalUnitName;
}
void ConversionFormula::setDerivedUnitName(const QString &newDerivedUnitName)
{
    derivedUnitName = newDerivedUnitName;
}

// Comparison operator
bool ConversionFormula::operator==(const ConversionFormula &other) const
{
    return formulaId == other.formulaId && initalUnitId == other.initalUnitId
           && derivedUnitId == other.derivedUnitId && formula == other.formula
           && initalUnitName == other.initalUnitName && derivedUnitName == other.derivedUnitName;
}
