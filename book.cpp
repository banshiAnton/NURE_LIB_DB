#include "book.hpp"
#include <stdio.h>

Book::Book()
{

}

Book::Book( std::map<std::string, std::string> m )
{
    this->author = m["author"];
    this->title = m["title"];
    this->subject = m["subject"];
}

bool Book::operator++ (int)
{
    this->count++;
    return this->save();
}

bool Book::operator-- (int)
{
    if(!(--this->count))
    {   
        return this->removeSelf();
    } else
    {
        return this->save();
    }

}

void Book::getInfo(bool b)
{
    std::cout << "\n\tauthor: " << this->author << std::endl;
    std::cout << "\ttitle: " << this->title << std::endl;
    std::cout << "\tsubject: " << this->subject << std::endl;
    if(b)
        std::cout << "\tcount: " << this->count << std::endl << std::endl;
}

bool Book::setAllInfo()
{
    bool b = false;

    std::cout << "\nInput new book info\n\n";

    std::cout << "Input new book autor: ";
    std::cin >> this->author;
    b = this->input( this->author, "0", &this->validateNameAndSubject );
    if(!b) return false;

    std::cout << "Input new book title: ";
    std::cin >> this->title;
    b = this->input( this->title, "0", &this->validateTitle );
    if(!b) return false;

    std::cout << "Input new book subject: ";
    std::cin >> this->subject;
    b = this->input( this->subject, "0", &this->validateNameAndSubject );
    if(!b) return false;

    std::string temp;
    std::cout << "Input new book count: ";
    std::cin >> temp;
    b = this->input( temp, "stp", &this->validateNumb, this->count );
    if(!b) return false;

    this->isSet = true;

    return this->save();
}

bool Book::setAllInfo(std::string fileName, bool b)
{
    if(!this->isFile(fileName))
    {
        if(b) std::cout << "No such file";
        return false;
    }

    std::ifstream f;

    f.open(fileName);

    f >> this->author;
    if(!this->validateNameAndSubject(this->author)) return false;

    f >> this->subject;
    if(!this->validateNameAndSubject(this->subject)) return false;

    f >> this->title;
    if(!this->validateTitle(this->title)) return false;

    std::string temp;
    f >> temp;
    if(!this->validateNumb(temp)) return false;

    this->count = std::stoi(temp, nullptr, 10);
    if(this-count == 0) return false;

    this->isSet = true;

    return this->save();
}

bool Book::save()
{
    std::string path = this->pathToFile();

    std::ofstream bookFile;
    bookFile.open(path);

    bookFile << this->author + "\n";
    bookFile << this->subject + "\n";
    bookFile << this->title + "\n";
    bookFile << this->count;

    bookFile.close();

    return true;
}

bool Book::removeSelf()
{

    std::string path = this->pathToFile();

    return !remove(path.c_str());
}

bool Book::write(std::ostream & _stream)
{
    _stream << "\n" + this->author + "\n";
    _stream << this->subject + "\n";
    _stream << this->title;

    return true;
}

bool Book::setCount(int c)
{
    if(!(c > 0)) return false;

    this->count = c;

    return true;
}

std::string Book::pathToFile()
{
    return this->relPath + "books/" + this->strToLower(this->author) + "_" + this->strToLower(this->subject) + "_" + this->strToLower(this->title) + ".txt";
}