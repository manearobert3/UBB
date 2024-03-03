#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include"Repository.h"
#include"window.h"
#include"windowDepart.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    Repository repo;
    Service serv{ repo };
    for (auto& department : serv.getDepartments()) {
        auto* window = new Window(serv, department);
        window->show();
    }
    auto* windowDepartments = new WindowDepart(serv);
    windowDepartments->show();
    return a.exec();
}
