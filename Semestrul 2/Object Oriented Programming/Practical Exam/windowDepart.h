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
class WindowDepart : public QWidget, public Observer {
private:
	Service& serv;
	//Department& currDepartment;
	QListWidget* list;
public:
	WindowDepart(Service& serv, QWidget* parent = Q_NULLPTR);
	~WindowDepart() override = default;
	void update() override;

};