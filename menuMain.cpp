/*
 * assignment5.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: dgv130030
 */

#include <iostream>
#include <string>

#include "stack.h"
#include "queue.h"
#include <queue>

#include "menuList.h"
#include "browserCommand.h"
#include "browserSupport.h"

int main()
{
	// create the menu class
	menuList menu("Browser Support Test");
	// create the browserSupport object
	browserSupport support;

	// build all of the commands
	backCommand backCmd(std::cin, std::cout, support);
	forwardCommand forwardCmd(std::cin, std::cout, support);
	urlCommand urlCmd(std::cin, std::cout, support);
	historyCommand historyCmd(std::cin, std::cout, support);
	clearHistoryCommand clearHistoryCmd(std::cin, std::cout, support);
	clearCacheCommand clearCacheCmd(std::cin, std::cout, support);
	setMaximumCommand setMaxCmd(std::cin, std::cout, support);
	displayMaximumCommand displayMaxCmd(std::cin, std::cout, support);

	// build the menu items
	menuItem back('<', "Left arrow (back)", backCmd);
	menuItem forward('>', "Right arrow (forward)", forwardCmd);
	menuItem url('u', "Enter url", urlCmd);
	menuItem history('h', "Display history", historyCmd);
	menuItem clearHistory('c', "Clear history", clearHistoryCmd);
	menuItem clearCache('a', "Clear cache", clearCacheCmd);
	menuItem setMax('s', "Set maximum history limit", setMaxCmd);
	menuItem displayMax('d', "Display maximum history limit", displayMaxCmd);


	// add the items to the menu
	menu.add(back);
	menu.add(forward);
	menu.add(url);
	menu.add(history);
	menu.add(clearHistory);
	menu.add(clearCache);
	menu.add(setMax);
	menu.add(displayMax);

	// start the application going
	menu.start();


	return 0;
}
