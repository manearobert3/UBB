#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include"gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // QtWidgetsApplication2 w;
    GUI gui;
    gui.show();
    return a.exec();
}
