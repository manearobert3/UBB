#include"ui.h"
#include<vector>
#include<iostream>


UI::UI() {
	this->service = Service();
}
UI::~UI() {

}
void UI::printMenu() {
	std::cout << "1.Add protein" << std::endl;
	std::cout << "2.Remove protein" << std::endl;
	std::cout << "3.Print protein" << std::endl;
	std::cout << "4.exit" << std::endl;
}

void UI::printAdd() {
	std::string name, organism, sequence;
	std::cout << "name:" << std::endl;
	std::cin >> name;
	std::cout << "organism:" << std::endl;
	std::cin >> organism;
	std::cout << "sequence:" << std::endl;
	std::cin >> sequence;
	Protein protein = Protein(organism, name, sequence);
	if (this->service.addProtein(protein) == true) {
		std::cout << "protein added succesfuly";
	}
	else std::cout << "protein not added";
}


void UI::printRemove() {
	std::string name, organism, sequence;
	std::cout << "name:" << std::endl;
	std::cin >> name;
	std::cout << "organism:" << std::endl;
	std::cin >> organism;
	std::cout << "sequence:" << std::endl;
	std::cin >> sequence;
	Protein protein = Protein(organism, name, sequence);
	if (this->service.removeProtein(protein) == true) {
		std::cout << "protein rmeoved succesfuly";
	}
	else std::cout << "protein not added";
}

void UI::run() {
	while (true) {
		this->printMenu();
		int choice;
		std::cout << "Input your choice:";
		std::cin >> choice;
		if (choice == 1)
		{
			this->printAdd();
		}
		else if (choice == 2) {
			this->printRemove();
		}
		else if (choice == 3) {
			this->printProtein();
		}
		else if (choice == 4) {
			exit;
		}
	}
}

void UI::printProtein()
{
	std::vector<Protein> proteins = this->service.getProtein();
	std::vector<Protein>::iterator index;
	for (index = proteins.begin(); index < proteins.end(); index++) {
		Protein currentPro = *index;
		std::cout << currentPro.getOrganism() << ", " << currentPro.getName() << ", " << currentPro.getSequence() << ";";
	}
}

