#ifndef TODOMANAGER_H		
#define TODOMANAGER_H
#include <string>
#include"TODO.h"

class TODOmanager
{
public:
	explicit TODOmanager(TODO & task);
	void run_TODOmanager();

private:
	TODO& TODO_now;
	bool execute_cmd(std::string&);
	void show_help() const;
};

#endif