#include "TODO.h"
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>

void TODO::setTODO(const std::string & name)
{
	this->name = name;
}
void TODO::setImportance(const size_t importance)
{
	this->importance = importance%6;
}
void TODO::setDate(const std::string& date)
{
	this->date = date;
}
void TODO::setIndex(size_t index)
{
	this->index = index;
}

void TODO::set_TODO_dependency(TODO& item, const TODO& dependency)
{
	item.dependencies.push_back(dependency);
}

