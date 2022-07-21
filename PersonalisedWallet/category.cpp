// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <852021>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
#include "category.h"

//  Writes a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};

Category::Category(std::string name) :name(name),items(){}

//  Writes a function, size, that takes no parameters and returns an unsigned
//  int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();

const unsigned int Category::size() const{
    return items.size();
}

//  Writes a function, empty, that takes no parameters and returns true
//  if the number of Items in the Category is zero, false otherwise.
//
// Example:
//  Category c{"categoryIdent"};
//  auto empty = c.empty();

const bool Category::empty() const {
    if (items.size() == 0) {
        return true;
    } else {
        return false;
    }
}

//  Writes a function, getIdent, that returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();

std::string Category::getIdent() const{
    return name;
}

//  Writes a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

void Category::setIdent(const std::string n) {
    name = n;
}

//  Writes a function, newItem, that takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");

Item &Category::newItem(const std::string ident) {
    if (items.find(ident) != items.end()) {
        return items.at(ident);
    } else throw std::runtime_error("Object cannot be inserted...");         
}

//  Writes a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);

const bool Category::addItem(const Item x) {
    auto it = items.find(x.getIdent());
    if (it != items.end()) {
        it->second = x;
        return false;
    } else {
        items.insert(std::pair<std::string, Item>(x.getIdent(),x));
        return true;
    }
}
//  Writes a function, getItem, that takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");

Item &Category::getItem(const std::string ident) {
    if (items.find(ident) != items.end()) {
        return items.at(ident);
    } else {
        throw std::out_of_range("No such item exists. ");
    }
}

//  Writes a function, deleteItem, that takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");

const bool Category::deleteItem(const std::string ident) {
    auto it = items.find(ident);
    if (it != items.end()) {
            items.erase(it);
            return true;
    } else {
        throw std::out_of_range("No such item exists. ");
    }
}

//  Writes an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }

bool operator==(const Category &x, const Category &y) {
    return (x.items == y.items);
}

//  Writes a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();

const std::string Category::str() const{
     std::stringstream categoryStream;
     categoryStream << "{";
     unsigned int counter = 0;
     for (auto it = items.begin() ; it != items.end(); it++) {
         categoryStream << "\""<< it->first << "\":" << it->second.str();
         if (items.size() - 1 > counter) {
            categoryStream << ",";
             counter++;
         } 
     }
     categoryStream << "}";
    return categoryStream.str();
}
