// Chris Gerhardstein

#include "stdafx.h"  // Required for visual studio to work correctly

#include "filemngr.h"
#include "scanner.h"

#include <ctype.h>
#include "string"



scannerClass::scannerClass()
{
	string lexeme = "";
}


int scannerClass::getCurrentNestingLevel()
{
	return myTable.getCurrentNestingLevel();
}

// BEGIN METHODS FOR TABLECLASS TO
void scannerClass::tableAddLevel(string lex)
{
	// doesn't need parameters
	myTable.tableAddLevel(lex);
}

bool scannerClass::tableAddEntry(string lexeme, int kind, int type)
{
	// NEEDS PARAMETERS
	return myTable.tableAddEntry(lexeme, kind, type);
}

void scannerClass::tableDeleteLevel()
{
	// doesn't need parameters.  deletes level closest to top.
	myTable.tableDeleteLevel();
}

void scannerClass::deleteAllTemps()
{
	myTable.deleteAllTemps();
}

ItemCell * scannerClass::tableLookup(string lexeme)
{
	return myTable.tableLookup(lexeme);
}

int::scannerClass::numFuncParams(string lex)
{
	return myTable.numFuncParams(lex);
}
// methods to do with value params
void scannerClass::deleteSpecialTemps()
{
	myTable.deleteSpecialTemps();
}
int scannerClass::paramCountTest(string lexeme)
{
	return myTable.paramCountTest( lexeme );
}
bool scannerClass::tableAddParam(string lex, int kind, int type)
{
	return myTable.tableAddParam(lex, kind, type);
}

// END METHODS FOR TABLE CLASS


bool scannerClass::checkExpressionDebuggingStatus()
{
	return expressionDebugging;
}

int scannerClass::getNextState(int row, int input)
{
	int col;
	static int table[14][24] = {
			{ 0, 45, 0, 44, 14, 15, 16, 17, 18, 19, 20, 21, 22, 1, 44, 6, 7, 9, 10, 11, 12, 13, 44, 44 },
			{ 4, 23, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 24, 4, 4, 4, 4, 4, 4, 4, 4, 2 },
			{ 4, 23, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 24, 4, 4, 3, 4, 4, 4, 4, 4, 4 },
			{ 4, 23, 4, 4, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 24, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
			{ 4, 23, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 26, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
			{ 4, 23, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 25, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
			{ 29, 29, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 28, 6, 6, 6, 6, 6, 6, 6, 6 },
			{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 8, 31, 31, 31, 31, 31, 31, 31 },
			{ 30, 30, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
			{ 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 9, 9, 32, 32, 32, 9, 32 },
			{ 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 10, 33, 33, 33, 33, 33 },
			{ 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 34, 34, 34, 34 },
			{ 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 39, 37, 38, 36, 36 },
			{ 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 43, 41, 42, 40, 40 }
	};
	// character return
	if (input == '\n')
	{
		col = 0;
	}
	//
	else if (input == EOF)
	{
		col = 1;
	}
	else if (input == ' ')
	{
		col = 2;
	}
	else if (input == '+')
	{
		col = 4;
	}
	else if (input == '-')
	{
		col = 5;
	}
	else if (input == '*')
	{
		col = 6;
	}
	else if (input == '(')
	{
		col = 7;
	}
	else if (input == ')')
	{
		col = 8;
	}
	else if (input == '.')
	{
		col = 9;
	}
	else if (input == ';')
	{
		col = 10;
	}
	else if (input == ',')
	{
		col = 11;
	}
	else if (input == '&')
	{
		col = 12;
	}
	else if (input == '{')
	{
		col = 13;
	}
	else if (input == '}')
	{
		col = 14;
	}
	else if (input == '\'')
	{
		col = 15;
	}
	else if (input == '/')
	{
		col = 16;
	}
	else if (isalpha(input))
	{
		col = 17;
	}
	else if (isdigit(input))
	{
		col = 18;
	}

	else if (input == '=')
	{
		col = 19;
	}
	else if (input == '<')
	{
		col = 20;
	}
	else if (input == '>')
	{
		col = 21;
	}
	else if (input == '_')
	{
		col = 22;
	}
	else if (input == '$')
	{
		col = 23;
	}
	else
	{
		col = 3;
	}
	return (table[row][col]);
}


tokenClass scannerClass::getNextToken()
{
	int state = 0;

	do
	{
		//tokenClass myToken;
		theLexeme = "";
		char input = theFile.getNextChar();
		if (input == ' ' || input == '\n')
		{
			do{
				input = theFile.getNextChar();
			} while (input == ' ' || input == '\n' || input == '\t');
		}
		// get an input character (use routine from file manager)
		state = getNextState(state, input);
		// look at september 9th slides 18-22. 
		if (input == '_')
		{
			cout << "Lexical error. _ found." << endl;
			printCurrentLine();
			cin.get();
			exit(1);
		}
		//This MASSIVE thing below deals with comments
		if (state == EOF_T)
		{
			myToken.setToken(EOF_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == PLUS_ST)
		{
			theLexeme = theLexeme + input;
			myToken.setToken(ADDOP_T, PLUS_ST, theLexeme);
			return myToken;
		}
		else if (state == MINUS_ST)
		{
			theLexeme = theLexeme + input;
			myToken.setToken(ADDOP_T, MINUS_ST, theLexeme);
			return myToken;
		}
		else if (state == TIMES_ST)
		{
			theLexeme = theLexeme + input;
			myToken.setToken(MULOP_T, TIMES_ST, theLexeme);
			return myToken;
		}
		else if (state == 17)//OPENP_T
		{
			theLexeme = theLexeme + input;
			myToken.setToken(OPENP_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == 18)//CLOSEP_T
		{
			theLexeme = theLexeme + input;
			myToken.setToken(CLOSEP_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == PERIOD_T)
		{
			theLexeme = theLexeme + input;
			myToken.setToken(PERIOD_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == 20) // SEMICOLON
		{
			theLexeme = theLexeme + input;
			myToken.setToken(SEMICOLON_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == COMMA_T)
		{
			theLexeme = theLexeme + input;
			myToken.setToken(COMMA_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == AMPERSAND_T)
		{
			theLexeme = theLexeme + input;
			myToken.setToken(AMPERSAND_T, NONE_ST, theLexeme);
			return myToken;
		}
		else if (state == 1) //OPENBRACKET_T
		{
			// now at "{"
			theLexeme = theLexeme + input;
			input = theFile.getNextChar();
			state = getNextState(state, input);

			if (state == 2)
			{
				// now at {$;
				
				theLexeme = theLexeme + input;
				input = theFile.getNextChar();
				state = getNextState(state, input);

				if (state == 3)
				{
					//now at "{$p"    with p being a letter
					theLexeme = theLexeme + input;
					input = theFile.getNextChar();
					state = getNextState(state, input);

					if (state == 5)
					{
						//now at "{$p+ or {$p-
						theLexeme = theLexeme + input;
						input = theFile.getNextChar();
						state = getNextState(state, input);
						if (input == EOF)
						{
							cout << "EOF encountered after open brace.";
							theFile.printCurrentLine();
							cin.get();
							exit(1);
						}
						if (state == COMPDIRECTIVE_T)
						{
							// know we have compiler directive 
							//now at "{$p+}" or some letter is in there

							theLexeme = theLexeme + input;

							if (theLexeme == "{$p+}")
							{
								setPrinterStatus(true);
							}
							else if (theLexeme == "{$e+}")
							{
								expressionDebugging = true;
							}
							else if (theLexeme == "{$e-}")
							{
								expressionDebugging = false;
							}
							else if (theLexeme == "{$p-}")
							{
								setPrinterStatus(false);
							}
							else if (theLexeme == "{$s+}")
							{
								myTable.dumpTable();
							}
							else
							{
								cout << "Invalid compiler directive: " << theLexeme << endl;
								
							}

							state = 0;
							theLexeme = "";
						}
						// we know this is a comment now.
						else if (state == 4)
						{
							if (input == '}')
							{
								state = 0;
								theLexeme = "";
							}

							// now at {$p+ other
							do{
								if (input == EOF)
								{
									cout << "EOF encountered after open brace.";
									theFile.printCurrentLine();
									cin.get();
									exit(1);
								}
								input = theFile.getNextChar();
							} while (input != '}');
							state = 0;
							theLexeme = "";
						}
						else if (state == ERROR_T)
						{
							// had {$p+ Eof
							cout << "EOF encountered after open brace.";
							theFile.printCurrentLine();
							cin.get();
							exit(1);
						}
					}
					// know that it is a coment
					else if (state == 4)
					{
						if (input == '}')
						{
							state = 0;
							theLexeme = "";
						}
						// go through characters until you encounter a }
						do{
							if (input == EOF)
							{
								cout << "EOF encountered after open brace." << endl;
								theFile.printCurrentLine();
								cin.get();
								exit(1);
							}
							input = theFile.getNextChar();
						} while (input != '}');
						state = 0;
						theLexeme = "";
					}
					else if (input == EOF)
					{
						cout << "EOF encountered after open brace." << endl;
						theFile.printCurrentLine();
						cin.get();
						exit(1);
					}
					else if (state == COMMENT_NONTOKEN)
					{
						state = 0;
						theLexeme = "";
					}
				}
				// know that we have a comment
				else if (state == 4)
				{
					if (input == '}')
					{
						state = 0;
						theLexeme = "";
					}
					do{
						if (input == EOF)
						{
							cout << "EOF encountered after open brace." << endl;
							theFile.printCurrentLine();
							cin.get();
							exit(1);
						}
						input = theFile.getNextChar();
					} while (input != '}');
					state = 0;
					theLexeme = "";
				}
				else if (state == ERROR_T)
				{
					cout << "EOF encountered after open brace.";
					theFile.printCurrentLine();
					cin.get();
					exit(1);
				}
				else if (state == COMMENT_NONTOKEN)
				{
					state = 0;
					theLexeme = "";
				}
			}
			// know that we have a comment
			else if (state == 4)
			{
				if (input == EOF)
				{
					cout << "EOF encountered after open brace." << endl;;
					theFile.printCurrentLine();
					cin.get();
					exit(1);
				}
				if (input == '}')
				{
					state = 0;
					theLexeme = "";
				}
				do{
					if (input == EOF)
					{
						cout << "EOF encountered after open brace.";
						theFile.printCurrentLine();
						cin.get();
						exit(1);
					}
					input = theFile.getNextChar();
				} while (input != '}');
				state = 0;
				theLexeme = "";
			}
			else if (state == ERROR_T)
			{
				cout << "EOF encountered after open brace.";
				theFile.printCurrentLine();
				cin.get();
				exit(1);
			}
			else if (state == COMMENT_NONTOKEN)
			{
				state = 0;
				theLexeme = "";
			}
		}

		//This method deals with > and all variations
		else if (state == 13)
		{
			theLexeme = theLexeme + input;
			input = theFile.getNextChar();
			state = getNextState(state, input);

			if (state == GREATER_ST)
			{
				theFile.pushBack();
				myToken.setToken(RELOP_T, GREATER_ST, theLexeme);
				return myToken;
			}
			else if (state == SWAP_T)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(SWAP_T, NONE_ST, theLexeme);
				return myToken;
			}
			else if (state == EXTRACT_T)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(EXTRACT_T, NONE_ST, theLexeme);
				return myToken;
			}
			else if (state == GREATEREQ_ST)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(RELOP_T, GREATEREQ_ST, theLexeme);
				return myToken;
			}

		}
		// This method deals with < and all of the variations
		// such as <, <=, <<, <>
		else if (state == 12)
		{
			theLexeme = theLexeme + input;
			input = theFile.getNextChar();
			state = getNextState(state, input);
			//cout << input << " " << state << endl;

			if (state == LESS_ST)
			{
				theFile.pushBack();
				myToken.setToken(RELOP_T, LESS_ST, theLexeme);
				return myToken;
			}
			else if (state == LESSEQ_ST)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(RELOP_T, LESSEQ_ST, theLexeme);
				return myToken;
			}
			else if (state == INSERT_T)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(INSERT_T, NONE_ST, theLexeme);
				return myToken;
			}
			else if (state == NOTEQ_ST)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(RELOP_T, NOTEQ_ST, theLexeme);
				return myToken;
			}

		}

		// This method deals with = and ==
		else if (state == 11)
		{
			theLexeme = theLexeme + input;
			input = theFile.getNextChar();
			state = getNextState(state, input);

			if (state == EQUAL_T)
			{
				theFile.pushBack();
				myToken.setToken(EQUAL_T, EQUAL_ST, theLexeme);
				return myToken;
			}
			else if (state == ISEQUAL_ST)
			{
				theLexeme = theLexeme + input;
				myToken.setToken(RELOP_T, ISEQUAL_ST, theLexeme);
				return myToken;
			}
		}
		// this method finds DIGITS
		else if (state == 10)
		{
			int ct = 0;
			do
			{
				ct++;
				theLexeme = theLexeme + input;
				input = theFile.getNextChar();
				state = getNextState(state, input);
			} while (state == 10);

			theFile.pushBack();
			if (ct > 4)
			{
				cout << "Error. Digit is greater than 4 characters." << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
			myToken.setToken(DIGIT_T, NONE_ST, theLexeme);
			return myToken;
		}
		// This method finds the identifyers or sepcial cases such as and, if, etc.
		else if (state == 9)
		{
			int ct = 0;
			do
			{
				ct++;
				theLexeme = theLexeme + input;
				input = theFile.getNextChar();
				state = getNextState(state, input);
			} while (state == 9);



			theFile.pushBack();
			string s1 = theLexeme;
			// if statements determines if the lexemes is too long.
			if (ct > 12)
			{
				cout << "Error. More than 12 digits in the identifyer." << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
			else if (_stricmp(s1.c_str(), "program")==0)
			{
				myToken.setToken(PROGRAM_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "function") == 0)
			{
				myToken.setToken(FUNCTION_T, NONE_ST, theLexeme);
			}

			else if (_stricmp(s1.c_str(), "begin") == 0)
			{
				myToken.setToken(BEGIN_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "end") == 0)
			{
				myToken.setToken(END_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "if") == 0)
			{
				myToken.setToken(IF_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "then") == 0)
			{
				myToken.setToken(THEN_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "else") == 0)
			{
				myToken.setToken(ELSE_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "while") == 0)
			{
				myToken.setToken(WHILE_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "do") == 0)
			{
				myToken.setToken(DO_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "cout") == 0)
			{
				myToken.setToken(COUT_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "cin") == 0)
			{
				myToken.setToken(CIN_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "endl") == 0)
			{
				myToken.setToken(ENDL_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "or") == 0)
			{
				myToken.setToken(ADDOP_T, OR_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "and") == 0)
			{
				myToken.setToken(MULOP_T, AND_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "div") == 0)
			{
				myToken.setToken(MULOP_T, DIV_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "mod") == 0)
			{
				myToken.setToken(MULOP_T, MOD_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "int") == 0)
			{
				myToken.setToken(INT_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "boolean") == 0)
			{
				myToken.setToken(BOOLEAN_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "true") == 0)
			{
				myToken.setToken(TRUE_T, NONE_ST, theLexeme);
			}
			else if (_stricmp(s1.c_str(), "false") == 0)
			{
				myToken.setToken(FALSE_T, NONE_ST, theLexeme);
			}
			else
			{
				myToken.setToken(IDENT_T, NONE_ST, theLexeme);
			}
			
			return myToken;
		}

		// This method is for COMMENTS with two //
		else if (state == 7) // found one /
		{
			theLexeme = theLexeme + input;
			input = theFile.getNextChar();
			state = getNextState(state, input);
			if (state == 8) // found two //
			{
				do
				{
					input = theFile.getNextChar();
					state = getNextState(state, input);
				} while (state == 8);
				if (state == 30)
				{
					if (input == EOF)
					{
						myToken.setToken(EOF_T, NONE_ST, theLexeme);
						return myToken;
					}
					state == 0;
					theLexeme == "";
				}
				state = 0;
				theLexeme = "";
			}
			else if (state == 31) // ERROR STATE returns EOF and error
			{
				cout << "Found / without a second /. invalid comment." << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
			
		}
		// this method finds STRINGS. found one ' at this point
		else if (state == 6)
		{
			int ct = 0;
			theLexeme = theLexeme + input;
			//input = theFile.getNextChar();
			//state = getNextState(state, input);
			do
			{
				input = theFile.getNextChar();
				state = getNextState(state, input);
				if (state == 6)
				{
					theLexeme = theLexeme + input;
				}
				else if (state == 29)
				{
					cout << "Found a Character return or EOF before closing string." << endl;
					printCurrentLine();
					cin.get();
					exit(1);
				}
				ct++;
			} while (state == 6);
			ct--;
			if (ct > 50)
			{
				cout << "Error. the string is longer than 50 characters." << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
			if (state == STRING_T)//114 on page
			{
				myToken.setToken(STRING_T, NONE_ST, theLexeme);
				return myToken;
			}
			else if (state == 28)// 115 on page
			{
				cout << "error found while creating string." << endl;
				printCurrentLine();
				cin.get();
				exit(1);
			}
		}
		else
		{
			cout << "Lexical Error Found." << endl;;
			theFile.printCurrentLine();
			cin.get();
			exit(1);
		}

	} while (1);
}


void scannerClass::dumpTables()
{
	myTable.dumpTable();
}
void scannerClass::closeSourceProgram()
{
	theFile.closeSourceProgram();
}
void scannerClass::setPrinterStatus(bool newStatus)
{
	theFile.setPrinterStatus(newStatus);
}
void scannerClass::printCurrentLine()
{
	theFile.printCurrentLine();
}

int scannerClass::numLinesProcessed()
{
	return theFile.numLinesProcessed();
}


tokenClass::tokenClass()
{
	type = -1;
	subType = -1;
	lexeme = "";
}



void tokenClass::display()
{	
	cout << type;
	if (type == ADDOP_T)
	{
		if (subType == PLUS_ST)
		{
			cout << getLexeme() << " ADDOP_T PLUS_ST" << endl;
		}
		else if (subType == MINUS_ST)
		{
			cout << getLexeme() << " ADDOP_T MINUS_ST" << endl;
		}
		else if (subType == OR_ST)
		{
			cout << getLexeme() << " ADDOP_T OR_ST" << endl;
		}
		return;
	}

	else if (type == MULOP_T)
	{
		if (subType == TIMES_ST)
		{
			cout << getLexeme() << " MULOP_T TIMES_ST" << endl;
		}
		else if (subType == AND_ST)
		{
			cout << getLexeme() << " MULOP_T AND_ST" << endl;
		}
		else if (subType == DIV_ST)
		{
			cout << getLexeme() << " MULOP_T DIV_ST" << endl;
		}
		else if (subType == MOD_ST)
		{
			cout << getLexeme() << " MULOP_T MOD_ST" << endl;
		}
		return;
	}
	else if (type == 17)//OPENP_T
	{
		cout << getLexeme() << " OPENP_T NONE_T" << endl;
		
		return;
	}
	else if (type == 18)//CLOSEP_T
	{
		cout << ") " << "CLOSEP_T";
		if (subType == NONE_ST)
		{
			cout << " " << "NONE_T" << endl;
		}
		return;
	}
	else if (type == PERIOD_T)
	{
		cout << ". " << "PERIOD_T";
		if (subType == NONE_ST)
		{
			cout << " " << "NONE_T" << endl;
		}
		return;
	}
	else if (type == 20) // SEMICOLON_T
	{
		cout << "; " << "SEMICOLON_T";
		if (subType == NONE_ST)
		{
			cout << " " << "NONE_T" << endl;
		}
		return;
	}
	else if (type == COMMA_T)
	{
		cout << ", " << "COMMA_T";
		if (subType == NONE_ST)
		{
			cout << " " << "NONE_T" << endl;
		}
		return;
	}
	else if (type == AMPERSAND_T)
	{
		cout << "& " << "AMPERSAND_T";
		if (subType == NONE_ST)
		{
			cout << " " << "NONE_T" << endl;
		}
		return;
	}
	else if (type == COMPDIRECTIVE_T)
	{
		cout << "{$p+} " << "COMPDIRECTIVE_T";
		if (subType == PRINT_ST)
		{
			cout << " PRINT_T" << endl;
		}
		return;
	}
	else if (type == INSERT_T) // 37 on sheet
	{
		cout << "<< RELOP_T NONE_ST" << endl;
	}
	else if (type == EXTRACT_T)
	{
		cout << ">> EXTRACT_ST NONE_T" << endl;
	}
	else if (type == SWAP_T) // 38 on sheet
	{
		cout << ">< SWAP_T NONE_ST" << endl;
	}
	else if (type == RELOP_T)
	{

		if (subType == GREATER_ST)
		{
			cout << "> RELOP_T GREATER_ST" << endl;
		}
		else if (subType == NOTEQ_ST)
		{
			cout << "<> RELOP_T NOTEQ_ST" << endl;
		}
		else if (subType == GREATEREQ_ST)
		{
			cout << ">= RELOP_T GREATEREQ_ST" << endl;
		}
		else if (subType == LESS_ST) // 36 on sheet
		{
			cout << "< RELOP_T LESS_ST" << endl;
		}
		
		else if (subType == LESSEQ_ST) // 39 on sheet
		{
			cout << "<= RELOP_T LESSEQ_ST" << endl;
		}
		else if (subType == ISEQUAL_ST)
		{
			cout << "== RELOP_T ISEQUAL_ST" << endl;
		}
		return;
	}
	else if (type == EQUAL_T)
	{
		cout << getLexeme() << " EQUAL_T NONE_ST" << endl;
		return;
	}
	
	else if (type == DIGIT_T)
	{
		cout << getLexeme() << " DIGIT_T NONE_ST" << endl;
		return;
	}
	else if (type == IDENT_T)
	{
		cout << getLexeme() << " IDENT_T NONE_S	T" << endl;
		return;
	}
	else if (type == STRING_T)
	{
		cout << getLexeme() << " STRING_T NONE_ST" << endl;
		return;
	}
	else if (type == PROGRAM_T)
	{
		cout << getLexeme() << " PROGRAM_T NONE_ST" << endl;
		return;
	}
	else if (type == FUNCTION_T)
	{
		cout << getLexeme() << " FUNCTION_T NONE_T" << endl;
		return ;
	}
	else if (type == BEGIN_T)
	{
		cout << getLexeme() << " BEGIN_T NONE_T" << endl;
		return;
	}
	else if (type == END_T)
	{
		cout << getLexeme() << " END_T NONE_T" << endl;
		return;
	}
	else if (type == IF_T)
	{
		cout << getLexeme() << " IF_T NONE_T" << endl;
		return;
	}
	else if (type == THEN_T)
	{
		cout << getLexeme() << " THEN_T NONE_T" << endl;
		return;
	}
	else if (type == ELSE_T)
	{
		cout << getLexeme() << " ELSE_T NONE_T" << endl;
		return;
	}
	else if (type == WHILE_T)
	{
		cout << getLexeme() << " WHILE_T NONE_T" << endl;
		return;
	}
	else if (type == DO_T)
	{
		cout << getLexeme() << " DO_T NONE_T" << endl;
		return;
	}
	else if (type == COUT_T)
	{
		cout << getLexeme() << " COUT_T NONE_T" << endl;
		return;
	}
	else if (type == CIN_T)
	{
		cout << getLexeme() << " CIN_T NONE_T" << endl;
		return;
	}
	else if (type == ENDL_T)
	{
		cout << getLexeme() << " ENDL_T NONE_T" << endl;
		return;
	}
	else if (type == INT_T)
	{
		cout << getLexeme() << " INT_T NONE_T" << endl;
		return;
	}
	else if (type == BOOLEAN_T)
	{
		cout << getLexeme() << " BOOLEAN_T NONE_T" << endl;
		return;
	}
	else if (type == TRUE_T)
	{
		cout << getLexeme() << " TRUE_T NONE_T" << endl;
		return;
	}
	else if (type == FALSE_T)
	{
		cout << getLexeme() << " FALSE_T NONE_T" << endl;
		return;
	}
}


// All the getters and setters

int tokenClass::getType()
{
	return type;
}
int tokenClass::getSubType()
{
	return subType;
}
string tokenClass::getLexeme()
{
	return lexeme;
}
ItemCell * tokenClass::getItemCell()
{
	return myTemp;
}
void tokenClass::setType(int newType)
{
	type = newType;
}
void tokenClass::setSubType(int newSubType)
{
	subType = newSubType;
}
void tokenClass::setLexeme(string newLexeme)
{
	lexeme = newLexeme;
}

void tokenClass::setToken(int newType, int newSubType, string newLexeme)
{
	type = newType;
	subType = newSubType;
	lexeme = newLexeme;
}

void tokenClass::setTokenPointer(ItemCell *aTemp)
{
	myTemp = aTemp;
}

