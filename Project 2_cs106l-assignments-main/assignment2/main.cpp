/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include <random>

std::string kYourName = "John TSANG"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */

 
std::string get_initials(const std::string& full_name) {
    size_t space_pos = full_name.find(' ');
    if (space_pos == std::string::npos || space_pos + 1 >= full_name.size()) {
        return "";
    }
    char first_initial = full_name[0];
    char last_initial = full_name[space_pos + 1];
    return std::string(1, first_initial) + last_initial;
}

std::set<std::string> get_applicants(std::string filename) {
  std::ifstream file(filename);
  std::string name;std::set<std::string> name_list;
  while(std::getline(file,name))
  {
     name_list.insert(name);
  }
  
  return name_list;
}
/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  std::string your_ini=get_initials(name);
  if(your_ini=="")return matches;
  for(const auto & u : students)
  {
    std::string curr= get_initials(u);
    if(curr.empty())continue;
    if(curr==your_ini)
    {
      matches.push(&u);
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
    if (matches.empty()) {
        return "NO MATCHES FOUND.";
    }
    std::vector<const std::string*> vec;
    while (!matches.empty()) {
        vec.push_back(matches.front());
        matches.pop();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vec.size() - 1);
    int index = dis(gen);
    return *vec[index];
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
