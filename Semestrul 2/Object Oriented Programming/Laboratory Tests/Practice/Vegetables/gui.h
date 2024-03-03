#pragma once
#include<QWidget>
#include<QListWidget>
#include<QPushButton>
#include <qlabel.h>
#include<qlineedit>
#include<qvboxlayout>
#include "repository.h"
#include<vector>
#include<qstring.h>
using namespace std;
class GUI : public QWidget
{
private:
	Repository repo;
	QVBoxLayout* mainLay;
	QListWidget* listOfAllVeg;
	QListWidget* listOfSpecVeg;
	QLineEdit* searchByVegLine;
	QLineEdit* calculateSum;
	QPushButton* searchByVegBut;
	QPushButton* CalculateButton;
	QLabel* numberVeg;
public:
	GUI(QWidget* parent = Q_NULLPTR);
	void populateList();
public slots:
	void searchByVeg(QListWidgetItem* item);
	void highlight();
	void sum();
};