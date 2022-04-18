// main window class

#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>

#include "../include/drawField.h"

class MainWindow : public QWidget
{

    Q_OBJECT

    private:
    DrawField *drawField;

    public:
    MainWindow(
      double x1, double y1, double z1, 
      double x2, double y2, double z2, 
      double x3, double y3, double z3,
      double x4, double y4, double z4
    , QWidget *parent = 0);

    DrawField* getDrawField();

    protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H