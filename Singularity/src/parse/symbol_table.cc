#include <iostream>

#include "symbol_table.hh"

std::ostream& operator<<(std::ostream& out, Datatype value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(UNKNOWN)
        PROCESS_VAL(INTEGER)
        PROCESS_VAL(DOUBLE)
        PROCESS_VAL(STRING)
        PROCESS_VAL(BOOLEAN)
        PROCESS_VAL(FUNCTION)
       	PROCESS_VAL(LIST)
       	PROCESS_VAL(MATRIX)
    }

    return out << s;
}

void TableRow::print()
{
	std::cout << "\t" << id << " " << type << std::endl;
}

void Subtable::insertRow(const std::string& id, Datatype type)
{
	content[id] = new TableRow(id, type);
	// content.insert(std::make_pair<const std::string&,TableRow*>(id, new TableRow(id, type)));
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
	return children[name] = new Subtable(name, parent);
	//children.insert(std::make_pair<const std::string&, Subtable*>(name, new Subtable(name, parent))).first->second;
}

void Subtable::print()
{
	std::cout << name << ":" << std::endl;
	for(auto itr = content.begin(); itr != content.end(); ++itr)
	{
		itr->second->print();
	}

	for(auto itr = children.begin(); itr != children.end(); ++itr)
	{
		itr->second->print();
	}
}

void SymbolTable::initializeScope(const std::string& name)
{
	currentSubtable = currentSubtable->insertChild(name, currentSubtable);
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