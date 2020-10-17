#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <functional>
#include <string>

enum Datatype
{
	UNKNOWN,
	INTEGER,
	DOUBLE,
	STRING,
	BOOLEAN
};

class TableRow
{
private:
	std::string id;
	Datatype type;
public:
	TableRow(const std::string& id, Datatype type)
		: id(id), type(type) {}
	inline void setType(Datatype type) { this->type = type; }
};

class Subtable
{
private:
	std::string name;
	std::hash<TableRow> subtable;
	Subtable* pointer;
};

class SymbolTable
{
private:
	Subtable* currentSubtable;
	std::hash<Subtable*> table;
public:
	SymbolTable() {}
};

#endif // SYMBOL_TABLE_H