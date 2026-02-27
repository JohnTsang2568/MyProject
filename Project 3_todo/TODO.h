#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#ifndef TODO_H
#define TODO_H

class TODO
{
public:
	TODO() : name(""),importance(0), date("0-0-0"), index(0), completed(false)
	{
	}
	void setTODO(const std::string& name);
	void setImportance(const size_t importance);
	void setDate(const std::string& date);
	void setIndex(size_t index);
	void set_TODO_dependency(const std:: string & dependency);
	void set_completed();

	size_t index;
	std::string name;
	size_t importance;
	std::string date;
	std::vector <std::string> dependencies;
	bool completed;
	//Functions that set parameters of TODOs

	
private:
	
	//Parameters of TODOs

};
//A TODO is a task to be finished in the TODO list!

#endif