#include "gui.h"



SearchEngine::SearchEngine(QWidget* parent)
{
	Layout = new QVBoxLayout();
	firstList = new QListWidget();
	secondList = new QListWidget();
	button = new QPushButton("Show best matching");
	search = new QLineEdit();
	label = new QLabel();
	this->setLayout(Layout);
	Layout->addWidget(firstList);
	Layout->addWidget(button);
	Layout->addWidget(search);
	Layout->addWidget(label);
	this->populateList();
	QObject::connect(this->search, &QLineEdit::textChanged, this, &SearchEngine::populateList2);
	QObject::connect(this->button, &QPushButton::clicked, this, &SearchEngine::buttonPressed);
}

void SearchEngine::populateList()
{
	this->firstList->clear();
	for (auto app : this->serv.sortByName())
	{
		this->firstList->addItem(QString::fromStdString(app.toString()));
	}
}

void SearchEngine::populateList2() {
	this->firstList->clear();
	string search = this->search->text().toStdString();
	for (auto app : this->serv.returnAll())
	{	if(app.getName().find(search)!=string::npos || app.getKeys().find(search)!=string::npos)
		this->firstList->addItem(QString::fromStdString(app.toString()));
	}
}

void SearchEngine::buttonPressed() {
	this->label->clear();
	string search = this->search->text().toStdString();
	string bestMatch=" null ";
	double max = -99;
	for (auto app : this->serv.returnAll()) {
		if (app.getName().find(search) != string::npos and search!="")
		{
			string matched = app.getName().substr(app.getName().find(search), search.length());
			double div = double(matched.length() / app.getName().length());
			if (div > max) {
				max = matched.length() / app.getName().length();
				bestMatch = app.getName();
			}
		}
	}
	this->label->setText(QString::fromStdString(bestMatch));
}
