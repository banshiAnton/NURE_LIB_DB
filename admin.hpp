#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_

#include "person.hpp"
#include "user.hpp"

#include <string>
#include <vector>


class Admin : public Person
{
    private:
        std::string dirPath = "admins/";
        std::string dirUsers = "users/";
        std::string getPath();
        bool getUsers(std::vector<User>&);

    public:
        Admin();
        bool removeBook();
        bool removeSelf();
        bool addBook();
        bool addUser();
        bool getUser(bool b = 0);
        bool removeUser();
        void getUsersInfo();
};

#endif