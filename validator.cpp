#include "validator.hpp"

#include <iostream>
#include <fstream>
#include <vector>

std::string Validator::strToLower( std::string str)
{
	std::string converted;

	for(int i = 0; i < str.size(); ++i)
		converted += (std::tolower(str[i]));
	
	return converted;
}

bool Validator::isFile( std::string fileName)
{
    bool b = false;
    std::ifstream f(fileName);

    if(f) b = true;

    f.close();

    return b;
}

bool Validator::validateNumb( std::string numb)
{
    std::regex regular("\\D");
    std::cmatch res;

    return !std::regex_search(numb.c_str(), res, regular);
}

bool Validator::validateNameAndSubject( std::string name)
{
    bool b = false;

    // std::regex regular("\\^[a-zA-Z]([a-zA-Z-])*[a-zA-Z]\\$");
    std::regex regular("[^a-zA-Z-]");
    std::cmatch res;

    b = !std::regex_search(name.c_str(), res, regular);

    if(!b) return b;

    if(!(b && ((int)name[0] != 45) && ((int)name[name.size()-1] != 45)))
        b = false;

    return b;
}

bool Validator::validatePwd( std::string numb)
{
    std::regex regular("[^a-zA-Z0-9]");
    std::cmatch res;

    return !std::regex_search(numb.c_str(), res, regular);
}

bool Validator::validateTitle( std::string name)
{

    
    bool b = false;

    std::regex regular("[^ 0-9a-zA-Z-@.]");

    std::cmatch res;
    std::cmatch res1;
    std::cmatch res2;
    // std::cmatch res3;
    // std::cmatch res4;
    // std::cmatch res5;

    b = !std::regex_search(name.c_str(), res, regular);

    if(!b) return b;

    std::regex regularDigital("([a-zA-Z])+\\d([a-zA-Z])+");

    b = !std::regex_search(name.c_str(), res, regularDigital);

    if(!b) return b;


    std::regex regularDot("\\.[a-zA-Z]");

    b = !std::regex_search(name.c_str(), res, regularDot);

    if(!b) return b;

    std::regex regularStrEnd("[a-zA-Z0-9]");

    std::string s1 = "";
    s1.push_back(name[0]);

    std::string s2 = "";
    s2.push_back(name[name.size()-1]);

    if(!(b && (std::regex_search(s1.c_str(), res1, regularStrEnd)) && (std::regex_search(s2.c_str(), res2, regularStrEnd))))
        b = false;

    return b;
}

bool Validator::input(std::string& field, std::string stop, bool (Validator::*func)(std::string))
{
    while(! (this->*func)(field) )
    {
        std::cout << "Wrong Data (input " + stop + " to stop)\n";
        std::cin >> field;

        if(field == stop)
            return false;
    }

    return true;
}

bool Validator::input(std::string& field, std::string stop, bool (Validator::*func)(std::string), int&c )
{
    while(! (this->*func)(field) || field == "0")
    {
        std::cout << "Wrong Data (input " + stop + " to stop)\n";
        std::cin >> field;

        if(field == stop)
            return false;
    }

    c = std::stoi(field, nullptr, 10);

    return true;
}

int Validator::inputMinMax(std::string text, int min, int max)
{
    while(true)
    {
        std::string c = "";
        std::cout << text;
        std::cin >> c;
        
        if(!this->validateNumb(c))
        {
            std::cout << "\nIncorrect\n";
            continue;
        }

        int numb =  std::stoi(c, nullptr, 10);

        if( (numb < min) || (numb > max))
        {
            std::cout << "\nIncorrect\n";
            continue;
        }
        
        return numb;
    }
}