#ifndef TODOLIST_H
#define TODOLIST_H

#include<iostream>
#include<vector>
#include"TODO.h"
class TODOlist
{
private:
	

public:
	std::vector<TODO> items;
	TODOlist(std::vector<TODO> now) :items(now) {};
	TODOlist(){};
	void add_TODO_to_list(const TODO& item);
	void delete_by_name(const std::string& name);
	void display_list() const;
	void set_TODO_dependency(const TODO& item, const TODO& dependency);

	//basic settings of the list

	void sort_list_by_importance();
	void sort_list_by_date();

	//sort the list

	TODO& get_item(size_t index);
	std::vector<TODO> ImportExistedList();
	void ExportCurrentList();

	static void Help();

	void search(const std::string& keyword);
	
};


#endif 