#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#ifndef TODO_H
#define TODO_H

class TODO
{
public:
	TODO() : name(""),importance(0), date(""), index(0)
	{
	}
	void setTODO(const std::string& name);
	void setImportance(const size_t importance);
	void setDate(const std::string& date);
	void setIndex(size_t index);
	void set_TODO_dependency(TODO& item, const TODO& dependency);

	size_t index;
	std::string name;
	size_t importance;
	std::string date;
	std::vector <TODO> dependencies;
	//Functions that set parameters of TODOs

	
private:
	
	//Parameters of TODOs

};
//A TODO is a task to be finished in the TODO list!

#endif