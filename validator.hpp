#ifndef _VALIDATOR_HPP_
#define _VALIDATOR_HPP_

#include <string>
#include <regex>
#include <vector>

class Validator
{
    protected:
        std::string relPath = "./db/";
        std::string bookPath = "./db/books/";
        bool isFile( std::string );
        std::string strToLower( std::string );

    public:
        bool validateNumb( std::string );
        bool validateNameAndSubject( std::string );
        bool validateTitle( std::string );
        bool validatePwd( std::string );
        bool input( std::string&, std::string, bool (Validator::*)(std::string) );
        bool input( std::string&, std::string, bool (Validator::*)(std::string), int& );
        int inputMinMax(std::string, int, int);
};

#endif