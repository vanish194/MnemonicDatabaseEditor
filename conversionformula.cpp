#include "conversionformula.h"

ConversionFormula::ConversionFormula(int id,
                                     const QString &formula,
                                     int initialUnitId,
                                     int derivedUnitId)
    : formulaId(id)
    , formula(formula)
    , initialUnitId(initialUnitId)
    , derivedUnitId(derivedUnitId)
{}

int ConversionFormula::getFormulaId() const
{
    return formulaId;
}
QString ConversionFormula::getFormula() const
{
    return formula;
}
int ConversionFormula::getInitialUnitId() const
{
    return initialUnitId;
}
int ConversionFormula::getDerivedUnitId() const
{
    return derivedUnitId;
}

void ConversionFormula::setFormulaId(int id)
{
    formulaId = id;
}
void ConversionFormula::setFormula(const QString &formula)
{
    this->formula = formula;
}
void ConversionFormula::setInitialUnitId(int id)
{
    initialUnitId = id;
}
void ConversionFormula::setDerivedUnitId(int id)
{
    derivedUnitId = id;
}

bool ConversionFormula::operator==(const ConversionFormula &other) const
{
    return formulaId == other.formulaId && formula == other.formula
           && initialUnitId == other.initialUnitId && derivedUnitId == other.derivedUnitId;
}
