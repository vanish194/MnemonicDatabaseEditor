#ifndef ADDITIONALMNEMONICADDWINDOW_H
#define ADDITIONALMNEMONICADDWINDOW_H

#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class AdditionalMnemonicAddWindow;
}

class AdditionalMnemonicAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionalMnemonicAddWindow(QWidget *parent = nullptr);
    ~AdditionalMnemonicAddWindow();

    QString getAdditionalMnemonicName() const;
    int getMainMnemonicIndex() const;
    int getCompanyNameIndex() const;
    int getUnitIndex() const;
    QString getConversionFormula() const;

    void setMainMnemonicIndex(int index);
    void setCompanyNameIndex(int index);
    void setUnitIndex(int index);
    void setAdditionalMnemonicName(const QString &name);
    void setConversionFormula(const QString &formula);

private slots:
    void onCleanClicked();
    void onInputClicked();

private:
    Ui::AdditionalMnemonicAddWindow *ui;
};

#endif // ADDITIONALMNEMONICADDWINDOW_H
