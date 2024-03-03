#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "UI.h"
#include "graphic.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicInterface gui;
    //ui.mainProgram();
    //QtWidgetsApplication1 w;
    gui.show();
    //w.show();
    return a.exec();
}
