#pragma once
#include<qwidget.h>
#include<qlineedit.h>
#include<qlabel.h>
#include<qstring.h>
#include<qbuttongroup.h>
#include<qpushbutton.h>
#include<qvboxlayout>
#include<vector>
#include<qlistwidget.h>
#include "service.h"
using namespace std;

class GUI : public QWidget {
private:
	Service serv;
	QVBoxLayout* Layout;
	QListWidget* firstList;
	QListWidget* secondList;
	QLineEdit* search;
	QLabel* label;
	QPushButton* button;

public:
	GUI(QWidget* parent = Q_NULLPTR);
	void populateList();
public slots:
	void populateList2();
	void setLabel();

};