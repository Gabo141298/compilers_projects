#include <iostream>

#include "symbol_table.hh"

void TableRow::print()
{
	std::cout << "\t" << id << " " << type << std::endl;
}

void Subtable::insertRow(const std::string& id, Datatype type)
{
	content.insert(std::make_pair<const std::string&,TableRow*>(id, new TableRow(id, type)));
}

TableRow* Subtable::search(const std::string& id)
{
	TableRow* row = nullptr;
	try
	{
		row = content.at(id);
	}
	catch(const std::out_of_range&)
	{
		if(parent)
			row = parent->search(id);
		else
			return nullptr;
	}
	return row;
}

Subtable* Subtable::insertChild(const std::string& name, Subtable* parent)
{
	return children.insert(std::make_pair<const std::string&, Subtable*>(name, new Subtable(name, parent))).first->second;
}

void Subtable::print()
{
	std::cout << name << ":" << std::endl;
	for(auto itr = content.begin(); itr != content.end(); ++itr)
	{
		itr->second->print();
	}
}

void SymbolTable::initializeScope(const std::string& name)
{
	Subtable* newSubtable = new Subtable(name, this->currentSubtable);
	currentSubtable->insertChild(name, newSubtable);
	currentSubtable = newSubtable;
}

void SymbolTable::finalizeScope()
{
	if(currentSubtable)
		currentSubtable = currentSubtable->getParent();
}

void SymbolTable::insertToCurrentSubtable(const std::string& id, Datatype type)
{
	currentSubtable->insertRow(id, type);
}

void SymbolTable::print()
{
	currentSubtable->print();
}