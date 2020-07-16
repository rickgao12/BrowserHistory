/*
 * browserCommand.h
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */

#ifndef BROWSERCOMMAND_H_
#define BROWSERCOMMAND_H_

#include <iostream>
#include <string>

#include "command.h"
#include "browserSupport.h"

class browserCommand : public command
{
	protected:
		std::istream &in;
		std::ostream &out;
		browserSupport &support;
	public:
		browserCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~browserCommand();
	protected:
		std::string getText(std::string promptText);
		void displayText(std::string text);
};

class backCommand : public browserCommand
{
	public:
		backCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~backCommand();
		void execute() override;
};

class forwardCommand : public browserCommand
{
	public:
		forwardCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~forwardCommand();
		void execute() override;
};

class urlCommand : public browserCommand
{
	public:
		urlCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~urlCommand();
		void execute() override;
};

class historyCommand : public browserCommand
{
	public:
		historyCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~historyCommand();
		void execute() override;
};

class clearHistoryCommand : public browserCommand
{
	public:
		clearHistoryCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~clearHistoryCommand();
		void execute() override;
};

class clearCacheCommand : public browserCommand
{
	public:
		clearCacheCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~clearCacheCommand();
		void execute() override;
};

class setMaximumCommand : public browserCommand
{
	public:
		setMaximumCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~setMaximumCommand();
		void execute() override;
};

class displayMaximumCommand : public browserCommand
{
	public:
		displayMaximumCommand(std::istream &in, std::ostream &out, browserSupport &support);
		virtual ~displayMaximumCommand();
		void execute() override;
};

#endif /* BROWSERCOMMAND_H_ */
