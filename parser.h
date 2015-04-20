//Chris Gerhardstein
//Parser class.  should get tokens and return expressions

#ifndef _parser
#define _parser


#include <fstream>
#include "stdafx.h"  // Required for visual studio to work correctly
#include <sstream>
#include "filemngr.h"
#include "GENERAL.H"
#include "scanner.h"
#include "pstack.h"
#include <vector>
#include <stack>

class parserClass
{
	public:
		parserClass();

		void printCurrentLine();
		void closeSourceProgram();
		int numLinesProcessed();
		int checkPresidence(int, int);

		void block();

		void varDecs();
		void type();
		void identList();
		void identifierTail();
		void identTail();

		void funcDecs();
		void funcDecTail();
		void typeTail();
		void paramList();


		void programBody();

		

		void statement();
		void followBegin();
		void statementTail();
		void followIf(string, string);
		void followId(string);
		void followExpression();
		void followCin();
		void followCout();
		void followInsert();
		void coutTail();

		void printInstruction(string, ItemCell *temp, string, ItemCell *temp2, string);

		void errorStatement(string, string);
		

		string getNextTemp();
		string getSpecialTemp();

		void parseProgram();
		void parse_expr();
		void expressionDebug(vector<tokenClass>);
		tokenClass topTerminal(vector<tokenClass>);
		tokenClass topStackTerminal(stack<tokenClass>);
		
		bool isTerminal(tokenClass);
		bool hasPoped(tokenClass);

		
		tokenClass topTerm;

		vector<tokenClass> symbolsPopped;
		//vector<ItemCell> symbolsPointer;

		pStackClass myStack;

		//stack<tokenClass>myStack;

		bool validRHS(vector<tokenClass>);


	private:
		scannerClass scanner;
		tokenClass token;
		tokenClass ident_token;
		tokenClass afterParser_token;
		fstream outfile;

		// variables are used for project 5
		int TEMP_TYPE;
		bool PARAM = false;
		bool AMPERSAND = false;
		
		int postExprType;
		int paramCount;
		string potentialFuncString;
		int numGlobals = 0;
		string digitValue;
		string mainFunctionJump;
		string funcName;
		int booleanTemp;
		int tempCount;
		tokenClass e_token;
		bool isParam;
		void paramsToStack(int numParams);
}; 

#endif