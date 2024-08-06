#ifndef MAINMNEMONICADDWINDOW_H
#define MAINMNEMONICADDWINDOW_H

#include <QDialog>
#include "mainmnemonic.h"

namespace Ui {
class MainMnemonicAddWindow;
}

class MainMnemonicAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainMnemonicAddWindow(QWidget *parent = nullptr);
    ~MainMnemonicAddWindow();

    void setMainMnemonicData(const QString &name,
                             const QString &description,
                             const QString &unitName,
                             const QString &typeOfUnit,
                             const QString &sensorName);
    MainMnemonic getMainMnemonicData() const;

private:
    Ui::MainMnemonicAddWindow *ui;
};

#endif // MAINMNEMONICADDWINDOW_H
