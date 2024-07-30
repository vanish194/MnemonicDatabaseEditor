#ifndef CONVERSIONFORMULA_H
#define CONVERSIONFORMULA_H

#include <QString>

class ConversionFormula
{
public:
    static ConversionFormula *create(int formulaId,
                                     int initalUnitId,
                                     int derivedUnitId,
                                     const QString &formula,
                                     const QString &initalUnitName,
                                     const QString &derivedUnitName);

    ConversionFormula(int formulaId,
                      int initalUnitId,
                      int derivedUnitId,
                      const QString &formula,
                      const QString &initalUnitName,
                      const QString &derivedUnitName);

    // Getters
    int getFormulaId() const;
    int getInitalUnitId() const;
    int getDerivedUnitId() const;
    QString getFormula() const;
    QString getInitalUnitName() const;
    QString getDerivedUnitName() const;

    // Setters
    void setFormulaId(int newFormulaId);
    void setInitalUnitId(int newInitalUnitId);
    void setDerivedUnitId(int newDerivedUnitId);
    void setFormula(const QString &newFormula);
    void setInitalUnitName(const QString &newInitalUnitName);
    void setDerivedUnitName(const QString &newDerivedUnitName);

    // Comparison operator
    bool operator==(const ConversionFormula &other) const;

private:
    int formulaId;
    int initalUnitId;
    int derivedUnitId;
    QString formula;
    QString initalUnitName;
    QString derivedUnitName;
};

#endif // CONVERSIONFORMULA_H
