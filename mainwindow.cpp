#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "biguint.h"
#include <QMessageBox>
#include <cmath>
#include <Qstring>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    exit(1);
}

void MainWindow::on_Additionbutton_clicked()
{
    leftOp += rightOp;
    ui->LeftOperand->setText(leftOp.toQString());
}

void MainWindow::on_Subtractionbutton_clicked()
{
    leftOp -= rightOp;
    ui->LeftOperand->setText(leftOp.toQString());
}


void MainWindow::on_Multiplicationbutton_clicked()
{
    leftOp *= rightOp;
    ui->LeftOperand->setText(leftOp.toQString());
}



void MainWindow::on_Divisionbutton_clicked()
{
    leftOp /= rightOp;
    ui->LeftOperand->setText(leftOp.toQString());
}


void MainWindow::on_Modulusbutton_clicked()
{
    leftOp %= rightOp;
    ui->LeftOperand->setText(leftOp.toQString());
}


void MainWindow::on_Storebutton_clicked()
{
    memory=leftOp;
    ui->MemBox->setText(memory.toQString());
}

void MainWindow::on_Recallbutton_clicked()
{
    rightOp = memory;
    ui->RightOperand->setText(rightOp.toQString());
}

void MainWindow::on_LeftOperand_textChanged(const QString &arg1)
{
    leftOp = biguint(arg1.toStdString());
    ui->LeftOperand->setText(leftOp.toQString());
}

void MainWindow::on_RightOperand_textChanged(const QString &arg1)
{
    rightOp = biguint(arg1.toStdString());
    ui->RightOperand->setText(rightOp.toQString());
}

void MainWindow::on_MemBox_textChanged(const QString &arg1)
{
    memory = biguint(arg1.toStdString());
    ui->MemBox->setText(memory.toQString());
}

void MainWindow::on_Factorialbutton_clicked()
{
    biguint product(1);
    for(biguint i(1); i <= leftOp; i++){
        product *= i;
    }
    leftOp = product;
    ui->LeftOperand->setText(leftOp.toQString());
}

void MainWindow::on_Powerbutton_clicked()
{
    biguint product(1);
    for(biguint i(1); i <= rightOp; i++){
        product*= leftOp;
    }
    leftOp = product;
    ui->LeftOperand->setText(leftOp.toQString());
}
