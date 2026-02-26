#include "TODOlist.h"
#include<iostream>
#include<vector>
#include <algorithm>
#include <iomanip>
#include<fstream>
#include<sstream>
#include <stdexcept>

std::string EXPORT_PATH = R"(C:\Users\JohnTsang\Desktop\filename.csv)";

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
	std::cout << "Current List: " << std::endl;
	std::cout << "Index" << std::setw(20) << " " << "TODO" << std::setw(25) << std::endl;
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


std::vector<TODO> TODOlist::ImportExistedList()
{
	std::string line;
	std::ifstream file(EXPORT_PATH);
	if (!file.is_open())
	{
		{
			std::cout << "Fail to import existed list.\n" << std::endl;
			return this->items;
		}
	}
	while (std::getline(file, line))
	{
		if (!line.empty() && line.back() == '\r')line.pop_back();
		if (line.empty())continue;
		size_t comma_pos = line.find(",");
		
		if (comma_pos == std::string::npos)continue;
		//skip empty lines and invalid lines
		
		std::string item = line.substr(comma_pos + 1);
		item.erase(item.find_last_not_of(" ") + 1); //remove blankspace
		TODO current;
		current.setTODO(item);
		this->add_TODO_to_list(current);
	}
	std::cout << "Loading from your previous list...Succeed!\n" << std::endl;
	this->display_list();
	file.close();
	return this->items;
}

void TODOlist::ExportCurrentList()
{
	std::ofstream sheet; std::ostringstream ss;
	for (size_t i = 0; i < this->items.size(); ++i)
	{
		ss << i + 1 << "," << this->items.at(i).name << std::endl;
	}
	sheet.open(EXPORT_PATH);
	if (!sheet.is_open())
	{
		std::cout << "Fail to export your list." << std::endl;
		return;
	}
	sheet << ss.str();
	std::cout << "Your list has been exported!\n";
	sheet.flush();
	sheet.close();
}

void TODOlist::Help()
{
	std::cout << "Welcome to the TODOlist Manager" << std::endl;
	std::cout << "Please Enter Command as Follows to Proceed" << std::endl;
	for (size_t i = 0; i < 50; i++)std::cout << "-";
	std::cout << std::endl;
	std::cout << "\"add <TODOname>\" to add a new TODO to your TODOlist" << std::endl;
	std::cout << "\"delete <TODOname>\" to  delete a TODO from your TODOlist:" << std::endl;
	std::cout << "\"list\" to show current TODOlist" << std::endl;
	std::cout << "\"edit\" to edit the status of TODO" << std::endl;
	std::cout << "\"sortimp\" to sort current TODOlist by importance" << std::endl;
	std::cout << "\"sortdate\" to sort current TODOlist by date" << std::endl;
	std::cout << "\"exit\" to exit this application" << std::endl;
	std::cout << R"("export" to export your current list)" << std::endl;;
	std::cout << R"("help" to see instructions)" << std::endl;
	for (size_t i = 0; i < 50; i++)std::cout << "-";
	std::cout << std::endl;

	std::cout << std::endl;
}