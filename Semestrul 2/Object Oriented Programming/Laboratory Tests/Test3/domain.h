#pragma once
#include<string>
#include<vector>
using namespace std;
class Application {
private:
	string name, content;
	vector<string> keywords;
public:
	Application(string name, vector<string> keywords, string content) : name{ name }, keywords{ keywords }, content{ content } {};
	Application() : name{ "" }, keywords{ "" }, content{ "" } {};
	~Application() {};
	string getName() {
		return name;
	}
	string getContent() {
		return content;
	}
	string getKeys() {
		string s;
		for (int i = 0; i < keywords.size()-1; i++) {
			s = s + keywords[i] + ", ";
		}
		s = s + keywords[keywords.size() - 1];
		return s;
	}
	void setName(string name) {
		this->name = name;
	}
	void setContent(string content) {
		this->content = content;
	}
	void setKeys(vector<string> keys) {
		this->keywords = keys;
	}
	string toString() {
		string s = "";
		s = s + this->name + " | ";
		for (int i = 0; i < keywords.size() - 1; i++) {
			s = s + keywords[i] + " , ";
		}
		s = s + keywords[keywords.size() - 1];
		return s;
	}
};