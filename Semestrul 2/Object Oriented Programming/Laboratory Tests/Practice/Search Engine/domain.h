#pragma once
#include<string>
#include<vector>
using namespace std;

class Application {
private:
	string name;
	vector<string> keywords;
	string content;

public:
	Application(string& name, vector<string> keywords, string& content) : name{ name }, keywords{ keywords }, content{ content } {};
	Application() : name{ "" }, keywords{ "" }, content{ "" } {};
	~Application() {};
	void setName(string name) {
		this->name = name;
	}
	void setKey(vector<string> key) {
		this->keywords = key;
	}
	void setContent(string content){
		this->content = content;
}
	string toString() {
		string s = "";
		s = s + name +" | ";
		for (int i = 0; i < keywords.size()-1; i++) {
			s = s + keywords[i] + " , ";
		}
		s = s + keywords[keywords.size() - 1];
		return s;
	}
	string getName() {
		return name;
	}
	string getkeys() {
		string keyword;
		for (int i = 0; i < keywords.size()-1; i++) {
			keyword = keyword + keywords[i] + ", ";
		}
		keyword = keyword + keywords[keywords.size()-1];
		return keyword;
	}
};