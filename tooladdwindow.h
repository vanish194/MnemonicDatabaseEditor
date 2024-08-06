#ifndef TOOLADDWINDOW_H
#define TOOLADDWINDOW_H

#include <QDialog>
#include "tool.h" // Assuming this is the class you are using

namespace Ui {
class ToolAddWindow;
}

class ToolAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolAddWindow(QWidget *parent = nullptr);
    ~ToolAddWindow();

    void setToolData(const QString &name,
                     const QString &description,
                     const QString &length,
                     int outerDiameter,
                     int innerDiameter,
                     const QString &imagePath,
                     int producerIndex);
    Tool getToolData() const;

private slots:
    void onInputClicked();
    void onCleanClicked();

    void on_button_input_clicked();

private:
    Ui::ToolAddWindow *ui;
};

#endif // TOOLADDWINDOW_H
