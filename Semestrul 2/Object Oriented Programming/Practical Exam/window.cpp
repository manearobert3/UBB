#include "window.h"
#include<QVBoxLayout>
#include<qmessagebox.h>
#include<string>
#include<sstream>
Window::Window(Service& serv, Department& currDepartment, QWidget* parent) : serv{ serv }, currDepartment{ currDepartment }, QWidget(parent)
{
	this->serv.addObserver(this);
	this->setWindowTitle(QString::fromStdString(this->currDepartment.getName()));
	auto* layout = new QVBoxLayout(this);
	this->setLayout(layout);
	listVolunteersWithDepartment = new QListWidget();
	listVolunteersNoDepartment = new QListWidget();
	QLabel* descriptionBox = new QLabel{ QString::fromStdString(currDepartment.getDescription()) };
	QLabel* descriptionWord = new QLabel{ "Description:" };
	layout->addWidget(descriptionWord);
	layout->addWidget(descriptionBox);
	for (auto volunteer : serv.getVolunteers()) {
		std::string volunteerString;
		if (volunteer.getDepartment() == "")
		{
			volunteerString = volunteer.getName() + "," + volunteer.getEmail() + "," + volunteer.getListOfInterests();
			listVolunteersNoDepartment->addItem(QString::fromStdString(volunteerString));
		}
		else {
			volunteerString = volunteer.getName() + "," + volunteer.getEmail() + "," + volunteer.getListOfInterests() + "," + volunteer.getDepartment();
			listVolunteersWithDepartment->addItem(QString::fromStdString(volunteerString));
		}


	}
	listVolunteersNoDepartment->sortItems(Qt::AscendingOrder);
	listVolunteersWithDepartment->sortItems(Qt::AscendingOrder);
	QLabel* nameLabel = new QLabel{ "Input the name under here: " };
	QLabel* listOfInterestsLabel = new QLabel{ "Input the list of interests under here: " };
	QLabel* emailLabel = new QLabel{ "Input the email under here: " };
	name = new QLineEdit{};
	listOfInterests = new QLineEdit{};
	email = new QLineEdit{};
	addVolunteerButton = new QPushButton{"Add the Volunteer"};
	assignVolunteer = new QPushButton{ "assign volunteer to department" };
	sort = new QPushButton{ "Sort by the three best" };
	layout->addWidget(listVolunteersWithDepartment);
	layout->addWidget(listVolunteersNoDepartment);
	layout->addWidget(nameLabel);
	layout->addWidget(name);
	layout->addWidget(listOfInterestsLabel);
	layout->addWidget(listOfInterests);
	layout->addWidget(emailLabel);
	layout->addWidget(email);
	layout->addWidget(addVolunteerButton);
	layout->addWidget(assignVolunteer);
	QObject::connect(addVolunteerButton, &QPushButton::clicked, this, &Window::addVolunteer);
	QObject::connect(assignVolunteer, &QPushButton::clicked, this, &Window::assignDepartmentToVolunteer);
}


void Window::addVolunteer() {
	std::string listInterests, nameString, emailString;
	nameString = name->text().toStdString();
	listInterests = listOfInterests->text().toStdString();
	emailString = email->text().toStdString();
	if (name->text().isEmpty() or email->text().isEmpty())
	{
		std::string error = "Not a valid name or email";
		QMessageBox::warning(this, "Warning", QString::fromStdString(error));
	}
	else {
		this->serv.addVolunteer(nameString, emailString, listInterests);
	}

}

void Window::update() {
	//this->serv.sortRepo();
	listVolunteersNoDepartment->clear();
	listVolunteersWithDepartment->clear();
	for (auto volunteer : serv.getVolunteers()) {
			std::string volunteerString;
			if (volunteer.getDepartment() == "")
			{
				volunteerString = volunteer.getName() + "," + volunteer.getEmail() + "," + volunteer.getListOfInterests();
				listVolunteersNoDepartment->addItem(QString::fromStdString(volunteerString));
			}
			else {
				volunteerString = volunteer.getName() + "," + volunteer.getEmail() + "," + volunteer.getListOfInterests() + "," + volunteer.getDepartment();
				listVolunteersWithDepartment->addItem(QString::fromStdString(volunteerString));
			}


		}
	listVolunteersNoDepartment->sortItems(Qt::AscendingOrder);
	listVolunteersWithDepartment->sortItems(Qt::AscendingOrder);
}

void Window::assignDepartmentToVolunteer()
{
	QListWidgetItem* selectedItem = listVolunteersNoDepartment->currentItem();
	char del = ',';
	std::string currentItem, name, email;
	QString selectedItemQString = selectedItem->text();
	currentItem = selectedItemQString.toStdString();
	std::stringstream ss(currentItem);
	std::getline(ss, name, del);
	std::getline(ss, email, del);
	for (auto& volunteer : this->serv.getVolunteers()) {
		if (volunteer.getName() == name && volunteer.getEmail() == email) {
			volunteer.setDepartment(currDepartment.getName());
		}
	}
	this->serv.notifyObs();
}
