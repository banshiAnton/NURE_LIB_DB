#ifndef _USER_HPP_
#define _USER_HPP_

#include "person.hpp"

#include <string>


class User : public Person
{   
    private:
        std::vector<Book> books;
        std::string dirPath = "users/";
        std::string getPath();
        bool getHistory();
        bool writeHistory(std::string, Book);
        bool bookTest(Book);
        void getBooksInfo();
    public:
        User();
        bool removeSelf();
        void getInfo();
        bool getBook();
        bool initBooks();
        bool save();
        bool unloadBook();
};

#endif