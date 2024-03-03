#pragma once
#include <qwidget.h>
#include<qlineedit.h>
#include<qpushbutton.h>
#include<qstring.h>
#include<qlistview.h>
#include<qlistview.h>
#include<qvboxlayout>
#include "service.h"
#include <qlistwidget.h>
#include<qlabel.h>

class SearchEngine: public QWidget {
private:
	Service serv;
	QVBoxLayout* Layout;
	QListWidget* firstList;
	QListWidget* secondList;
	QPushButton* button;
	QLineEdit* search;
	QLabel* label;

public:
	SearchEngine(QWidget* parent = Q_NULLPTR);
	~SearchEngine() {};
	void populateList();
public slots:
	void populateList2();
	void buttonPressed();
};