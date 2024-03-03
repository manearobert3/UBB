#include "repository.h"
#include<fstream>
#include<sstream>
using namespace std;
void Repository::readFromFile()
{
	string filename = "apps.txt";
	ifstream fin(filename);
	if (!fin.is_open())
		throw exception();
	Application app;
	string line;
	while (getline(fin, line)) {
		stringstream ss(line);
		string word;
		string everyWord;
		vector<string> keywords;
		char delimiter = '|';
		getline(ss, word, delimiter);
		app.setName(word);
		getline(ss, word, delimiter);
		char delimiter2 = ',';
		stringstream ss2(word);
		while (getline(ss2, word, delimiter2)) {
			everyWord = word;
			keywords.push_back(word);
		}
		app.setKey(keywords);
		getline(ss, word, delimiter);
		app.setContent(word);
		apps.push_back(app);
	}
	fin.close();
}

vector<Application> Repository::returnAll()
{
	return this->apps;
}
