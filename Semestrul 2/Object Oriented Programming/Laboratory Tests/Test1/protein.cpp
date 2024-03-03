#include"protein.h"
#include<string>

Protein::Protein(const std::string& organism, const std::string& name, const std::string& sequence) : organism{ organism }, name{ name }, sequence{ sequence } {};
Protein::~Protein() {}
void Protein::setName(std::string& name)
{
	this->name = name;
}
void Protein::setSequence(std::string& sequence)
{
	this->sequence = sequence;
}
std::string Protein::getName() const
{
	return this->name;
}
void Protein::setOrganism(std::string& organism)
{
	this->organism = organism;
}

std::string Protein::getOrganism() const
{
	return this->organism;
}

std::string Protein::getSequence() const
{
	return this->sequence;
}

Protein::Protein(const Protein& protein) {
	this->name = protein.name;
	this->organism = protein.organism;
	this->sequence = protein.sequence;
}
Protein& Protein::operator=(const Protein& protein)
{
	this->organism = protein.organism;
	this->name = protein.name;
	this->sequence = protein.sequence;
	return *this;
		
}
bool Protein::operator==(const Protein& protein)
{
	return protein.name == this->name && this->sequence==protein.sequence && this->organism==protein.organism;
}