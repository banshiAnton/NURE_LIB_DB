#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include "validator.hpp"
#include "book.hpp"

#include <string>
#include <iostream>
#include <vector>


class Person : public Validator
{
    private:
        std::string dirPath;

    protected:
        bool isAuth = false;
        std::string username;
        std::string password;
        virtual std::string getPath();
        

    public:
        Person();
        bool auth();
        bool auth(std::string);
        bool signUp(bool b = 0);
        bool signIn();
        bool findBook();
        bool findBook(std::vector<Book>&);
};

#endif