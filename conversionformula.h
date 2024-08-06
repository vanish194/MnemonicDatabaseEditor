#ifndef CONVERSIONFORMULA_H
#define CONVERSIONFORMULA_H

#include <QString>

class ConversionFormula
{
public:
    ConversionFormula(); // Default constructor
    ConversionFormula(int id, const QString &formula, int initialUnitId, int derivedUnitId);

    // Getters
    int getFormulaId() const;
    QString getFormula() const;
    int getInitialUnitId() const;
    int getDerivedUnitId() const;

    // Setters
    void setFormulaId(int id);
    void setFormula(const QString &formula);
    void setInitialUnitId(int id);
    void setDerivedUnitId(int id);

    // Equality operator
    bool operator==(const ConversionFormula &other) const;

private:
    int formulaId;
    QString formula;
    int initialUnitId;
    int derivedUnitId;
};

#endif // CONVERSIONFORMULA_H
