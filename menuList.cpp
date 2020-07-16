/*
 * menuList.cpp
 *
 * The menuList class implements a very simple menu system.
 *
 * The menu is made up of a collection of menuItem values.
 * Each menuItem contains a character for the menu (such as
 * a for add), descriptive text (such as "Add an item"), and
 * a command object. The command object is executed when
 * the corresponding menu item is selected.
 *
 * Note that the menuList class does not know what is being
 * done by the command objects, so this allows us to separate
 * the menu from what is actually being executed as a result
 * of the menu item being selected.
 *
 * Note that a menu item of "q exit the menu" will always be
 * the last item in the menu displayed by menuList.
 *
 * The add member function of the menuList class adds an
 * object of type menuItem to the menu. The start() member
 * function starts the display / processing loop for the
 * application. The start member function stops when the
 * application user types in the quit command - q
 *
 *  Created on: Sep 10, 2018
 *      Author: dgv130030
 */

#include <iostream>
#include <string>

#include "menuList.h"

// create menuList with default menu heading
menuList::menuList()
	: itemList(0), menuText(TITLE_TEXT)
{
}

// create menuList with the specified menu heading
menuList::menuList(const std::string &menuText)
	: itemList(0), menuText(menuText)
{
}

// add an item to the list
void menuList::add(menuItem &item)
{
	itemList.push_back(item);
}

// start the menu process
void menuList::start() const
{
	char selectChar;
	do
	{
		// display the menu
		displayMenu();

		// get the menu item selected
		selectChar = getSelection();

		// if it isn't quit process it
		if (selectChar != QUIT)
		{
			bool valid = false;
			// first find it
			for (auto item : itemList)
			{
				if (selectChar == item.select())
				{
					// we found the menu item for the
					// (valid) selectChar value
					valid = true;
					// execute the command
					item.execute();
					// no need to process the rest of
					// the menu items
					break;
				}
			}

			if (valid)
			{
				// it was valid, just output a blank line
				std::cout << std::endl;
			}
			else
			{
				// the item was not valid, display a message and try again
				std::cout << "The menu item '" << selectChar << "' was invalid" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	while (selectChar != QUIT);
}

// display all of the menu item values
void menuList::displayMenu() const
{
	std::cout << menuText << std::endl;
	for (auto &item : itemList)
	{
		std::cout << item.select();
		std::cout << " ";
		std::cout << item.description();
		std::cout << std::endl;
	}
	// display our quit option
	std::cout << QUIT << " " << QUIT_TEXT << std::endl;
}

// get the menu item selection char from the user
char menuList::getSelection() const
{
	char returnValue;
	std::string text;

	// read in the input buffer
	getline(std::cin, text);

	if (text.length() == 0)
	{
		// if it is empty return the null character
		returnValue = '\0';
	}
	else
	{
		// return the character entered
		returnValue = text[0];
	}

	return returnValue;
}

// create the dummyCommand
menuItem::quitCommand menuItem::dummyCommand;

// dummy command
menuItem::menuItem()
	: theSelectChar('q'), theDescription("Quit"), theCommand(dummyCommand)
{
}

// actual, useful, command
menuItem::menuItem(char selectChar, const std::string &descriptionText, command &cmd)
	: theSelectChar(selectChar), theDescription(descriptionText), theCommand(cmd)
{
}

//return selection char
char menuItem::select() const
{
	return theSelectChar;
}

// return descriptoin
std::string menuItem::description() const
{
	return theDescription;
}

// execute the command
void menuItem::execute()
{
	theCommand.execute();
}
