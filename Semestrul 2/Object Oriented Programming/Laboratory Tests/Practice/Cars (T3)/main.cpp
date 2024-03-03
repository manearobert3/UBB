#include "PRacticet3.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include <vector>
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //vector<Car>car_list{ Car{"a", 1, "a", "a"} };
    Repository repo("cars.txt");
    Service serv(repo);
    PRacticet3 gui(serv);
    gui.show();
    return a.exec();
}
