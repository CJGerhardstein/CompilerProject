// Chris Gerhardstein symbolTable.h


#ifndef _symbolTable
#define _symbolTable

#include <iostream>
#include <stdlib.h>    //to allow exit
#include "GENERAL.h"
#include <string>

using namespace std;
using std::ifstream;

class ParamItemCell
{
public:
	string lexemeValue;
	int kind;
	int type;
	int offset;
	ParamItemCell *next;
};


class ItemCell
{
public:
	string lexemeValue;
	int kind;
	int type;
	int offset;
	int nestingLevel;

	ParamItemCell *parameter;
	ItemCell *next;
};


class TableCell
{
public:
	string scopingLevel;
	int nestingLevel;
	int offset;

	TableCell *next;
	ItemCell *itemList;
private:	
};

// Kind constants
const int FUNCT_ID = 300;
const int VAR_ID = 301;
const int REF_PARAM = 302;
const int VALUE_PARAM = 303;

// Type constants
const int FUNC_ID_TYPE = 304;
const int INT_TYPE = 305;
const int BOOLEAN_TYPE = 306;

class symbolTableClass
{
public:

	symbolTableClass();

	void tableAddLevel(string);
	void tableDeleteLevel();
	bool tableAddEntry( string lexeme, int kind, int type);
	void deleteAllTemps();
	// methods to do with value params
	void deleteSpecialTemps();
	int paramCountTest(string lexeme);
	bool tableAddParam(string lex, int kind, int type);

	ItemCell * tableLookup(string);
	ItemCell * tableItemSearch(string lexeme, TableCell *level);

	int numFuncParams(string lex);
	int getCurrentNestingLevel();

	void dumpTable();

private:
	TableCell *top;

	int selfOrganize;
	
	
	
};


#endif
