// Chris Gerhardstein
#ifndef _scanner
#define _scanner

#include "stdafx.h"  // Required for visual studio to work correctly

//#include "GENERAL.H"
//#include <string>
#include "FILEMNGR.H"
//#include <fstream>
//#include <stdlib.h>
#include <ctype.h>
#include "symbolTable.h"


class tokenClass
{
public:
	//token class will have data elements for hte token type (an int), subtype(an int) and a
	// string lexeme value
	//methods to print a token, etc
	//with a type (int), subtype(int) and lexeme(string)
	// see project description
	tokenClass();
	void display();
	int getType();
	int getSubType();
	string getLexeme();
	ItemCell * getItemCell();
	void setType(int);
	void setSubType(int);
	void setLexeme(string);
	void setToken(int, int, string);
	void setTokenPointer(ItemCell *temp);
	

	
private:
	int type;
	int subType;
	string lexeme;
	ItemCell *myTemp;
};

class scannerClass
{
public:
	scannerClass();
	void printCurrentLine();
	tokenClass getNextToken();
	int getNextState( int, int);
	tokenClass myToken;
	void setPrinterStatus(bool);

	void closeSourceProgram(); //The class will also need a method that can be
		//called to close the file when the driver program is about to terminate(this new member
		// function will simply call the appropriate member function from the fileManagerClass)
	
	 //these methods call the tableClass methods.
	 void tableAddLevel(string);
	 void tableDeleteLevel();
	 void deleteAllTemps();
	 bool tableAddEntry(string, int, int);
	 ItemCell * tableLookup(string);

	 int numFuncParams(string lex);
	
	int numLinesProcessed();
	int getCurrentNestingLevel();

	bool checkExpressionDebuggingStatus();
	bool expressionDebugging = false;

	void dumpTables();

	// methods to do with value params
	void deleteSpecialTemps();
	int paramCountTest(string lexeme);
	bool tableAddParam(string lex, int kind, int type);


private:
	fileManagerClass theFile;
	string theLexeme;
	bool finalState;
	symbolTableClass myTable;
};





#endif