#include "user.hpp"
#include <stdio.h>
#include <map>

User::User()
{
    
}

std::string User::getPath()
{
    return this->relPath + this->dirPath + this->strToLower(this->username);
}

bool User::removeSelf()
{
    if(!this->isAuth)
    {
        std::cout << "\nNot auth\n";
        return false;
    }

    std::string pathProfile = this->getPath() + ".txt";
    std::string pathHistory = this->getPath() + "_history" + ".txt";

    return !remove(pathProfile.c_str()) && !remove(pathHistory.c_str());
}

void User::getInfo()
{
    if(!this->isAuth)
    {
        std::cout << "\nNot auth\n";
    }

    std::cout << "\nUsername: " << this->username << std::endl;

    this->getBooksInfo();
    this->getHistory();
}

void User::getBooksInfo()
{
    if(this->books.size())
    {
        std::cout << "\nBooks:\n";

        for(int i  = 0; i < this->books.size(); i++)
        {   
            std::cout << i << "\n";
            books[i].getInfo(0);
        }
    } 
    std::cout << "\nCount of Books: " << this->books.size() << std::endl;
}

bool User::bookTest(Book b)
{

    for(int i  = 0; i < this->books.size(); i++)
    {  
        if( (b.author == books[i].author) && (b.subject == books[i].subject) && (b.title == books[i].title) )
        {
            std::cout << "\nError: This book exist in your catalog\n";
            return false;
        }
    }

    return true;
}

bool User::getBook()
{

    if(!this->isAuth)
    {
        std::cout << "\nNot auth\n";
        return false;
    }

    std::vector<Book> tempV;

    if(!this->findBook(tempV)) return false;

    int c = this->inputMinMax("Input number of book to get: ", 0, tempV.size() - 1);

    if(!this->bookTest(tempV[c]))
    {
        std::cout<<"\nIncorect data(you have this book)\n";
        return false;
    }

    if(tempV[c]--)
    {
        Book b = tempV[c];

        std::string fileName = this->getPath() + ".txt";

        std::ofstream f(fileName, std::ios_base::app);

        b.write(f);

        this->books.push_back(b);

        this->writeHistory("Take:", b);

        return true;
    }
    return false;
}

bool User::unloadBook()
{
    if(!this->isAuth)
    {
        std::cout << "\nNot auth\n";
        return false;
    }

    this->getBooksInfo();

    if(this->books.size())
    {
        int c = this->inputMinMax("Input number of book to unload:", 0, this->books.size() - 1); 

        Book b = this->books[c];

        this->books.erase (this->books.begin() + c);

        Book tmp;
        if(tmp.setAllInfo(b.pathToFile(), true))
        {
            this->save();
            this->writeHistory("Unload:", b);
            return tmp++;
        }

        if(b.setCount(1))
        {
            this->save();
            return this->writeHistory("Unload:", b) && b.save();
        }

        return false;
    }

    std::cout << "No books to unload";

    return false;
}

bool User::initBooks()
{
    std::string fileName = this->getPath() + ".txt";

    std::string str;

    std::ifstream f(fileName);

    f>>str;
    f>>str;

    while(f)
    {
        std::map<std::string, std::string> m;
        f >> m["author"];
        if(!f) break;
        f >> m["subject"];
        if(!f) break;
        f >> m["title"];
        if(!f) break;

        Book b(m);

        this->books.push_back(b); 
    }
    
    return true;
}

bool User::save()
{
    std::string path = this->getPath() + ".txt";

    if(!this->isFile(path))
    {
        std::cout << "No Such user";
        return false;
    }

    std::ofstream f (path);

    f << this->username + "\n";
    f << this->password;

    for(int i = 0; i < this->books.size(); i++)
    {
        this->books[i].write(f);
    }

    return true;
}

bool User::writeHistory(std::string text, Book b)
{
    std::string path = this->getPath() + "_history" + ".txt";

    if(!this->isFile(path))
    {
        std::cout << "No Such history";
        return false;
    }

    std::ofstream f(path, std::ios_base::app);

    f << "\n" + text;
    b.write(f);

    f.close();

    return true;
}

bool User::getHistory()
{
    std::string path = this->getPath() + "_history" + ".txt";

    if(!this->isFile(path))
    {
        std::cout << "No Such history";
        return false;
    }

    std::ifstream f(path);

    std::cout << "\nHistory: \n\n";

    while(f)
    {
        std::string tmp;
        f >> tmp;

        std::cout << tmp << "\n";
    }

    return true;
}