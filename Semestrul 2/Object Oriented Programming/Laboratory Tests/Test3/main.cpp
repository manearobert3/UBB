#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include"gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QtWidgetsApplication1 w;
    SearchEngine gui;
    gui.show();
    return a.exec();
}
