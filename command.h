/*
 * command.h
 *
 *  Created on: Sep 10, 2018
 *      Author: dgv130030
 */

#ifndef COMMAND_H_
#define COMMAND_H_

class command
{
public:
	command() {}
	virtual ~command() {}
	virtual void execute() = 0;
	virtual void unExecute() {};
};

#endif /* COMMAND_H_ */
