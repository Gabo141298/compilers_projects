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

TableRow* Subtable::createRow(const std::string& id, Datatype type, size_t optional1, size_t optional2)
{
	switch(type)
	{
		case Datatype::INTEGER:
		case Datatype::DOUBLE:
		case Datatype::STRING:
		case Datatype::BOOLEAN:
		case Datatype::UNKNOWN:
		case Datatype::LIST:
			return new TableRow(id, type);
			break;
		case Datatype::FUNCTION:
			return new FunctionTableRow(id, type, optional1);
		case Datatype::MATRIX:
			return new MatrixTableRow(id, type, optional1, optional2);
		default:
			break;
	}
	return nullptr;
}

TableRow* Subtable::insertRow(const std::string& id, Datatype type, size_t optional1, size_t optional2)
{
	try
	{
		auto itr = content.find(id);
		if(itr != content.end())
			delete itr->second;
		return content[id] = createRow(id, type, optional1, optional2);
	}
	catch(const std::out_of_range&)
	{
		TableRow* row = parent->insertRow(id, type, optional1, optional2);
		if(row)
			return row;
		else
			return content[id] = createRow(id, type, optional1, optional2);
	}
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
			row = nullptr;
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

void SymbolTable::insertToCurrentSubtable(const std::string& id, Datatype type, size_t optional1, size_t optional2)
{
	currentSubtable->insertRow(id, type, optional1, optional2);
}

void SymbolTable::print()
{
	currentSubtable->print();
}