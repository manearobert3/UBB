#include "UI.h"
#include<iostream>
void UI::start()
{
	string file;
	int option;
	while (true)
	{
		cout << "1.Add a new car + show its price\n2.Show all cars\n3.Save to File";
		cin >> option;
		if (option == 1) {
			add();
		}
		if (option == 2) {
			for (auto car : service.getAllCars()) {
				std::cout << car.toString()<<", price: "<<car.computePrice()<<"\n";

			}
		}
		if (option == 3) {
			file = "cars.txt";
			vector<Car> carsMax;
			cout << "input max price";
			int price;
			cin >> price;
			carsMax = service.getCarsWithMaxPrice(price);
			//service.writeToFile(file,this->service.getAllCars());
			service.writeToFile(file, carsMax);
		}
	}
}

void UI::add()
{
	string body;
	string engine;
	int autonomy;
	cout << "body?";
	cin >> body;
	cout << endl;
	cout << "engine";
	cin >> engine;
	if (engine == "Electric")
	{
		cout << "input atuonomy";
		cin >> autonomy;
		this->service.addCar(body, engine, autonomy);
	}
	else this->service.addCar(body, engine,0);
	
}

void UI::print()
{
	
}
