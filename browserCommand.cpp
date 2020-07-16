/*
 * browserCommand.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */
#include <string>
#include <cstddef>

#include "browserCommand.h"

browserCommand::browserCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: command(), in(in), out(out), support(support)
{
}

browserCommand::~browserCommand()
{
}

std::string browserCommand::getText(std::string promptText)
{
	std::string inputText;
	displayText(promptText);
	getline(in, inputText);
	return inputText;
}

void browserCommand::displayText(std::string text)
{
	out << text << std::endl;
}

backCommand::backCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

backCommand::~backCommand()
{
}

void backCommand::execute()
{
	url backURL= support.back();

	if (backURL.valid())
	{
		displayText("The url is valid and is \"" + static_cast<std::string>(backURL) + "\"");
	}
	else
	{
		displayText("There is no back url available");
	}
}

forwardCommand::forwardCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

forwardCommand::~forwardCommand()
{
}

void forwardCommand::execute()
{
	url forwardURL= support.forward();

	if (forwardURL.valid())
	{
		displayText("The url is valid and is \"" + static_cast<std::string>(forwardURL) + "\"");
	}
	else
	{
		displayText("There is no forward url available");
	}
}

urlCommand::urlCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

urlCommand::~urlCommand()
{
}

void urlCommand::execute()
{
	std::string urlText = getText("Enter the URL");
	support.display(url(urlText));
}

historyCommand::historyCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

historyCommand::~historyCommand()
{
}

void historyCommand::execute()
{
	std::vector<url> history;
	support.history(history);

	if (history.empty())
	{
		displayText("The history is empty");
	}
	else
	{
		for (auto it = history.rbegin(); it != history.rend(); it++)
		{
			const auto &elem = *it;
			displayText(elem);
		}
	}
}

clearHistoryCommand::clearHistoryCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

clearHistoryCommand::~clearHistoryCommand()
{
}

void clearHistoryCommand::execute()
{
	auto size = support.clearHistory();

	if (size == 0)
	{
		displayText("The history is empty");
	}
	else
	{
		displayText("The history was emptied of " + std::to_string(size) + " entries");
	}
}

clearCacheCommand::clearCacheCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

clearCacheCommand::~clearCacheCommand()
{
}

void clearCacheCommand::execute()
{
	auto size = support.clearCache();

	if (size == 0)
	{
		displayText("The cache is empty");
	}
	else
	{
		displayText("The cache was emptied of " + std::to_string(size) + " entries");
	}
}

setMaximumCommand::setMaximumCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

setMaximumCommand::~setMaximumCommand()
{
}

void setMaximumCommand::execute()
{
	std::string sMax = getText("Enter the new maximum size for the URL history");
	std::size_t max = std::stoi(sMax);
	if (max <= 0)
	{
		displayText("The input \"" + sMax + "\" is invalid and must be a number greater than 0");
	}
	else
	{
		support.maximum(max);
		displayText("The new maximum for the URL history is " +std::to_string(max));
	}
}

displayMaximumCommand::displayMaximumCommand(std::istream &in, std::ostream &out, browserSupport &support)
	: browserCommand(in, out, support)
{
}

displayMaximumCommand::~displayMaximumCommand()
{
}

void displayMaximumCommand::execute()
{
	auto max = support.maximum();
	displayText("The maximum for the URL history is " +std::to_string(max));
}
