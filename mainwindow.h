#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "biguint.h"
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_Additionbutton_clicked();

    void on_Subtractionbutton_clicked();

    void on_Multiplicationbutton_clicked();

    void on_Divisionbutton_clicked();

    void on_Modulusbutton_clicked();

    void on_Storebutton_clicked();

    void on_Recallbutton_clicked();

    void on_LeftOperand_textChanged(const QString &arg1);

    void on_RightOperand_textChanged(const QString &arg1);

    void on_MemBox_textChanged(const QString &arg1);

    void on_Factorialbutton_clicked();

    void on_Powerbutton_clicked();

private:
    Ui::MainWindow *ui;
    biguint leftOp;
    biguint rightOp;
    biguint memory;
};
#endif // MAINWINDOW_H
