#include "TODOlist.h"
#include<iostream>
#include<vector>
#include <algorithm>
#include <iomanip>
#include<fstream>
#include<sstream>
#include <stdexcept>

namespace {
	bool sort_key_importance(const TODO& a, const TODO& b)
	{
		return a.importance > b.importance;
	}
	bool sort_key_date(const TODO& a, const TODO& b)
	{
		std::stringstream date(a.date); std::stringstream date_1(b.date);
		//initialize sstream using input date

		std::string yy; std::string mm; std::string dd;
		std::string yy_1; std::string mm_1; std::string dd_1;
        //breakdown of the input date

		date >> yy >> mm >> dd;
		date_1 >> yy_1 >> mm_1 >> dd_1;
		//extract from input, end of initialization
		
		if (std::stoi(yy) == std::stoi(yy_1))
		{
			if (std::stoi(mm) == std::stoi(mm_1))
			{
				return std::stoi(dd) <= std::stoi(dd_1);
			}
			return std::stoi(mm) <= std::stoi(mm_1);
		}
		return std::stoi(yy) <= std::stoi(yy_1);
        //compare
	}
	//unnamed util functions
}

void TODOlist::add_TODO_to_list(const TODO& item)
{
	this->items.push_back(item);
}
void TODOlist::delete_by_name(const std::string& name) {
	items.erase(
		std::remove_if(items.begin(), items.end(),
			[&name](const TODO& item) { return item.name == name; }),
		items.end()
	);
}
void TODOlist::display_list ()const
{
	std::cout << std::left;
	//standardrize output

	std::cout << "Index" << std::setw(15) << "TODO" << std::setw(25) << std::endl;
	//print table title
	size_t it = 1;
	for (const auto& v : this->items)
	{
		std::cout << it << std::setw(15) << v.name << std::setw(25) << std::endl;
		it++;
	}
	std::cout << std::endl;
	std::cout << std::setw(0);
	//renew the width of ostream after display the list
}


//basic settings of the list

void TODOlist::sort_list_by_importance()
{
	sort(items.begin(), items.end(), sort_key_importance);
}
void TODOlist::sort_list_by_date()
{
	sort(items.begin(), items.end(), sort_key_date);
}

//sort the list

TODO& TODOlist::get_item(size_t index) {
	if (index >= items.size())
		throw std::out_of_range("Index Error: Out of Range");
	return items[index];
}