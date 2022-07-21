// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <852021>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// An Item class contains multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include "lib_json.hpp"
#include <sstream>

class Item {

    private:
        std::string name;
        std::map<std::string, std::string> entries;

    public: 
        Item(std::string name);
        const unsigned int size()const;
        const bool empty()const;
        void setIdent(const std::string n);
        const bool addEntry(const std::string key, const std::string val);
        std::string getIdent() const;
        std::string getEntry(const std::string key)const;
        const bool deleteEntry(const std::string key); 
        friend bool operator==(const Item &x, const Item &y);
        const std::string str()const;
};
#endif // ITEM_H
