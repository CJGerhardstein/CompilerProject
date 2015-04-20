//Chris Gerhardstein

#include "stdafx.h"  // Required for visual studio to work correctly

#include "filemngr.h"
#include "scanner.h"

#include "filemngr.cpp"
#include "string"


class tokenClass
{
public:
	//token class will have data elements for hte token type (an int), subtype(an int) and a
	// string lexeme value
	//methods to print a token, etc
	//with a type (int), subtype(int) and lexeme(string)
	// see project description
	tokenClass(int t, int s, string l);
	string display();
	int getType();
	int getSubType();
	string getLexeme();
	void setType(int);
	void setSubType(int);
	void setLexeme(string);
	void setToken(int, int, string);
private:
	int type;
	int subType;
	string lexeme;
};
