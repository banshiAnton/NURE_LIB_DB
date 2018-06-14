#include "person.hpp"
#include "book.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

Person::Person()
{

}

std::string Person::getPath()
{
    return this->relPath + this->dirPath + this->strToLower(this->username);
}

bool Person::auth()
{
    bool b = false;

    std::cout << "\nInput username: ";
    std::cin >> this->username;
    b = this->input( this->username, "0", &this->validateNameAndSubject );
    if(!b)
    {
        std::cout << "\nInvalid username\n";
        return false;
    }

    std::cout << "\nInput password: ";
    std::cin >> this->password;
    b = this->input( this->password, "0", &this->validatePwd );

    if(!b) 
    {
        std::cout << "\nInvalid passworsd\n";
        return false;
    }

    return true;
}

bool Person::auth(std:: string path)
{
    if(!this->isFile(path))
    {
        std::cout << "\nNo such file\n";
        return false;
    }

    std::ifstream f;
    f.open(path);

    f >> this->username;
    if(!this->validateNameAndSubject(this->username))
    {
        std::cout << "\nInvalid username\n";
        return false;
    }

    f >> this->password;
    if(!this->validatePwd(this->password))
    {
        std::cout << "\nInvalid passworsd\n";
        return false;
    }

    return this->isAuth = true;
}

bool Person::signUp(bool b)
{
    if(!this->auth())
    {
        std::cout << "\nAuth error\n";
        return false;
    }

    std::string fileName = this->getPath() + ".txt";

    if(this->isFile(fileName))
    {
        std::cout << "\nUser already exist\n";
        return false;
    } 

    std::ofstream file;
    file.open(fileName);

    file << this->username + "\n";

    file << this->password;

    file.close();

    if(b)
    {
        std::ofstream fHistory (this->getPath() + "_history" + ".txt");
        fHistory.close();
    }


    return this->isAuth = true;
}

bool Person::signIn()
{
    if(!this->auth())
    {
        std::cout << "\nAuth error\n";
        return false;
    }

    std::string fileName = this->getPath() + ".txt";

    if(!this->isFile(fileName))
    {
        std::cout << "\nNo such user\n";
        return false;
    }

    std::string tmpPwd;

    std::ifstream f;
    f.open(fileName);

    f >> this->username;

    f >> tmpPwd;

    if(tmpPwd != this->password)
    {
        std::cout << "\nInvalid passwor compare\n";
        return false;
    }

    f.close();

    
    return this->isAuth = true;
}


bool Person::findBook()
{
    bool b = false;

    std::string field = "";

    int n = this->inputMinMax("Choose search field: author(0), subject(1), title(2), all books(3)\n", 0, 3);

    if(n != 3)
    {
        std::cout << "\ntype field: ";
        std::cin >> field;
        field = this->strToLower(field);
    }

    if(!n)
    {
        b = this->input( field, "0", &this->validateNameAndSubject );
        field += "_";
    } else if(n == 1) 
    {
        b = this->input( field, "0", &this->validateNameAndSubject );
        field = "_" + field + "_";
    } else if(n == 2)
    {
        b = this->input( field, "0", &this->validateTitle );
        field = "_" + field;
    } else
    {
        field = "";
        b = true;
    }

    if(!b)
    {
        std::cout << "\nInvalid field\n";
        return false;
    }

    DIR* dirp = opendir(this->bookPath.c_str());

    int i = 0;
    int i2 = 0;

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {

        i2++;
        if(i2 < 3) continue;

        std::string file = dp->d_name;

        if(file.find(field) != std::string::npos)
        {
            Book b;
            if(b.setAllInfo(this->bookPath + file))
            {
                std::cout << "\n" << i++;
                b.getInfo();
            }
        }
    }

    closedir(dirp);

    return b;
}

bool Person::findBook(std::vector<Book>& vBooks)
{
    bool b = false;

    std::string field = "";

    int n = this->inputMinMax("Choose search field: author(0), subject(1), title(2), all books(3)\n", 0, 3);

    if(n != 3)
    {
        std::cout << "\ntype field: ";
        std::cin >> field;
        field = this->strToLower(field);
    }

    if(!n)
    {
        b = this->input( field, "0", &this->validateNameAndSubject );
        field += "_";
    } else if(n == 1) 
    {
        b = this->input( field, "0", &this->validateNameAndSubject );
        field = "_" + field + "_";
    } else if(n == 2)
    {
        b = this->input( field, "0", &this->validateTitle );
        field = "_" + field;
    } else
    {
        field = "";
        b = true;
    }

    if(!b) return false;

    DIR* dirp = opendir(this->bookPath.c_str());

    int i = 0;
    int i2 = 0;

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {

        i2++;
        if(i2 < 3) continue;

        std::string file = dp->d_name;

        if(file.find(field) != std::string::npos)
        {
            Book b;
            if(b.setAllInfo(this->bookPath + file))
            {
                vBooks.push_back(b);
                std::cout << "\n" << i++;
                b.getInfo();
            }
        }
    }

    closedir(dirp);

    if(!vBooks.size()) std::cout << "\nNo such book(s)\n";

    return (bool)vBooks.size();
}