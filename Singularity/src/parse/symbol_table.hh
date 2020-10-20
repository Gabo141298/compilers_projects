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
	inline Datatype getType() { return this->type; }
	inline void setType(Datatype type) { this->type = type; }
	inline std::string getId() { return this->id; }
	void print();
};

class FunctionTableRow : public TableRow
{
private:
	size_t arguments;
	Datatype returnType = Datatype::UNKNOWN;
public:
	FunctionTableRow(const std::string& id, Datatype type, size_t arguments = 0)
		: TableRow(id, type)
		, arguments(arguments)
	{
	}
	inline size_t getArgumentCount() { return this->arguments; }
	inline Datatype getReturnType() { return this->returnType; }
	inline void setReturnType(Datatype type) { this->returnType = type; }
};

class ListTableRow : public TableRow
{
private:
	Datatype contentType = Datatype::UNKNOWN;
public:
	inline Datatype getContentType() { return this->contentType; }
	inline void setContentType(Datatype type) { this->contentType = type; }
};

class MatrixTableRow : public TableRow
{
private:
	Datatype contentType = Datatype::UNKNOWN;
	size_t row;
	size_t col;
public:
	MatrixTableRow(const std::string& id, Datatype type, size_t row = 0, size_t col = 0)
		: TableRow(id, type)
		, row(row)
		, col(col)
	{
	}
	inline Datatype getContentType() { return this->contentType; }
	inline void setContentType(Datatype type) { this->contentType = type; }
	inline size_t getRow() { return this->row; }
	inline void setRow(size_t row) { this->row = row; }
	inline size_t getCol() { return this->col; }
	inline void setCol(size_t col) { this->col = col; }
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
	TableRow* createRow(const std::string& id, Datatype type, size_t optional1 = 0, size_t optional2 = 0);
	TableRow* insertRow(const std::string& id, Datatype type = UNKNOWN, size_t optional1 = 0, size_t optional2 = 0);
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
	void insertToCurrentSubtable(const std::string& id, Datatype type = UNKNOWN, size_t optional1 = 0, size_t optional2 = 0);
	void print();
};

#endif // SYMBOL_TABLE_H