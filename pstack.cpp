// Chris Gerhardstein


#include "stdafx.h"

#include "pstack.h"
#include "parser.h"
#include "filemngr.h"
#include "scanner.h"


pStackClass::pStackClass()
{
	top = NULL;
}

// pushes something onto the stack
void pStackClass::push(tokenClass theToken)
{
	StackCell *tempCell = new StackCell;
	tempCell->next = top;
	top = tempCell;
	tempCell->type = theToken.getType();
	tempCell->subtype = theToken.getSubType();

	if (theToken.getItemCell() != NULL)
	{
		tempCell->item = theToken.getItemCell();
	}
}

tokenClass pStackClass::pop()
{
	if (top->item == NULL)
	{
		tokenClass newToken;
		newToken.setToken(top->type, top->subtype, "");
		top = top->next;
		return newToken;
	}
	else
	{
		tokenClass newToken;
		newToken.setToken(top->type, top->subtype, "");
		newToken.setTokenPointer(top->item);
		top = top->next;
		return newToken;
	}
}

bool pStackClass::isTerminalOnTopOfStack()
{
	if (top->type != E_T )
	{
		return true;
	}
	else
		return false;
}

tokenClass pStackClass::topTerminalOnStack()
{
	tokenClass newToken;
	StackCell *tempCell1 = new StackCell;

	tempCell1 = top;

	while (tempCell1 != NULL)
	{	
		if (tempCell1->type != E_T)
		{
			newToken.setToken(tempCell1->type, tempCell1->subtype, "");
			return newToken;
		}
		tempCell1 = tempCell1->next;
	}
	cout << "Error: no token on the stack." << endl;
	cin.get();
	exit(1);
	
}

void pStackClass::dump()
{
	StackCell *tempCell = new StackCell;
	tempCell = top;
	cout << "Starting Stack Dump" << endl;
	while (tempCell != NULL)
	{
		cout << "Type: " << tempCell->type << " SubType: " << tempCell->subtype << endl;
		tempCell = tempCell->next;
	}
	cout << "Finished Dumping Stack." << endl;
}

tokenClass pStackClass::topOfStack()
{
	if (top->item != NULL)
	{
		tokenClass newToken;
		newToken.setToken(top->type, top->subtype, "");
		newToken.setTokenPointer(top->item);

		return newToken;
	}
	else
	{
		tokenClass newToken;
		newToken.setToken(top->type, top->subtype, "");


		return newToken;
	}
	
}