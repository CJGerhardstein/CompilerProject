// Chris Gerhardstein

#include "stdafx.h"  // Required for visual studio to work correctly

#include "filemngr.h"
#include "scanner.h"
#include "parser.h"
#include "pstack.h"

#include <ctype.h>
#include "string"

// empty constructor
parserClass::parserClass()
{
	outfile.open("out.pal", ios::out);
}
// prints the current line
void parserClass::printCurrentLine()
{
	scanner.printCurrentLine();
}

// closes program
void parserClass::closeSourceProgram()
{
	scanner.closeSourceProgram();
}

// prints the number of lines processed
int parserClass::numLinesProcessed()
{
	return scanner.numLinesProcessed();
}

// returns the presidence (GT, LT, EQ, or ER)
int parserClass::checkPresidence(int row, int col)
{
	//ROWS AND COLUMNS
	/*0=relop     1 = addop     2 = mulop
	3 = (           4 = )       5 = identifyer
	6 = integer     7 = true    8 = false
	9 = semicolon   10 = other*/

	static int table[11][11]{
			{ GT, LT, LT, LT, GT, LT, LT, LT, LT, GT, ER},
			{ GT, GT, LT, LT, GT, LT, LT, LT, LT, GT, ER },
			{ GT, GT, GT, LT, GT, LT, LT, LT, LT, GT, ER },
			{ LT, LT, LT, LT, EQ, LT, LT, LT, LT, ER, ER },
			{ GT, GT, GT, ER, GT, ER, ER, ER, ER, GT, ER },
			{ GT, GT, GT, ER, GT, ER, ER, ER, ER, GT, ER },
			{ GT, GT, GT, ER, GT, ER, ER, ER, ER, GT, ER },
			{ GT, GT, GT, ER, GT, ER, ER, ER, ER, GT, ER },
			{ GT, GT, GT, ER, GT, ER, ER, ER, ER, GT, ER },
			{ LT, LT, LT, LT, ER, LT, LT, LT, LT, ER, ER },
			{ ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER }
	};

	/*	||  (token.getType() == THEN_T)
			|| (token.getType() == COMMA_T)
			|| (token.getType() == END_T)
			|| (token.getType() == ELSE_T)
			|| (token.getType() == INSERT_T)*/
	if (col == DO_T)
	{
		col = SEMICOLON_T;
	}
	if (row == DO_T)
	{
		row = SEMICOLON_T;
	}

	if (col == THEN_T)
	{
		col = SEMICOLON_T;
	}
	if (row == THEN_T)
	{
		row = SEMICOLON_T;
	}

	if (col == COMMA_T)
	{
		col = SEMICOLON_T;
	}
	if (row == COMMA_T)
	{
		row = SEMICOLON_T;
	}

	if (col == END_T)
	{
		col = SEMICOLON_T;
	}
	if (row == END_T)
	{
		row = SEMICOLON_T;
	}

	if (col == ELSE_T)
	{
		col = SEMICOLON_T;
	}
	if (row == ELSE_T)
	{
		row = SEMICOLON_T;
	}

	if (col == INSERT_T)
	{
		col = SEMICOLON_T;
	}
	if (row == INSERT_T)
	{
		row = SEMICOLON_T;
	}
	// all but close paren go to semicolon

	return table[row][col];
}


// returns whether or not the token passed is terminal
bool parserClass::isTerminal(tokenClass checkToken)
{
	if (checkToken.getType() != E_T )
	{
		return true;
	}
	else
		return false;
}


// prints what if E goes to I, relop, mulop, paren, addop
void parserClass::expressionDebug(vector<tokenClass> checkVector)
{
	//does E -> i
	if (checkVector.size() == 1)
	{
		if (checkVector.at(0).getType() == TRUE_T)
		{
			cout << "E -> TRUE" << endl;
		}
		else if (checkVector.at(0).getType() == FALSE_T)
		{
			cout << "E -> FALSE" << endl;
		}
		else if (checkVector.at(0).getType() == DIGIT_T)
		{
			cout << "E -> DIGIT" << endl;
		}
		else if (checkVector.at(0).getType() == IDENT_T)
		{
			cout << "E -> IDENT" << endl;
		}
	}

	// if the vector is of size 3 checks for relop, mulop, paren, addop
	else if (checkVector.size() == 3)
	{
		if (checkVector.at(checkVector.size() - 1).getType() == E_T &&
			checkVector.at(checkVector.size() - 2).getType() == RELOP_T &&
			checkVector.at(checkVector.size() - 3).getType() == E_T)
		{
			if (checkVector.at(checkVector.size() - 2).getSubType() == ISEQUAL_ST)
			{
				cout << "E -> E == E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == LESSEQ_ST)
			{
				cout << "E -> E <= E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == GREATEREQ_ST)
			{
				cout << "E -> E >= E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == LESS_ST)
			{
				cout << "E -> E < E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == GREATER_ST)
			{
				cout << "E -> E > E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == NOTEQ_ST)
			{
				cout << "E -> E <> E" << endl;
			}
			else
			{
				cout << "Error: expected a relop." << endl;
			}
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == E_T &&
			checkVector.at(checkVector.size() - 2).getType() == ADDOP_T &&
			checkVector.at(checkVector.size() - 3).getType() == E_T)
		{
			if (checkVector.at(checkVector.size() - 2).getSubType() == PLUS_ST)
			{
				cout << "E -> E + E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == MINUS_ST)
			{
				cout << "E -> E - E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == OR_ST)
			{
				cout << "E -> E or E" << endl;
			}
			else
			{
				cout << "Error: expected an addop: + || - || 'or'" << endl;
			}
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == E_T &&
			checkVector.at(checkVector.size() - 2).getType() == MULOP_T &&
			checkVector.at(checkVector.size() - 3).getType() == E_T)
		{
			if (checkVector.at(checkVector.size() - 2).getSubType() == TIMES_ST)
			{
				cout << "E -> E * E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == DIV_ST)
			{
				cout << "E -> E div E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == MOD_ST)
			{
				cout << "E -> E mod E" << endl;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == AND_ST)
			{
				cout << "E -> E and E" << endl;
			}
			else
			{
				cout << "Error. Expected a mulop; * || div || mod || and" << endl;
			}
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == OPENP_T &&
			checkVector.at(checkVector.size() - 2).getType() == E_T &&
			checkVector.at(checkVector.size() - 3).getType() == CLOSEP_T)
		{
			cout << "E -> (E)" << endl;
		}
	}
}

// returns true if the symbols poped are a valid RHS
bool parserClass::validRHS(vector<tokenClass> checkVector)
{
	if (checkVector.size() == 1)
	{
		if (checkVector.at(checkVector.size()-1).getType() == TRUE_T)
		{
			// string that becomes a unique ItemCell's lexeme value
			std::string numG = "$" + std::to_string(numGlobals);

			// adds a unique
			scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

			e_token.setTokenPointer(scanner.tableLookup(numG));

			ItemCell *newEntry = scanner.tableLookup(numG);

			outfile << endl << ": found true" << endl;
			printInstruction("movw", NULL, "#1", newEntry, "");
			printInstruction("addw", NULL, "#4", NULL, "sp");

			numGlobals++;

			return true;
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == FALSE_T)
		{
			// string that becomes a unique ItemCell's lexeme value
			std::string numG = "$" + std::to_string(numGlobals);

			// adds a unique
			scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

			e_token.setTokenPointer(scanner.tableLookup(numG));

			ItemCell *newEntry = scanner.tableLookup(numG);

			printInstruction("movw", NULL, "#0", newEntry, "");
			printInstruction("addw", NULL, "#4", NULL, "sp");
			outfile << endl << ": found false" << endl;


			numGlobals++;

			return true;
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == DIGIT_T)
		{
			// string that becomes a unique ItemCell's lexeme value
			std::string numG = "$" + std::to_string(numGlobals);

			// adds a unique
			scanner.tableAddEntry(numG, VAR_ID, INT_TYPE);

			e_token.setTokenPointer(scanner.tableLookup(numG));
			
			ItemCell *newEntry = scanner.tableLookup(numG);

			printInstruction("movw", NULL, "#" + digitValue, newEntry, "");
			printInstruction("addw", NULL, "#4", NULL, "sp");
			outfile << endl << ": found digit" << endl;
			
			numGlobals++;
			return true;
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == IDENT_T)
		{
			return true;
		}
		cout << "Error in expression." << endl;;
		printCurrentLine();
		cin.get();
		exit(1);
	}

	// if the size is 3 it must be a relop, addop, mulop, or paren.
	else if (checkVector.size() == 3)
	{
		//cout << "size is 3" << endl;
		if (checkVector.at(checkVector.size() - 1).getType() == E_T &&
			checkVector.at(checkVector.size() - 2).getType() == RELOP_T &&
			checkVector.at(checkVector.size() - 3).getType() == E_T)
		{
			if (checkVector.at(checkVector.size() - 2).getSubType() == GREATER_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				if (st->type != INT_TYPE || second->type != INT_TYPE)
				{
					cout << "Error: Must have two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				outfile << endl << ": starting greater relop" << endl;

				printInstruction("cmpw", st, "", second, "");
				outfile << "bleq " << str1 << " " << endl;

				printInstruction("movw", NULL, "#1", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << "jmp " << str3 << endl;

				outfile << str1 << " ";

				printInstruction("movw", NULL, "#0", newEntry, "");
				//printInstruction("addw", NULL, "#4", NULL, "sp");

				outfile << endl << ": finished greater relop" << endl;
				outfile << str3 << " ";

			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == GREATEREQ_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				if (st->type != INT_TYPE || second->type != INT_TYPE)
				{
					cout << "Error: Must have two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				outfile << endl << ": starting greater or eq relop" << endl;

				printInstruction("cmpw", st, "", second, "");
				outfile << "blss " << str1 << " " << endl;

				printInstruction("movw", NULL, "#1", newEntry, "");
				//printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << "jmp " << str3 << endl;

				outfile << str1 << " ";

				printInstruction("movw", NULL, "#0", newEntry, "");
				outfile << endl << ": finished greater or eq relop" << endl;
				outfile << str3 << " ";
				

			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == LESSEQ_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != INT_TYPE || second->type != INT_TYPE)
				{
					cout << "Error: Must have two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				outfile << endl << ": starting less or eq relop" << endl;

				printInstruction("cmpw", st, "", second, "");
				outfile << "bgtr " << str1 << " " << endl;

				printInstruction("movw", NULL, "#1", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << "jmp " << str3 << endl;

				outfile << str1 << " ";

				printInstruction("movw", NULL, "#0", newEntry, "");
				//printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << endl << ": finished less or eq relop" << endl;
				outfile << str3 << " ";
				

			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == LESS_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != INT_TYPE || second->type != INT_TYPE)
				{
					cout << "Error: Must have two int types for < operation." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				outfile << endl << ": starting less relop" << endl;
				printInstruction("cmpw", st, "", second, "");
				outfile << "bgeq " << str1 << " " << endl;

				printInstruction("movw", NULL, "#1", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << "jmp " << str3 << endl;

				outfile << str1 << " ";

				printInstruction("movw", NULL, "#0", newEntry, "");
				//printInstruction("addw", NULL, "#4", NULL, "sp");

				outfile << endl << ": finished less relop" << endl;
				outfile << str3 << " ";
			}


			else if (checkVector.at(checkVector.size() - 2).getSubType() == ISEQUAL_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving pearse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();


				if ((st->type == BOOLEAN_TYPE && second->type == BOOLEAN_TYPE) || 
					(st->type == INT_TYPE && second->type == INT_TYPE))
				{
					string str1 = getNextTemp();
					string str2 = getNextTemp();
					string str3 = getNextTemp();

					outfile << endl << ": starting isEqual relop" << endl;

					printInstruction("cmpw", st, "", second, "");
					outfile << "bneq " << str1 << " " << endl;

					printInstruction("movw", NULL, "#1", newEntry, "");
					printInstruction("addw", NULL, "#4", NULL, "sp");
					outfile << "jmp " << str3 << endl;

					outfile << str1 << " ";

					printInstruction("movw", NULL, "#0", newEntry, "");
					//printInstruction("addw", NULL, "#4", NULL, "sp");

					outfile << endl << ": finished less relop" << endl;
					outfile << str3 << " ";
				}
				else
				{
					cout << "Error: Must have two boolean or int types when doing an == comparison." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == NOTEQ_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if ((st->type == BOOLEAN_TYPE && second->type == INT_TYPE) || (st->type == INT_TYPE && second->type == BOOLEAN_TYPE))
				{
					cout << "Error: Must add two int types or two boolean types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				outfile << endl << ": starting isEqual relop" << endl;

				printInstruction("cmpw", st, "", second, "");
				outfile << "bneq " << str1 << " " << endl;

				printInstruction("movw", NULL, "#0", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << "jmp " << str3 << endl;

				outfile << str1 << " ";

				printInstruction("movw", NULL, "#1", newEntry, "");
				//printInstruction("addw", NULL, "#4", NULL, "sp");

				outfile << endl << ": finished less relop" << endl;
				outfile << str3 << " ";
			}

			return true;
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == E_T &&
			checkVector.at(checkVector.size() - 2).getType() == ADDOP_T &&
			checkVector.at(checkVector.size() - 3).getType() == E_T)
		{

			if (checkVector.at(checkVector.size() - 2).getSubType() == PLUS_ST)
			{
				std::string numG = "$" + std::to_string(numGlobals);

				scanner.tableAddEntry(numG, VAR_ID, INT_TYPE);

				ItemCell *newEntry = scanner.tableLookup(numG);


				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();



				if (st->type == INT_TYPE && second->type == INT_TYPE)
				{
					outfile << endl << ": starting plus operation" << endl;

					printInstruction("movw", st, "", newEntry, "");

					printInstruction("addw", second, "", newEntry, "");


					printInstruction("addw", NULL, "#4", NULL, "sp");
					outfile << endl << ": finished plus operation" << endl;
					numGlobals++;
				}
				else
				{
					cout << "Error: Must add two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				
				
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == MINUS_ST)
			{
				std::string numG = "$" + std::to_string(numGlobals);

				scanner.tableAddEntry(numG, VAR_ID, INT_TYPE);

				ItemCell *newEntry = scanner.tableLookup(numG);

				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != INT_TYPE || second->type != INT_TYPE)
				{
					cout << "Error: Must add two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				outfile << endl << ": starting minus operation" << endl;
				printInstruction("movw", st, "", newEntry, "");

				printInstruction("subw", second, "", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << endl << ": finished minus operation" << endl;
				numGlobals++;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == OR_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != BOOLEAN_TYPE || second->type != BOOLEAN_TYPE)
				{
					cout << "Error: Must have two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				outfile << endl << ":Starting OR" << endl;

				printInstruction("movw", st, "", NULL, "@r5");
				printInstruction("addw", second, "", NULL, "@r5");
				printInstruction("cmpw", NULL, "@r5", NULL, "#0");
				// if the words are notequal jump to later
				outfile << "bneq " << str1 << endl;
				// we know they are the same.
				printInstruction("movw", NULL, "#0", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");

				outfile << "jmp " << str3 << endl;
				// handles not equal. assigns value to be 0
				outfile << str1 << " ";
				printInstruction("movw", NULL, "#1", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");



				outfile << str3 << " ";
				//TODO make sure this works. added 1 lines below to move and value and reduce stack once and op was finished.
				printInstruction("movw", newEntry, "", NULL, "@r1");

				outfile << endl << "  :Finished OR" << endl;
				numGlobals++;
			}
			

			return true;
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == E_T &&
			checkVector.at(checkVector.size() - 2).getType() == MULOP_T &&
			checkVector.at(checkVector.size() - 3).getType() == E_T)
		{
			if (checkVector.at(checkVector.size() - 2).getSubType() == TIMES_ST)
			{
				outfile << ": starting TIMES" << endl;
				std::string numG = "$" + std::to_string(numGlobals);

				// should this be var_id or value_param?
				scanner.tableAddEntry(numG, VAR_ID, INT_TYPE);

				ItemCell *newEntry = scanner.tableLookup(numG);


				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();


				if (st->type != INT_TYPE && second->type != INT_TYPE)
				{
					cout << "Error: Must add two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				printInstruction("movw", st, "", newEntry, "");

				printInstruction("mulw", second, "", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << ": finishing TIMES" << endl;
				numGlobals++;
			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == MOD_ST)
			{
				std::string numG = "$" + std::to_string(numGlobals);

				// should this be var_id or value_param?
				scanner.tableAddEntry(numG, VAR_ID, INT_TYPE);

				ItemCell *newEntry = scanner.tableLookup(numG);


				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != INT_TYPE && second->type != INT_TYPE)
				{
					cout << "Error: Must add two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				outfile << ": starting MOD" << endl;


				printInstruction("movw", st, "", NULL, "r5");
				printInstruction("divw", second, "", NULL, "r5");
				
				printInstruction("movw", NULL, "r5", NULL, "r6");
				printInstruction("mulw", second, "", NULL, "r6");
				printInstruction("movw", st, "", NULL, "r7");
				printInstruction("subw", NULL, "r6", NULL, "r7");
				printInstruction("movw", NULL, "r7", newEntry, ""); // added
				//printInstruction("movw", NULL, "r7", NULL, "@r1");

				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << ": returning from MOD" << endl;

			}
			else if (checkVector.at(checkVector.size() - 2).getSubType() == DIV_ST)
			{
				std::string numG = "$" + std::to_string(numGlobals);

				// should this be var_id or value_param?
				scanner.tableAddEntry(numG, VAR_ID, INT_TYPE);

				ItemCell *newEntry = scanner.tableLookup(numG);

				//scanner.dumpTables();

				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != INT_TYPE && second->type != INT_TYPE)
				{
					cout << "Error: Must add two int types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				outfile << endl << ": starting MOD" << endl;
				printInstruction("movw", st, "", newEntry, "");

				printInstruction("divw", second, "", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				outfile << endl << ": finished MOD" << endl;
				numGlobals++;
			}

			else if (checkVector.at(checkVector.size() - 2).getSubType() == AND_ST)
			{
				// string used for new global variable
				std::string numG = "$" + std::to_string(numGlobals);

				// adds a boolean type. used for its offset later
				scanner.tableAddEntry(numG, VAR_ID, BOOLEAN_TYPE);

				// used to print stuff based on the offset of the new Entry
				ItemCell *newEntry = scanner.tableLookup(numG);

				// assigns a token pointer so when leaving parse_expr it won't give break error
				e_token.setTokenPointer(scanner.tableLookup(numG));

				ItemCell *st = checkVector.at(checkVector.size() - 1).getItemCell();
				ItemCell *second = checkVector.at(checkVector.size() - 3).getItemCell();

				if (st->type != BOOLEAN_TYPE || second->type != BOOLEAN_TYPE)
				{
					cout << "Error: Must compare two boolean types." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}

				string str1 = getNextTemp();
				string str2 = getNextTemp();
				string str3 = getNextTemp();

				outfile << endl << ":Starting AND" << endl;

				printInstruction("movw", st, "", NULL, "@r5");
				printInstruction("mulw", second, "", NULL, "@r5");
				printInstruction("cmpw", NULL, "@r5", NULL, "#0");
				// if the words are notequal jump to later
				outfile << "bneq " << str1 << endl;
				// we know they are the same.
				printInstruction("movw", NULL, "#0", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");
				
				outfile << "jmp " << str3 << endl;
				// handles not equal. assigns value to be 0
				outfile << str1 << " ";
				printInstruction("movw", NULL, "#1", newEntry, "");
				printInstruction("addw", NULL, "#4", NULL, "sp");

				

				outfile << str3 << " ";
				//TODO make sure this works. added 1 lines below to move and value and reduce stack once and op was finished.
				printInstruction("movw", newEntry, "", NULL, "@r1");
				
				outfile << endl << "  :Finished AND" << endl;
				numGlobals++;
			}
			return true;
		}
		else if (checkVector.at(checkVector.size() - 1).getType() == OPENP_T &&
			checkVector.at(checkVector.size() - 2).getType() == E_T &&
			checkVector.at(checkVector.size() - 3).getType() == CLOSEP_T)
		{
			// this is hte E_T. normally use the other ones.
			ItemCell *st = checkVector.at(checkVector.size() - 2).getItemCell();
			
			
			std::string numG = "$" + std::to_string(numGlobals);


			// should this be var_id or value_param?
			// changed to st-> kind instaed of INT_TYPE

			// scanner.tableAddEntry(numg, VAR_KIND, INT_TYPE);

			scanner.tableAddEntry(numG, st->kind, st->type);

			ItemCell *newEntry = scanner.tableLookup(numG);

			e_token.setTokenPointer(scanner.tableLookup(numG));

			
			printInstruction("movw", st, "", newEntry, "");
			printInstruction("addw", NULL, "#4", NULL, "sp");

			numGlobals++;
			

			return true;
		}
		cout << "Error in expression." << endl;;
		printCurrentLine();
		cin.get();
		exit(1);

	}
}

void parserClass::parse_expr()
{
	
	// marks the current top of hte stack with R1
	outfile << "movw SP R1" << endl;
	//outfile << "addw #4 SP" << endl;
	// temp is a pointer to the identifier in the symbol table
	ItemCell *temp;
	if (token.getType() == IDENT_T)
	{
		temp = scanner.tableLookup(token.getLexeme());
		if (temp == NULL)
		{
			cout << "Undeclared identifier: " << token.getLexeme() << endl;
			scanner.printCurrentLine();
			cin.get();
			exit(1);
		}
		token.setTokenPointer(temp);
		// KNOW TOKEN HAS ITEMCELL POINTER
	}
	
	
	// will be made true if a terminal is poped.
	bool terminalPoped = false;

	// pushes a semicolon onto the stack 
	tokenClass semiColonToken;
	semiColonToken.setToken(SEMICOLON_T, NONE_ST, ";");
	myStack.push(semiColonToken);
	topTerm = semiColonToken;
	
	if (token.getType() != TRUE_T &&
		token.getType() != FALSE_T &&
		token.getType() != DIGIT_T &&
		token.getType() != IDENT_T &&
		token.getType() != OPENP_T)
	{
		cout << "token type: " << token.getType()  << " " << token.getLexeme()<< endl;
		cout << "Error: invalid start of expression." << endl;
		printCurrentLine();
		cin.get();
		exit(1);
	}
	

	while (1)
	{
		if (token.getType() == DIGIT_T)
		{
			digitValue = token.getLexeme();
		}
		if (token.getType() == IDENT_T)
		{
			// if statement checks to see if the identifyer has been declared.
			temp = scanner.tableLookup(token.getLexeme());
			if (temp == NULL)
			{
				cout << "Undeclared identifier: " << token.getLexeme() << endl;
				scanner.printCurrentLine();
				cin.get();
				exit(1);
			}
			token.setTokenPointer(temp);
			// KNOW TEMP ITEMCELL HAS VALUE HERE
		}
		
		
		// if top of stack and the token are a semicolon then we have found a valid expression and return
		if ((myStack.topTerminalOnStack().getType() == SEMICOLON_T) && 
			((token.getType() == SEMICOLON_T)
			||  (token.getType() == DO_T)
			||  (token.getType() == THEN_T)
			|| (token.getType() == COMMA_T)
			|| (token.getType() == END_T)
			|| (token.getType() == CLOSEP_T)
			|| (token.getType() == ELSE_T)
			|| (token.getType() == INSERT_T)
			))
		{
			// Leave expression parser.
			
			tokenClass answerToken = myStack.topOfStack();
			ItemCell *answerItem = answerToken.getItemCell();

			postExprType = answerItem->type;
			
			// moves the answer to @r1
			printInstruction("movw", answerItem, "", NULL, "@r1");
			
			// moves the stack pointer to just above the memory location with the answer (spot in previous line).
			outfile << "movw r1 sp" << endl;
			outfile << "addw #4 sp" << endl;
			afterParser_token = answerToken;

			scanner.deleteAllTemps();
			// part5
			scanner.tableAddEntry(getSpecialTemp(), answerItem->kind, answerItem->type);

			return;
		}

		//SHIFT function is below.
		topTerm = myStack.topTerminalOnStack();
		if (checkPresidence(topTerm.getType(), token.getType()) == LT ||
			checkPresidence(topTerm.getType(), token.getType()) == EQ)
		{
			// KNOW ITEMCELL IS ON STACK
			myStack.push(token);

		
			token = scanner.getNextToken();
		}

		//REDUCE function is below.
		else if (checkPresidence(topTerm.getType(), token.getType()) == GT)
		{
			terminalPoped = false;
			tokenClass lastTerminalPoped;
			do
			{
				// should push back top token AND move pointer.
				symbolsPopped.push_back(myStack.pop());
				
				//KNOW SYMBOL TABLE HAS ITEMCELL POINTER

				//if the thing popped was a terminal make terminal poped true and
				// last terminal poped true
				if (isTerminal(symbolsPopped.at(symbolsPopped.size()-1)))
				{
					terminalPoped = true;
					lastTerminalPoped = symbolsPopped.at(symbolsPopped.size()-1);
				}
				topTerm = myStack.topTerminalOnStack();

			} while (terminalPoped == false ||
				myStack.isTerminalOnTopOfStack() == false ||
				checkPresidence(topTerm.getType(),lastTerminalPoped.getType()) != LT);



			// if we have a valid RHS then returns E token and debugging if it is true.
			if (validRHS(symbolsPopped) == true)
			{
				// calls expressionDebug() which prints the expression.
				if (scanner.checkExpressionDebuggingStatus() == true)
				{
					expressionDebug(symbolsPopped);
				}

				
				if (symbolsPopped.at(symbolsPopped.size()-1).getType() == IDENT_T)
				{
					
					// the E_token should be assigned a pointer value as well 
					
					if (e_token.getItemCell() == NULL)
					{
						e_token.setTokenPointer(temp);
					}
					
					myStack.push(e_token);
					symbolsPopped.clear();
					e_token.setTokenPointer(NULL);
				}
				else
				{
					// the token should not be assigned a pointer value
					//e_token.setToken(E_T, NONE_ST, "E");
					
					myStack.push(e_token);
					symbolsPopped.clear();
					e_token.setTokenPointer(NULL);
				}
					
			}
			// Not a valid Right hand side expression.
			else
			{
				cout << "Not a valid RHS expression." << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}

		}
		else
		{
			//cout << "Token type: " << token.getType() << endl;
			cout << "Syntax Error: Invalid statement." << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}
		
	}
}


// Before statement.

void parserClass::block()
{
	
	varDecs();

	if (scanner.getCurrentNestingLevel() == 0)
	{
		mainFunctionJump = getNextTemp();
		// moves the stack pointer the appropriate amount based on number of variables declared
		outfile << "addw #" << numGlobals * 4 << " SP" << endl;

		//jump to the start of the main program function
		printInstruction("jmp", NULL, mainFunctionJump, NULL, "");
	}
	else
	{
		outfile << "addw #" << tempCount * 4 << " SP" << endl;
	}
	

	funcDecs();
	
	programBody();

	if (scanner.getCurrentNestingLevel() != 0)
	{
		outfile << "movw FP SP" << endl;
		outfile << "RET" << endl;
	}

	scanner.tableDeleteLevel();
}
// START OF BLOCK METHODS

void parserClass::varDecs()
{
	
	if (token.getType() == INT_T || token.getType() == BOOLEAN_T)
	{
		tempCount = 0;
		type();
		identList();
		if (token.getType() == SEMICOLON_T)
		{
			token = scanner.getNextToken();
			varDecs();
		}
		else
		{
			errorStatement("semicolon", token.getLexeme());
		}
	}
	else
		return;
}

void parserClass::type()
{
	
	//  reads one declaration of integers.
	if (token.getType() == INT_T)
	{
		TEMP_TYPE = INT_TYPE;
		token = scanner.getNextToken();
		return;
	}
	//  reads one declaration of booleans.
	else if (token.getType() == BOOLEAN_T)
	{
		TEMP_TYPE = BOOLEAN_TYPE;
		token = scanner.getNextToken();
		return;
	}

	// either no ints and booleans are declared or there are no more
	else
		errorStatement("INT or BOOLEAN", token.getLexeme());
}

void parserClass::identList()
{
	if (token.getType() == IDENT_T)
	{
		
		// if the identifier is NOT a parameter tableAddEntry normally.
		if (PARAM == false)
		{
			if (TEMP_TYPE == BOOLEAN_TYPE)
			{
				if (!scanner.tableAddEntry(token.getLexeme(), VAR_ID, BOOLEAN_TYPE))
				{
					cout << "Duplicate identifier " << token.getLexeme() << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				else
				{

					// addentry was successful, globalvariable count increases
					numGlobals++;
					tempCount++;
				}
			}
			else if (TEMP_TYPE == INT_TYPE)
			{
				if (!scanner.tableAddEntry(token.getLexeme(), VAR_ID, INT_TYPE))
				{
					cout << "Duplicate identifier " << token.getLexeme() << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				else
				{
					// addentry was successful, globalvariable count increases
					numGlobals++;
					tempCount++;
					
				}
			}
		}
		
		else
		{
			// we know it is a parameter.  
			if (AMPERSAND)
			{ 
				// Know parameter is a reference parameter. 
				// statements below determine if it is boolean or int type.
				AMPERSAND = false;
				
				if (TEMP_TYPE == BOOLEAN_TYPE)
				{
					if (!scanner.tableAddEntry(token.getLexeme(), REF_PARAM, BOOLEAN_TYPE))
					{
						cout << "Duplicate identifier " << token.getLexeme() << endl;
						printCurrentLine();
						cin.get();
						exit(1);
					}
				}
				else if (TEMP_TYPE == INT_TYPE)
				{
					if (!scanner.tableAddEntry(token.getLexeme(), REF_PARAM, INT_TYPE))
					{
						cout << "Duplicate identifier " << token.getLexeme() << endl;
						printCurrentLine();
						cin.get();
						exit(1);
					}
				}
			}
			else
			{
				// Know parameter is a value parameter. 
				// statements below determine if it is boolean or int type.
				AMPERSAND = false;

				if (TEMP_TYPE == BOOLEAN_TYPE)
				{
					if (!scanner.tableAddEntry(token.getLexeme(), VALUE_PARAM, BOOLEAN_TYPE))
					{
						cout << "Duplicate identifier " << token.getLexeme() << endl;
						printCurrentLine();
						cin.get();
						exit(1);
					}
				}
				else if (TEMP_TYPE == INT_TYPE)
				{
					if (!scanner.tableAddEntry(token.getLexeme(), VALUE_PARAM, INT_TYPE))
					{
						cout << "Duplicate identifier " << token.getLexeme() << endl;
						printCurrentLine();
						cin.get();
						exit(1);
					}
				}
			}
		}
		

		token = scanner.getNextToken();

		identifierTail();
	}
	else
	{
		errorStatement("identifier", token.getLexeme());
	}
}

void parserClass::identTail()
{
	if (token.getType() == COMMA_T)
	{
		token = scanner.getNextToken();
		paramList();
	}
	else
		return;
}


void parserClass::identifierTail()
{
	if (token.getType() == COMMA_T)
	{
		token = scanner.getNextToken();
		identList();
	}
	else
		return;
}

void parserClass::funcDecs()
{

	if (token.getType() == FUNCTION_T)
	{
		outfile << ": starting function" << endl;
		token = scanner.getNextToken();
		if (token.getType() == IDENT_T)
		{

			// part5
			funcName = "$" + token.getLexeme();
			printInstruction(funcName, NULL, "movw", NULL, "r0 r0");

			if (!scanner.tableAddEntry(token.getLexeme(), FUNCT_ID, FUNC_ID_TYPE))
			{
				cout << "Duplicate identifyer " << token.getLexeme() << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
			// adds a table called whatever the function name is.
			scanner.tableAddLevel(token.getLexeme());
			token = scanner.getNextToken();

			PARAM = true;

			funcDecTail();
			if (token.getType() == SEMICOLON_T)
			{
				PARAM = false;
				token = scanner.getNextToken();
				block();
				if (token.getType() == SEMICOLON_T)
				{
					token = scanner.getNextToken();
					funcDecs();
				}
				else
				{
					errorStatement("semicolon", token.getLexeme());
				}
			}
			else
			{
				errorStatement("semicolon", token.getLexeme());
			}
		}
		else
		{
			errorStatement("identifyer", token.getLexeme());
		}
			
	}
	else
		return;
}

void parserClass::funcDecTail()
{
	if (token.getType() == OPENP_T)
	{
		// lets us know we are dealing with a parameter
		isParam = true;

		token = scanner.getNextToken();

		paramList();

		if (token.getType() == CLOSEP_T)
		{
			isParam = false;

			token = scanner.getNextToken();

			//part5
			paramsToStack(scanner.paramCountTest(funcName));
		}
		else
		{
			errorStatement(")", token.getLexeme());
		}
	}
	else
		return;
}

void parserClass::paramList()
{
	type();
	typeTail();
}

void parserClass::typeTail()
{
	if (token.getType() == IDENT_T)
	{
		// add parameters to the item.
		if (PARAM == true)
		{
			if (!scanner.tableAddEntry(token.getLexeme(), VALUE_PARAM, TEMP_TYPE))
			{
				cout << "Duplicate identifier " << token.getLexeme() << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
		}
		token = scanner.getNextToken();
		identTail();
	}
	else if (token.getType() == AMPERSAND_T)
	{
		AMPERSAND = true;
		
		token = scanner.getNextToken();
		if (token.getType() == IDENT_T)
		{
			if (!scanner.tableAddEntry(token.getLexeme(), REF_PARAM, TEMP_TYPE))
			{
				cout << "Duplicate identifier " << token.getLexeme() << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}

			token = scanner.getNextToken();
			identTail();
		}
		else
			errorStatement("identifyer", token.getLexeme());
	}
	else
		errorStatement("identifyer, &", token.getLexeme());
}


void parserClass::programBody()
{
	if (token.getType() == BEGIN_T)
	{
		if (scanner.getCurrentNestingLevel() == 0)
		{
			printInstruction(mainFunctionJump, NULL, "movw", NULL, "r0 r0");
		}

		

		token = scanner.getNextToken();
		followBegin();
	}
	else
	{
		errorStatement("begin", token.getLexeme());
	}
}
// END OF BLOCK METHODS

// START OF STATEMENT
void parserClass::statement()
{
	// if the token is 'while' then do while 'expression' do <statement>
	if (token.getType() == WHILE_T)
	{
		string whileStart = getNextTemp();
		string whileEnd = getNextTemp();
		// code for the top of the while loop
		outfile << ": Starting while loop." << endl;
		printInstruction(whileStart, NULL, "movw", NULL, "R0 R0");

		token = scanner.getNextToken();

		parse_expr();
		
		if (postExprType != BOOLEAN_TYPE)
		{
			cout << "Error: expected boolean expression following a while." << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}


		printInstruction("cmpw", NULL, "#0", NULL, "-4@sp");
		printInstruction("subw", NULL, "#4", NULL, "SP");
		printInstruction("beq", NULL, whileEnd, NULL, "");

		if (token.getType() == DO_T)
		{
			token = scanner.getNextToken();
			statement();

			// jmp $2 : two is the starting point of the while loop. number is made up.
			printInstruction("jmp", NULL, whileStart, NULL, "");
			// after while loop. prints $4 movw R0 R0
			printInstruction(whileEnd, NULL, "movw", NULL, "R0 R0");
			outfile << ": Finished while loop." << endl;
		}
		else
		{
			errorStatement("do", token.getLexeme());
		}
	}

	else if (token.getType() == IF_T)
	{
		string elseLable = getNextTemp();
		string afterIf = getNextTemp();

		token = scanner.getNextToken();
		parse_expr();

		if (postExprType != BOOLEAN_TYPE)
		{
			// method makes sure the type returned from method is a boolean

			cout << "Error: expected boolean expression following a while." << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}


		if (token.getType() == THEN_T)
		{
			outfile << ": starting if statement" << endl;
			printInstruction("cmpw", NULL, "#0", NULL, "-4@sp");
			printInstruction("subw", NULL, "#4", NULL, "SP");
			printInstruction("beq", NULL, afterIf, NULL, "");
			

			token = scanner.getNextToken();
			statement();
			followIf( elseLable, afterIf);
		}
		else
		{
			errorStatement("then", token.getLexeme());
		}
	}

	else if (token.getType() == IDENT_T)
	{
		
		// check to see if the Identifier exists.
		if (scanner.tableLookup(token.getLexeme()) == NULL)
		{
			cout << "Undeclared identifier: " << token.getLexeme() << endl;
			scanner.printCurrentLine();
			cin.get();
			exit(1);
		}
		potentialFuncString = token.getLexeme();
		ident_token = token;
		token = scanner.getNextToken();
		followId(ident_token.getLexeme());
	}
	
	else if (token.getType() == COUT_T)
	{
		token = scanner.getNextToken();
		followCout();
	}

	else if (token.getType() == CIN_T)
	{
		token = scanner.getNextToken();
		followCin();
	}

	else if (token.getType() == BEGIN_T)
	{
		token = scanner.getNextToken();
		followBegin();
	}
	else
	{
		string error = "Error: not a valid statement";
		cout << error << endl;
		printCurrentLine();
		cin.get();
		exit(1);
	}
	
}


// FINISHED
void parserClass::followBegin()
{
	if (token.getType() == END_T)
	{
		token = scanner.getNextToken();
	}
	else
	{
		statement();
		statementTail();
		if (token.getType() == END_T)
		{
			token = scanner.getNextToken();
			return;
		}
		else
			errorStatement("end", token.getLexeme());
	}
}

// START OF STATEMENT METHODS
void parserClass::statementTail()
{
	if (token.getType() == SEMICOLON_T)
	{
		token = scanner.getNextToken();
		statement();
		statementTail();
	}
	else
	{
		// found 'empty string' and thus the end of the statement tail.
		return;
	}
}
void parserClass::followIf( string elseLable, string afterIf)
{
	cout << token.getLexeme();
	if (token.getType() == ELSE_T)
	{
		// 3 in DyKnow.
		printInstruction("jmp", NULL, elseLable, NULL, "");
		printInstruction(afterIf, NULL, "movw", NULL, "r0 r0");
		

		token = scanner.getNextToken();
		statement();
		// 4 in dyknow
		printInstruction(elseLable, NULL, "movw", NULL, "r0 r0");
	}
	else
	{
		// means empty string was found.  part 2 in DyKnow
		// Lable is used to mark the end of the if statement.
		printInstruction(afterIf, NULL, "movw", NULL, "R0 R0");
		outfile << ": Finished if statement." << endl;
		
		return;
	}
		
}
void parserClass::followId(string str)
{
	paramCount = 0;
	if (token.getSubType() == EQUAL_ST) // Assign token
	{
		//cout << "identifier type: " << ident_token.getItemCell()->type << endl;
		// temp is the left side of the equal so in x = y + z another temp points to x
		ItemCell *anotherTemp = scanner.tableLookup(str);
		if (anotherTemp->kind == FUNCT_ID)
		{
			cout << "invalid input. Type mismatch." << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}
		token = scanner.getNextToken();
		parse_expr();

		if (afterParser_token.getItemCell()->type != anotherTemp->type)
		{
			cout << "Error: must compare two ints or two booleans." << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}

		// stores the value from parse_expr in the correct spot then cleans up the stack
		printInstruction("movw", NULL, "-4@sp", anotherTemp, "");
		outfile << ": returned from parse_expr @followId equal_st" << endl;
		printInstruction("subw", NULL, "#4", NULL, "sp");
	}
	else if (token.getType() == SWAP_T)
	{
		ItemCell *firstInSwap = scanner.tableLookup(str);
		token = scanner.getNextToken();
		if (token.getType() == IDENT_T)
		{
			ItemCell *secondInSwap = scanner.tableLookup(token.getLexeme());
			if (firstInSwap->type == secondInSwap->type)
			{
				printInstruction("movw", firstInSwap, "", NULL, "r4");
				printInstruction("movw", secondInSwap, "", firstInSwap, "");
				printInstruction("movw", NULL, "r4", secondInSwap, "");
				token = scanner.getNextToken();
				return;
			}
			else
			{
				cout << "Error: must compare ints to ints or bools to bools" << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
		}
		else
		{
			errorStatement("identifyer", token.getLexeme());
		}
	}
	else if (token.getType() == OPENP_T)
	{
		// found ident followed by "( expression <follow-expression. )" we know it is a function
		token = scanner.getNextToken();
		parse_expr();

		if (postExprType != scanner.tableLookup(funcName)->parameter->type)
		{
			cout << "Error: Invalid parameter type" << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}

		paramCount++;
		followExpression();
	

		if (token.getType() == CLOSEP_T)
		{

			token = scanner.getNextToken();

			// part5
			string thisFunc = "$" + str;

			stringstream ss;
			ss << "#" << scanner.paramCountTest(funcName);

			printInstruction("call", NULL, ss.str(), NULL, thisFunc);
			scanner.deleteSpecialTemps();

			return;

		}
		else
			errorStatement(")", token.getLexeme());
	}
	else
	{
		// catches if there are no parenthases when calling a function
		
		if (scanner.numFuncParams(potentialFuncString) != paramCount)
		{
			// prints an error message if the number of parameters are not the same.
			cout << "Error: incorrect number of parameters for " << potentialFuncString << endl;
			scanner.printCurrentLine();
			cin.get();
			exit(1);
		}

		string thisFuncName = "$" + str;
		printInstruction("call", NULL, "#" + scanner.paramCountTest(funcName), NULL, thisFuncName);

		return;
	}

}
void parserClass::followExpression()
{
	if (token.getType() == COMMA_T)
	{
		//cout << "paramCount: " << paramCount << endl;
		//cout << "potentialFuncString: " << potentialFuncString << endl;
		token = scanner.getNextToken();
		parse_expr();

		// paramCount keeps track of the number of parameters the user put in a given function
		paramCount++;

		followExpression();
	}
	else
	{
		cout << "param count: " << paramCount << endl;
		cout << "numFuncParams: " << scanner.numFuncParams(potentialFuncString) << endl;
		cout << "potentialFuncString: " << potentialFuncString << endl;
		scanner.dumpTables();
		if (scanner.numFuncParams(potentialFuncString) != paramCount)
		{
			// prints an error message if the number of parameters are not the same.
			cout << "Error: incorrect number of parameters for " << potentialFuncString << endl;
			scanner.printCurrentLine();
			cin.get();
			exit(1);
		}
		return;
	}

}
void parserClass::followCin()
{
	if (token.getType() == EXTRACT_T)
	{
		token = scanner.getNextToken();
		if (token.getType() == IDENT_T)
		{
			ItemCell *theIdent = scanner.tableLookup(token.getLexeme());

			if (theIdent->nestingLevel == 0)
			{
				outfile << "inw +" << theIdent->offset * 4 << "@R0" << endl;
			}
			else
			{
				outfile << "inw +" << theIdent->offset * 4 << "@fp" << endl;
			}


			token = scanner.getNextToken();
			return;
		}
		else
		{
			errorStatement("identifyer", token.getLexeme());
		}
	}
	else
	{
		outfile << "inb $junk" << endl;
		return;
	}
	
}

// Cout means insert
void parserClass::followCout()
{
	if (token.getType() == INSERT_T)
	{
		token = scanner.getNextToken();
		followInsert();
	}
	else
	{
		errorStatement("insert", token.getLexeme());
	}
}

void parserClass::followInsert()
{
	if (token.getType() == ENDL_T)
	{
		outfile << "outb #10" << endl;

		token = scanner.getNextToken();
		coutTail();
	}
	else if (token.getType() == STRING_T)
	{
		// added code to print ascii
		for (int i = 0; i < token.getLexeme().length(); i++)
		{
			if (token.getLexeme().at(i) == ' ')
			{
				outfile << "outb #32" << endl;
			}
			else
			{
				outfile << "outb ^" << token.getLexeme().at(i) << endl;
			}
		}
		// end of added code

		token = scanner.getNextToken();
		coutTail();
	}
	else if (token.getType() == TRUE_T ||
		token.getType() == FALSE_T ||
		token.getType() == DIGIT_T ||
		token.getType() == IDENT_T ||
		token.getType() == OPENP_T)
	{
		tokenClass originalToken = token;
		
		// parsing cout expression
		parse_expr();
		if (originalToken.getType() == IDENT_T)
		{
			printInstruction("outw", NULL, "-4@sp", NULL, "");
		}
		if (originalToken.getType() == OPENP_T)
		{
			printInstruction("outw", NULL, "-4@sp", NULL, "");
		}
		
		coutTail();

	}
	else
	{
		errorStatement("expression, string, or endl", token.getLexeme());
	}
}

void parserClass::coutTail()
{
	if (token.getType() == INSERT_T)
	{
		followCout();
	}
	else
		return;
}


// END OF STATEMENT METHODS

void parserClass::parseProgram()
{
	// loads the first token for statement.
	token = scanner.getNextToken();

	if (token.getType() == PROGRAM_T)
	{
		tempCount = 0;
		numGlobals = 0;
		e_token.setToken(E_T, NONE_ST, "E");
		e_token.setTokenPointer(NULL);
		outfile << "$junk #1" << endl;
		outfile << "$main movw SP R0" << endl;
		token = scanner.getNextToken();
		if (token.getType() == IDENT_T)
		{
			scanner.tableAddLevel(token.getLexeme());
			token = scanner.getNextToken();
			if (token.getType() == SEMICOLON_T)
			{
				token = scanner.getNextToken();
				block();


				if (token.getType() == PERIOD_T)
				{
					outfile << "inb $junk" << endl;
					outfile << "end" << endl;
					outfile.close();
					return;
				}
				else
					errorStatement(".", token.getLexeme());
			}
			else
				errorStatement(";", token.getLexeme());
		}
		else
			errorStatement("identifier", token.getLexeme());
	}
	else
		errorStatement("program", token.getLexeme());
}

void parserClass::errorStatement(string expected, string input)
{
	cout << "Error: Found " << input << " when expecting one of " << expected << 
		" at or near line" << endl;
	printCurrentLine();
	cin.get();
	exit(1);
}

void parserClass::printInstruction(string instruction, ItemCell *tempOne, string op1, ItemCell *tempTwo, string op2)
{
	outfile << instruction << " ";


	if (tempOne == NULL)
	{
		outfile << op1 << " ";
	}
	else
	{
		if (tempOne->nestingLevel == 0)
		{
			outfile << "+" << 4 * tempOne->offset << "@r0" << " ";
		}
		else
		{
			outfile << "+" << 4 * tempOne->offset << "@fp" << " ";
		}
	}


	if (tempTwo == NULL)
	{
		outfile << op2 << endl;
	}
	else
	{
		if (tempTwo->nestingLevel == 0)
		{
			outfile << "+" << 4 * tempTwo->offset << "@r0" << endl;
		}

		else
		{
			outfile << "+" << 4 * tempTwo->offset << "@fp" << endl;
		}
	}
}

string parserClass::getNextTemp()
{
	stringstream ss;

	static int nextCt = 0;

	ss << "$" << nextCt++;

	return ss.str();
}

string parserClass::getSpecialTemp()
{
	stringstream ss;

	static int nextCt = 0;

	ss << "$s" << nextCt++;

	return ss.str();
}

void parserClass::paramsToStack(int numParams)
{
	while (numParams != 0)
	{
		stringstream ss;

		ss << "-" << (numParams - 1) * 4 << "@AP";

		outfile << ": start of moving parameters to the top of the stack" << endl;
		printInstruction("movw", NULL, ss.str(), NULL, "@SP");
		printInstruction("addw", NULL, "#4", NULL, "SP");
		outfile << ": finished adding parameters to the top of the stack." << endl;

	}
}