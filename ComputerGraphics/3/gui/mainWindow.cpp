#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>
#include <QGridLayout>

#include "../include/mainWindow.h"
#include "../include/drawField.h"

MainWindow::MainWindow(
      double x1, double y1, double z1, 
      double x2, double y2, double z2, 
      double x3, double y3, double z3,
      double x4, double y4, double z4,
    QWidget *parent) : QWidget(parent)
{
    std::string str = "WSADQE – поворот камеры относительно текущей позиции зрителя\t\t\tYI<up><down><left><right> – движение по пространству относительно\n";
    str += "(наклон “головы” вниз, вверх, поворот “головы” влево,\t\t\t\t\tтекущей позиции зрителя (вверх, вниз, вперёд, назад, влево,\n";
    str += "вправо, наклон “головы” влево, вправо СООТВЕТСТВЕННО);\t\t\t\tвправо СООТВЕТСТВЕННО);\n";
    str += "RT - вращение относительно OX (против часовой,\t\t\t\t\tFG – вращение относительно OY (по часовой,\n";
    str += "по часовой СООТВЕТСТВЕННО);\t\t\t\t\t\t\tпротив часовой СООТВЕТСТВЕННО).\n";
    str += "UHJK<space>C – движение по пространству относительно начала осей\n";
    str += "координат (положительно по OX, положительно по OY, отрицательно,\n";
    str += "по OX, отрицательно по OY, положительно по OZ, отрицательно по OZ\n";
    str += "СООТВЕТСТВЕННО);";

    QLabel *label = new QLabel(str.c_str(), this);
    QGridLayout *grid = new QGridLayout(this);

    drawField = new DrawField(this,
       x1,  y1,  z1, 
       x2,  y2,  z2, 
       x3,  y3,  z3,
       x4,  y4,  z4);
    label->setGeometry(0, 0, 200, 100);

    grid->addWidget(label, 0, 0);
    grid->addWidget(drawField, 1, 0);

    grid->setRowStretch(1, 100);

    setLayout(grid);
}

DrawField* MainWindow::getDrawField()
{
    return drawField;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    drawField->keyPressEventFU(event);
}
