#include "gui.h"

GUI::GUI(QWidget* parent)
{	
	Layout = new QVBoxLayout{};
	firstList = new QListWidget{};
	secondList = new QListWidget{};
	search = new QLineEdit{};
	label = new QLabel{};
	button = new QPushButton("Find best Match");
	Layout->addWidget(firstList);
	Layout->addWidget(secondList);
	Layout->addWidget(search);
	Layout->addWidget(button);
	Layout->addWidget(label);
	this->setLayout(Layout);
	this->populateList();
	QObject::connect(this->search, &QLineEdit::textChanged, this, &GUI::populateList2);
	QObject::connect(this->button, &QPushButton::clicked, this, &GUI::setLabel);
}

void GUI::populateList()
{
	this->firstList->clear();
	for (auto app : this->serv.sortByName()) {
		this->firstList->addItem(QString::fromStdString(app.toString()));
	};
}

void GUI::populateList2() {
	this->secondList->clear();
	string search = this->search->text().toStdString();
	for (auto app : this->serv.returnAll()) {
		if (app.getName().find(search) != string::npos || app.getkeys().find(search) != string::npos) {
			this->secondList->addItem(QString::fromStdString(app.toString()));
		}
	}
}
void GUI::setLabel() {
	this->label->clear();
	string search = this->search->text().toStdString();
	string bestMatch;
	double max = -99;
	for (auto app : this->serv.returnAll()) {
		if (app.getName().find(search) != string::npos) {
			string matched = app.getName().substr(app.getName().find(search), search.length());
			double div = (matched.length() / app.getName().length());
			if (div > max) {
				max = matched.length() / app.getName().length();
				bestMatch = app.getName();
			}
			//this->secondList->addItem(QString::fromStdString(app.toString()));
		}
	}
	this->label->setText(QString::fromStdString(bestMatch));
}
