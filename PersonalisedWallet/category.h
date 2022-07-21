// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <852021>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
#include "item.h"
#include <stdexcept>

class Category {
    private:
        std::string name;
        std::map<std::string, Item> items;

    public:
        Category(std::string name);
        const unsigned int size()const;
        const bool empty()const;
        std::string getIdent() const;
        void setIdent(const std::string n);
        Item &newItem(const std::string ident);
        const bool addItem(const Item x);
        Item &getItem(const std::string ident);
        const bool deleteItem(const std::string ident);
        friend bool operator==(const Category &x, const Category &y);
        const std::string str()const;
};

#endif // CATEGORY_H
