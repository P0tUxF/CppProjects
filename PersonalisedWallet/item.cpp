// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <852021>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "item.h"

//  Writes a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};

Item::Item(std::string name) :name(name), entries(){}

//  Writes a function, size, that takes no parameters and returns an unsigned
//  int of the number of entries in the Item contains.
//
// Example:
//  Item iObj{"identIdent"};
//  auto size = iObj.size();

const unsigned int Item::size() const {
    return entries.size();
}

//  Writes a function, empty, that takes no parameters and returns true
//  if the number of entries in the Item is zero, false otherwise.
//
// Example:
//  Item iObj{"identIdent"};
//  auto empty = iObj.empty();

const bool Item::empty()const {
    if (entries.size() == 0) {
        return true;
    } else {
        return false;
    }
}

//  Writes a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");

void Item::setIdent(const std::string n) {
    name = n;
}

//  Writes a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();

std::string Item::getIdent() const {
    return name;
}

//  Writes a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");

const bool Item::addEntry(const std::string key, const std::string val) {
    auto it = entries.find(key);    
    if (it != entries.end()) {
        it->second = val;
        return false;
    } else {
        entries.insert(std::pair<std::string, std::string>
        (key, val));
            return true;
    }
}   

//  Writes a function, getEntry, that takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");

std::string Item::getEntry(const std::string key)const {  
        auto it = entries.find(key); 
        if (it != entries.end())
            return it->second;
        throw std::out_of_range("Out of Range");
}

//  Writes a function, deleteEntry, that takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");

const bool Item::deleteEntry(const std::string key) {
        if (entries.find(key) != entries.end()) {
            entries.erase(key);
            return true;
        } else throw std::out_of_range("No entry exists");         
    return 0;
} 

//  Writes an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }

bool operator==(const Item &x, const Item &y) {
    return (x.entries == y.entries);
}

//  Writes a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();

const std::string Item::str()const {
     std::stringstream itemStream;
     itemStream << "{";
     unsigned int counter = 0;
     for (auto it = entries.begin() ; it != entries.end();
      it++) {
         itemStream << "\""<< it->first << "\":\"" << 
         it->second << "\"";
         if (entries.size() - 1 > counter) {
            itemStream << ",";
             counter++;
         }
     }
     itemStream << "}";
    return itemStream.str();
}
