#ifndef CONVERSIONFORMULA_H
#define CONVERSIONFORMULA_H

#include <QString>

class ConversionFormula
{
public:
    static ConversionFormula create(int id,
                                    const QString &formula,
                                    int initialUnitId,
                                    int derivedUnitId)
    {
        return ConversionFormula(id, formula, initialUnitId, derivedUnitId);
    }

    int getFormulaId() const;
    QString getFormula() const;
    int getInitialUnitId() const;
    int getDerivedUnitId() const;

    void setFormulaId(int id);
    void setFormula(const QString &formula);
    void setInitialUnitId(int id);
    void setDerivedUnitId(int id);

    bool operator==(const ConversionFormula &other) const;

private:
    ConversionFormula(int id, const QString &formula, int initialUnitId, int derivedUnitId);
    int formulaId;
    QString formula;
    int initialUnitId;
    int derivedUnitId;
};

#endif // CONVERSIONFORMULA_H
