#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <functional>
#include <string>
#include <unordered_map>

#include <iostream>

enum Datatype
{
	UNKNOWN,
	INTEGER,
	DOUBLE,
	STRING,
	BOOLEAN,
	FUNCTION,
	LIST,
	MATRIX
};

#ifndef PROCESS_VAL
#define PROCESS_VAL(p) case(p): s = #p; break;
#endif
std::ostream& operator<<(std::ostream& out, Datatype value);

class TableRow
{
private:
	std::string id;
	Datatype type;
public:
	TableRow(const std::string& id, Datatype type)
		: id(id), type(type) {}
	inline void setType(Datatype type) { this->type = type; }
	void print();
};

class Subtable
{
private:
	std::string name;
	std::unordered_map<std::string, TableRow*> content;
	Subtable* parent;
	std::unordered_map<std::string, Subtable*> children;
public:
	Subtable(std::string name, Subtable* parent = nullptr)
		: name(name), parent(parent)
	{
	}
	void insertRow(const std::string& id, Datatype type = UNKNOWN);
	TableRow* search(const std::string& id);
	inline Subtable* getParent() { return parent; }
	Subtable* insertChild(const std::string& name, Subtable* parent);
	void print();
};

class SymbolTable
{
private:
	Subtable* currentSubtable;
public:
	SymbolTable()
		: currentSubtable(new Subtable("global"))
	{
	}
	void initializeScope(const std::string& name);
	void finalizeScope();
	void insertToCurrentSubtable(const std::string& id, Datatype type = UNKNOWN);
	void print();
};

#endif // SYMBOL_TABLE_H