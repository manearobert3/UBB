#include "gui.h"

GUI::GUI(QWidget* parent) : QWidget(parent)

{
	/*QVBoxLayout**/ mainLay = new QVBoxLayout();
	this->setWindowTitle("Veg tutorial");
	this->listOfAllVeg = new QListWidget();
	this->listOfSpecVeg = new QListWidget();
	this->searchByVegLine = new QLineEdit();
	this->searchByVegBut =new QPushButton("Search by vegetable");
	this->numberVeg = new QLabel("This is the number of veggies");
	this->calculateSum = new QLineEdit();
	this->CalculateButton = new QPushButton("Calculate Sum");
	mainLay->addWidget(this->listOfAllVeg);
	mainLay->addWidget(this->listOfSpecVeg);
	mainLay->addWidget(this->searchByVegLine);
	mainLay->addWidget(this->searchByVegBut);
	mainLay->addWidget(this->numberVeg);
	mainLay->addWidget(this->calculateSum);
	mainLay->addWidget(this->CalculateButton);
	this->setLayout(mainLay);
	this->populateList();
	QObject::connect(this->listOfAllVeg, &QListWidget::itemClicked, this, &GUI::searchByVeg);
	QObject::connect(this->searchByVegBut, &QPushButton::clicked, this, &GUI::highlight);
	QObject::connect(this->CalculateButton, &QPushButton::clicked, this, &GUI::sum);
}



void GUI::populateList()
{
	this->listOfAllVeg->clear();
	//for (auto veg : this->repo.sortFamily())
	QStringList listUnique;
	vector<Vegetable> asd;
		/*for (auto veg : this->repo.returnAll())
	{
		this->listOfAllVeg->addItem(QString::fromStdString(veg.getFamily()));

	};*/
		asd = this->repo.returnAll();
		for (int i = 0; i < this->repo.returnAll().size(); i++)
		{
			listUnique << QString::fromStdString(asd[i].getFamily());
		}

		listUnique.removeDuplicates();
		this->listOfAllVeg->clear();
		this->listOfAllVeg->addItems(listUnique);
		this->listOfAllVeg->sortItems();
}
 
void GUI::highlight()
{
	string vegetable = this->searchByVegLine->text().toStdString();
	this->listOfAllVeg->clear();
	for (auto veg : this->repo.sortFamily())
	{
		this->listOfAllVeg->addItem(QString::fromStdString(veg.getFamily()));
		if (veg.getFamily()==this->repo.getFamilyFromVeg(vegetable)) {
			QFont boldFont;
			boldFont.setBold(true);
			this->listOfAllVeg->item(this->listOfAllVeg->count() - 1)->setForeground(QColor(QString::fromStdString("red")));
			this->listOfAllVeg->item(this->listOfAllVeg->count() - 1)->setFont(boldFont);
			this->numberVeg->setText(QString::fromStdString("The things to eat from that=" + (this->repo.getEatable(vegetable))));
		}

	};
	
}

void GUI::sum()
{
	QLineEdit* response = new QLineEdit();
	string str = this->calculateSum->text().toStdString();
	int sum = this->repo.getVegFromFamily(str);
	string theSum = std::to_string(sum);
	response->setText(QString::fromStdString(theSum));
	mainLay->addWidget(response);
	this->setLayout(mainLay);
	mainLay->removeWidget(response);
	this->setLayout(mainLay);
}


void GUI::searchByVeg(QListWidgetItem* item) {
	string family = item->text().toStdString();
	this->listOfSpecVeg->clear();
	for (auto veg : this->repo.getVeg(family))
	{
		this->listOfSpecVeg->addItem(QString::fromStdString(veg.getName()));

	};
}
