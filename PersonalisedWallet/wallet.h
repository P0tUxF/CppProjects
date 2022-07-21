// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <852021>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H
#include "category.h"
#include <fstream>      

class Wallet {

    private:
        std::map<std::string, Category> categories;

    public:
        Wallet();
        const unsigned int size()const;
        const bool empty()const;
        Category &newCategory(const std::string ident);
        const bool addCategory(const Category x);
        Category getCategory(const std::string ident);
        const bool deleteCategory(const std::string ident);
        void load(const std::string filename);
        void save(const std::string filename);
        friend bool operator==(const Wallet &x, const Wallet &y);
        const std::string str()const; 
};

#endif // WALLET_H
