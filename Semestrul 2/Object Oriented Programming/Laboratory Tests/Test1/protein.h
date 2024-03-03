#pragma once
#include<string>
#include<vector>
#include<iostream>
class Protein {

private:
	std::string organism, name, sequence;
public:
	Protein(const std::string& organism = "", const std::string& name = "", const std::string& sequence = "");
	Protein(const Protein& protein);
	~Protein();
	void setName(std::string& name);
	void setOrganism(std::string& organism);
	void setSequence(std::string& sequence);
	std::string getName() const;
	std::string getOrganism() const;
	std::string getSequence() const;
	Protein& operator=(const Protein& protein);
	bool operator==(const Protein& protein);

};