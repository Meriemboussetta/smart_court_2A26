#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "salle.h"
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>


namespace Ui {class MainWindow;}




class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
void on_ajouter_clicked();
void on_supprimer_clicked();


void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_searchbutton_clicked();

private:
    Ui::MainWindow *ui;
    Salle E;
    Salle Etmp;


};

#endif // MAINWINDOW_H
