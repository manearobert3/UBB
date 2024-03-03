#include "PRacticet3.h"
using namespace std;
#include <iostream>
#include <qmessagebox.h>

PRacticet3::PRacticet3(Service& service, QWidget *parent)
    : QMainWindow(parent), service{service}
{
    ui.setupUi(this);
    this->populateAllCarsList();
    this->connectSignalAndSlots();
}

PRacticet3::~PRacticet3()
{}

void PRacticet3::connectSignalAndSlots()
{
    QObject::connect(this->ui.DeletePushButton, &QPushButton::clicked, this, &PRacticet3::deleteCarGUI);
    QObject::connect(this->ui.AddPushButton, &QPushButton::clicked, this, &PRacticet3::addCarGUI);
    QObject::connect(this->ui.updatePushButton, &QPushButton::clicked, this, &PRacticet3::updateCarGUI);
    QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &PRacticet3::populateOldCarsList);
}

int PRacticet3::getSelectedIndex() const
{
    QModelIndexList selected_indexes = this->ui.carListWidget->selectionModel()->selectedIndexes();
    if (selected_indexes.size() == 0) {
        this->ui.NameLineEdit->clear();
        this->ui.yearLineEdit_3->clear();
        this->ui.modelLineEdit_2->clear();
        this->ui.colorLineEdit_4->clear();
        return -1;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

void PRacticet3::addCarGUI()
{
    string name = this->ui.NameLineEdit->text().toStdString();
    int year = this->ui.yearLineEdit_3->text().toInt();
    string model = this->ui.modelLineEdit_2->text().toStdString();
    string color = this->ui.colorLineEdit_4->text().toStdString();

    this->ui.NameLineEdit->clear();
    this->ui.yearLineEdit_3->clear();
    this->ui.modelLineEdit_2->clear();
    this->ui.colorLineEdit_4->clear();

    Car new_car(name, year, model, color);

    this->service.addCarService(new_car);
    this->populateAllCarsList();
}

void PRacticet3::deleteCarGUI()
{
    int selected_index = this->getSelectedIndex();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Error", "No Song Selected");
        return;
    }
    Car car = service.getRepo().getCarList()[selected_index];
    service.deleteCarService(car);
    this->populateAllCarsList();
}

void PRacticet3::updateCarGUI()
{

    string name = this->ui.NameLineEdit->text().toStdString();
    int year = this->ui.yearLineEdit_3->text().toInt();
    string model = this->ui.modelLineEdit_2->text().toStdString();
    string color = this->ui.colorLineEdit_4->text().toStdString();
    Car new_car(name, year, model, color);
    int selected_index = this->getSelectedIndex();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Error", "No song selected");
        return;
    }
    service.updateCarService(selected_index, new_car);
    this->populateAllCarsList();

}

void PRacticet3::listAllCarsGUI()
{
}

void PRacticet3::populateAllCarsList()
{
    this->ui.carListWidget->clear();
    vector<Car> temporary_car_list = this->service.getRepo().getCarList();
    //vector<Car> temporary_car_list{ Car{"a", 1, "a", "a"} };
    for (Car& car : temporary_car_list)
        this->ui.carListWidget->addItem(QString::fromStdString(car.toString()));
}

void PRacticet3::populateOldCarsList()
{
    this->ui.CustomCarListWidget->clear();
    vector<Car>old_cars = this->service.getRepo().getOldCarsList();
    for (auto& car : old_cars) {
        QString carText = QString::fromStdString(car.toString());
        QListWidgetItem* item = new QListWidgetItem(carText);

        // Set the font color to red for the item
        item->setForeground(Qt::red);

        this->ui.CustomCarListWidget->addItem(item);
        //this->ui.CustomCarListWidget->addItem(QString::fromStdString(car.toString()));
        
    }
}

