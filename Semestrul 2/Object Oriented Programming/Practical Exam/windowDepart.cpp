#include "windowDepart.h"
#include<QVBoxLayout>
#include<qmessagebox.h>
#include<string>
#include<sstream>
WindowDepart::WindowDepart(Service& serv, QWidget* parent) : serv{ serv }, QWidget(parent)
{
	this->serv.addObserver(this);
	//this->setWindowTitle(QString::fromStdString(this->currDepartment.getName()));
	auto* layout = new QVBoxLayout(this);
	this->setLayout(layout);
	list = new QListWidget();
	for (auto department : serv.getDepartments()) {
		int contor=0;
		for (auto volunteer : serv.getVolunteers()) {
			if (volunteer.getDepartment() == department.getName())
				contor++;
		}
		std::string departmentString;
		departmentString = department.getName() + "," + std::to_string(contor);
		list->addItem(QString::fromStdString(departmentString));
		}
	layout->addWidget(list);
}

void WindowDepart::update() {
	list->clear();
	for (auto department : serv.getDepartments()) {
		int contor = 0;
		for (auto volunteer : serv.getVolunteers()) {
			if (volunteer.getDepartment() == department.getName())
				contor++;
		}
		std::string departmentString;
		departmentString = department.getName() + "," + std::to_string(contor);
		list->addItem(QString::fromStdString(departmentString));
	}
}