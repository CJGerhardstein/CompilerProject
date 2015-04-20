// Chris Gerhardstein table.cpp

#include "stdafx.h"  // Required for visual studio to work correctly

#include "symbolTable.h"
#include "parser.h"

symbolTableClass::symbolTableClass()
{
	// initializes the table to be empty

	top = NULL;
	
}

bool symbolTableClass::tableAddEntry(string lexeme, int kind, int type	)
{
	// Before we add the entry we need to check to make sure there is not already
	// an item declared with the same name.  NOTE: we only need to search the level
	// closest to the top since we are allowed to have variables called the same thing
	// as long as it is in a different nested level.

	ItemCell *search;
	search = top->itemList;
	// TODO: add andother while loop to search parameters of function ??  BOOMS: should we do <-- that?
	while (search != NULL)
	{
		// makes sure there are no duplicate identifiers
		if (_stricmp(search->lexemeValue.c_str(), lexeme.c_str()) == 0)
		{
			// returns false if there is already an identifier named whatever the copy-cat lexeme was.
			return false;
		}
		search = search->next;
	}

	delete search;


	if (kind != REF_PARAM && kind != VALUE_PARAM)
	{
		// add a new entry to the table since we know it is not a duplicate.  
		// We also know it is not a parameter value. 
		ItemCell *newItem = new ItemCell;
		newItem->lexemeValue = lexeme;
		newItem->kind = kind;
		newItem->type = type;
		newItem->offset = top->offset;
		newItem->parameter = NULL;
		newItem->nestingLevel = top->nestingLevel;

		// only increase the TableCell offset if it is a boolean or int. (not function)
		if (type == BOOLEAN_TYPE || type == INT_TYPE)
		{
			top->offset++;
		}

		// Now we will change the pointers so the newItem is at the top of the stack
		if (top->itemList == NULL)
		{
			top->itemList = newItem;

			newItem->next = NULL;
		}
		else
		{
			newItem->next = top->itemList;
			top->itemList = newItem;
		}
		return true;
	}
	else if (kind == REF_PARAM || kind == VALUE_PARAM)
	{
		// start adding to the new method's table level: not params of ItemCell.
		ItemCell *newItem = new ItemCell;
		newItem->lexemeValue = lexeme;
		newItem->kind = kind;
		newItem->type = type;
		newItem->offset = top->offset;
		newItem->parameter = NULL;
		newItem->nestingLevel = top->nestingLevel;

		
		if (type == BOOLEAN_TYPE || type == INT_TYPE)
		{
			top->offset++;
		}
		// Now we will change the pointers so the newItem is at the top of the stack
		if (top->itemList == NULL)
		{
			top->itemList = newItem;
			newItem->next = NULL;
		}
		else
		{
			newItem->next = top->itemList;
			top->itemList = newItem;
		}

		// Finished adding to the method's level now adding new parameters to the param's paramList
		ParamItemCell *newParam = new ParamItemCell;
		newParam->lexemeValue = lexeme;
		newParam->kind = kind;
		newParam->type = type;
		
		
		if (top->next->itemList->parameter== NULL)
		{
			newParam->offset = 0;
			// if there is one parameter make the item's pointer to
			top->next->itemList->parameter = newParam;
			newParam->next = NULL;
		}
		else
		{
			newParam->offset = top->next->itemList->parameter->offset + 1;
			newParam->next = top->next->itemList->parameter;
			top->next->itemList->parameter = newParam;
		}
		
		return true;
	}
	

}

void symbolTableClass::tableAddLevel(string scopingLevel)
{
	// add a new level to the table.  
	// the new level will contain an empty list.  this routine is used when you enter the scope of a new function
	TableCell *tempTable = new TableCell;
	tempTable->next = top;
	top = tempTable;
	if (tempTable->next == NULL)
	{
		tempTable->scopingLevel = scopingLevel;
		tempTable->nestingLevel = 0;
		tempTable->offset = 0;
		tempTable->next = NULL;
		tempTable->itemList = NULL;
	}
	else
	{
		// there is already a level in the cell.
		tempTable->scopingLevel = (tempTable->next->scopingLevel + "." + scopingLevel);
		tempTable->nestingLevel = (tempTable->next->nestingLevel + 1);
		tempTable->offset = 0;
		tempTable->itemList = NULL;
	}
}


void symbolTableClass::tableDeleteLevel()
{
	// delete top most level of the table.  Free all memory.  
	// called after the last token in a function but you need to be sure this is the end
	// of the function and not end of the loop, if statement, or compound statement.

	TableCell *temp = top;
	// takes the level closest to top off the stack.
	top = top->next;

	// deletes all the ItemCells in top
	while (temp->itemList != NULL)
	{
		ItemCell *temp2 = temp->itemList;
		temp->itemList = temp->itemList->next;

		delete temp2;
		
	}

	delete temp;
}

void symbolTableClass::deleteAllTemps()
{
	ItemCell *tempItem = top->itemList;

	while (tempItem != NULL)
	{
		string checker = tempItem->lexemeValue;
		
		if (checker != "")
		{
			if ((checker.at(0) == '$') && (checker.at(0)!='s'))
			{
				tempItem->lexemeValue = "";
				top->offset--;
			}
		}
		
		
		tempItem = tempItem->next;
		
	}
	delete tempItem;
}

ItemCell * symbolTableClass::tableLookup(string lex)
{
	// given a lexeme as a parameter, determine if it appears in the table (may need to search multiple levels)
	// write this routine in terms of a helping function that searches an individual list.  TableLookup should return NULL if
	// specified lexeme is not in the table otherwise it should return a pointer to the node of the list that contains the information
	// about the lexeme.  Self organizing moves it to the front of the list

	
	TableCell *table = top;
	while (table != NULL)
	{
		ItemCell *tempAnswer;
		tempAnswer = tableItemSearch(lex, table);
		
		if (tempAnswer != NULL)
		{
			if (table->itemList->lexemeValue != lex)
			{
				// Search item is currently pointing to the top of the list.
				ItemCell *searchItem = table->itemList;

				// holds the lexeme and answer
				ItemCell *answer = new ItemCell;
				answer->lexemeValue = tempAnswer->lexemeValue;
				answer->next = tempAnswer->next;

				// moves tempAnswer to the head of the list and assigns its next value to be old head of list
				table->itemList = tempAnswer;
				tempAnswer->next = searchItem;

				while (searchItem->next->lexemeValue != answer->lexemeValue)
				{
					searchItem = searchItem->next;
				}

				searchItem->next = answer->next;
				
			}

			// we have found a match! the Item exists in the table.
			return tempAnswer;
	
			
		}
		
		table = table->next;
	}
	// we have not found the lexeme. NULL returned.

	return NULL;
}

ItemCell * symbolTableClass::tableItemSearch(string lexeme, TableCell * level)
{
	ItemCell *search;
	search = level->itemList;
	// goes through a table's item list searching for a given lexeme.
	while (search != NULL)
	{
		if ((_stricmp(lexeme.c_str(), search->lexemeValue.c_str()) == 0))
		{
			return search;
		}
		search = search->next;
	}

	return NULL;
}

int symbolTableClass::numFuncParams(string lex)
{
	// returns the number of parameters a method should have.
	TableCell *tempCell = top;
	int paramCt = 0;
	while (tempCell != NULL)
	{
		ItemCell *tempItem = tempCell->itemList;
		while (tempItem != NULL)
		{
			if (tempItem->lexemeValue == lex)
			{
				ParamItemCell *tempParam = tempItem->parameter;
				while (tempParam != NULL)
				{
					paramCt++;
					tempParam = tempParam->next;
				}
				delete tempParam;
			}
			tempItem = tempItem->next;
		}
		delete tempItem;
		tempCell = tempCell->next;
	}
	delete tempCell;



	return paramCt;
}

void symbolTableClass::dumpTable()
// Dumps the contents of the table.
{
	cout << "**********************************" << endl;
	TableCell *tempCell = top;

	while (tempCell != NULL)
	{
		cout << "Name = " << tempCell->scopingLevel << " Nesting level = " << tempCell->nestingLevel << endl;
		ItemCell *tempItem = tempCell->itemList;
		
		while (tempItem != NULL)
		{
			string theType;
			string theKind;
			// if statements are to convert the kind const ints to their appropriate strings.
			if (tempItem->kind == FUNCT_ID)
			{
				theKind = "func-id";
			}
			else if (tempItem->kind == VAR_ID)
			{
				theKind = "var-id";
			}
			else if (tempItem->kind == REF_PARAM)
			{
				theKind = "ref-param";
			}
			else if (tempItem->kind == VALUE_PARAM)
			{
				theKind = "val-param";
			}

			if (tempItem->type == FUNC_ID_TYPE) // FUNC_ID_TYPE
			{
				theType = "func-type";
			}
			else if (tempItem->type == INT_TYPE)
			{
				theType = "int-type";
			}
			else if (tempItem->type == BOOLEAN_TYPE)
			{
				theType = "boolean-type";
			}

			cout << "lexeme = " << tempItem->lexemeValue;
			cout << ", kind=" << theKind;
			cout << ", type=" << theType;
			cout << ", offset=" << tempItem->offset;
			cout << ", nesting level=" << tempItem->nestingLevel << endl;

			ParamItemCell *tempParam = tempItem->parameter;

			// only prints pram-list if it is a function kind.
			int ct = 0;
			while (tempParam != NULL)
			{
				// Assigns string values to the tempParam fields
				if (tempParam->kind == FUNCT_ID)
				{
					theKind = "func-id";
				}
				else if (tempParam->kind == VAR_ID)
				{
					theKind = "var-id";
				}
				else if (tempParam->kind == REF_PARAM)
				{
					theKind = "ref-param";
				}
				else if (tempParam->kind == VALUE_PARAM)
				{
					theKind = "val-param";
				}

				if (tempParam->type == FUNC_ID_TYPE) // FUNC_ID_TYPE
				{
					theType = "func-type";
				}
				else if (tempParam->type == INT_TYPE)
				{
					theType = "int-type";
				}
				else if (tempParam->type == BOOLEAN_TYPE)
				{
					theType = "boolean-type";
				}


				if (ct == 0)
				{
					cout << "\tparam-list:" << endl;
				}
				cout << "\t\tlexeme=" << tempParam->lexemeValue;
				cout << ", kind=" << theKind;
				cout << ", type=" << theType;
				cout << ", offset=" << tempParam->offset << endl;

				tempParam = tempParam->next;
				ct++;
			}
			
			// prints the function parameters if there are any.
			
	
			delete tempParam;

			tempItem = tempItem->next;
			
		}

		delete tempItem;

		tempCell = tempCell->next;
		cout << endl;
		
	}
	delete tempCell;
	cout << "**********************************" << endl;
}

int symbolTableClass::getCurrentNestingLevel()
{
	TableCell *tempCell = top;

	return top->nestingLevel;
}


// start methods that pertain to value params
void symbolTableClass::deleteSpecialTemps()
{
	ItemCell *tempItem = top->itemList;

	while (tempItem != NULL)
	{
		string checker = tempItem->lexemeValue;

		if (checker != "")
		{
			if ((checker.at(0) == '$') && (checker.at(1) == 's'))
			{
				tempItem->lexemeValue = "";
				top->offset--;
			}
		}

		tempItem = tempItem->next;

	}
	delete tempItem;
}

int symbolTableClass::paramCountTest(string lexeme)
{
	// returns the number of parameters in the table
	int paramCount = 0;

	TableCell *searchLevel;
	searchLevel = top;
	while (searchLevel != NULL)
	{
		ItemCell *searchItem;
		searchItem = searchLevel->itemList;

		while (searchItem != NULL)
		{
			ParamItemCell *searchParam;
			searchParam = searchItem->parameter;

			if ((_stricmp(lexeme.c_str(), searchItem->lexemeValue.c_str()) == 0))
			{
				while (searchParam != NULL)
				{
					paramCount++;

					searchParam = searchParam->next;
				}
			}

			searchItem = searchItem->next;
		}

		searchLevel = searchLevel->next;
	}

	return paramCount;
}
bool symbolTableClass::tableAddParam(string lexeme, int kind, int type)
//Adds a param to the frontmost (thus current) function.
{
	//Temporary level we'll use to navigate towards param-holding function.
	TableCell *popLevel;
	popLevel = top->next;

	//Parameter we're going to insert into the param-holding function one level down.
	ParamItemCell *newParam = new ParamItemCell;
	newParam->lexemeValue = lexeme;
	newParam->kind = kind;
	newParam->type = type;
	//newParam->nestingLevel = popLevel->nestingLevel;

	if (popLevel->itemList->parameter == NULL)
	{
		newParam->offset = 0;
		newParam->next = NULL;
		popLevel->itemList->parameter = newParam;
	}
	else
	{
		ParamItemCell *searchParam;
		searchParam = popLevel->itemList->parameter;

		while (searchParam != NULL)
		{
			if ((_stricmp(lexeme.c_str(), searchParam->lexemeValue.c_str()) == 0))
			{
				return false;
			}

			searchParam = searchParam->next;
		}

		newParam->offset = popLevel->itemList->parameter->offset + 1;
		newParam->next = popLevel->itemList->parameter;
		popLevel->itemList->parameter = newParam;
	}

	return true;
}
