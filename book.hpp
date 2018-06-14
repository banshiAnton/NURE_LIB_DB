#ifndef _BOOK_HPP_
#define _BOOK_HPP_

#include "validator.hpp"

#include <string>
#include <map>
#include <iostream>
#include <fstream>


class Book : public Validator
{
    bool isSet = false;

    public:
        std::string author;
        std::string title;
        std::string subject;
        int count;
        Book();
        Book( std::map<std::string, std::string>);
        bool operator++ (int);
        bool operator-- (int);
        void getInfo(bool b = 1);
        bool setAllInfo();
        bool setAllInfo( std::string , bool b = false);
        bool save();
        bool removeSelf();
        bool write(std::ostream&);
        std::string pathToFile();
        bool setCount(int);
};

#endif