#pragma once
#include"Observer.h"
#include"Repository.h"
#include<qwidget.h>
#include<QListWidget>
#include<QLineEdit>
#include<qpushbutton>
#include"Service.h"
#include<qlabel.h>
#include<qmessagebox.h>
class Window : public QWidget, public Observer {
private:
	Service& serv;
	Department& currDepartment;
	QListWidget* listVolunteersWithDepartment;
	QListWidget* listVolunteersNoDepartment;
	QLineEdit* name;
	QLineEdit* listOfInterests;
	QLineEdit* email;
	QPushButton* addVolunteerButton;
	QLabel* descriptionBox;
	QPushButton* assignVolunteer;
	QPushButton* sort;
public:
	Window(Service& serv, Department& currDepartment, QWidget* parent = Q_NULLPTR);
	~Window() override=default;
	void update() override;

public slots:
	void addVolunteer();
	void assignDepartmentToVolunteer();
};