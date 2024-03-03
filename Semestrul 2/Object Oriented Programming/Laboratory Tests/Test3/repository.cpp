#include "repository.h"
#include<sstream>
#include<fstream>
#include <string>
#include<algorithm>
void Repository::readFromFile()
{
	ifstream fin("apps.txt");
	if (!fin.is_open()) {
		throw exception();
	}
	string line;
	while (getline(fin, line)) {
		Application app;
		vector<string> vector;
		stringstream ss(line);
		char delimiter = '|';
		string word,word2;
		char delimiter2 = ',';
		getline(ss,word, delimiter);
		app.setName(word);
		getline(ss, word, delimiter);
		stringstream ss2(word);
		string word3;
		//getline(ss2, word2, delimiter2);
		while (getline(ss2, word, delimiter2)) {
			//string word3 = word2;
			vector.push_back(word);
		}
		app.setKeys(vector);
		getline(ss, word, delimiter);
		app.setContent(word);
		this->apps.push_back(app);
	}

}

vector<Application> Repository::returnAll()
{
	return this->apps;
}
