#include "admin.hpp"
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

Admin::Admin()
{
    
}

std::string Admin::getPath()
{
    return this->relPath + this->dirPath + this->strToLower(this->username);
}

bool Admin::removeSelf()
{
    if(!this->isAuth)
    {
        std::cout << "\nNot auth\n";
        return false;
    }

    std::string pathProfile = this->getPath() + ".txt";

    return !remove(pathProfile.c_str());
}

bool Admin::removeBook()
{
    std::vector<Book> v;
    if(!this->findBook(v)) return false;
    int index = this->inputMinMax("\nInput number  of book to delet ", 0, v.size() - 1);
    int c = this->inputMinMax("\nDelet one(0) or all(1)", 0, 1);

    if(c)
    {
        return v[index].removeSelf();
    } else {

        return v[index]--;
    }
}

bool Admin::addBook()
{
    int opt = this->inputMinMax("\nAdd one book more(0) or another book(1)", 0, 1);

        if(opt)
        {
            Book b;

            opt = this->inputMinMax("\nAdd your self(0) or file(1)", 0, 1);

            if(!opt) 
            {
                return b.setAllInfo();
            } else
            {
                std::string path = "";
                std::cout << "Input path to file: ";
                std::cin >> path;
                return b.setAllInfo(path);
            }
            return b.save();

        } else
        {
            std::vector<Book> v;
            if(!this->findBook(v)) return false;
            int index = this->inputMinMax("\nInput number to inc:", 0, v.size() - 1);
            return v[index]++;
        } 
}

bool Admin::addUser()
{
    std::cout << "Add user";

    User u;
    if(u.signUp(1))
    {
        u.getInfo();
        return true;
    }
    
    return false;
}

bool Admin::getUser(bool b)
{
    std::string username = "";

    std::string path = this->relPath + this->dirUsers;

    bool b1 = false;
    bool bCount = false;

    std::cout << "\nInput username: ";
    std::cin >> username;
    b1 = this->input( username, "0", &this->validateNameAndSubject );
    if(!b1) return false;

    DIR* dirp = opendir(path.c_str());

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {

        std::string file = dp->d_name;

        if(file.find(this->strToLower(username) + ".txt") != std::string::npos)
        {
            bCount = true;
            User u;
            if(u.auth(path + file))
            { 
                u.initBooks();
                u.getInfo();
                if(b) return u.removeSelf();
            }
        }
    }

    closedir(dirp);

    if(!bCount) std::cout << "\nNo Such User\n";

    return true;
}

bool Admin::getUsers(std::vector<User>& vUsers)
{
    std::string path = this->relPath + this->dirUsers;

    DIR* dirp = opendir(path.c_str());

    int i = 0;
    int i2 = 0;

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        i2++;
        if(i2 < 3) continue;

        std::string file = dp->d_name;
        if(file.find("_history.txt") != std::string::npos) continue;

        User u;
        u.auth(path + file);
        vUsers.push_back(u);
        std::cout << "\n" << i++;
        u.getInfo();
    }

    closedir(dirp);

    return true;
}

void Admin::getUsersInfo()
{
    std::string path = this->relPath + this->dirUsers;

    DIR* dirp = opendir(path.c_str());

    int i = 0;
    int i2 = 0;

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        i2++;
        if(i2 < 3) continue;

        std::string file = dp->d_name;
        if(file.find("_history.txt") != std::string::npos) continue;

        User u;
        u.auth(path + file);
        u.initBooks();
        std::cout << "\n" << i++;
        u.getInfo();
    }

    closedir(dirp);
}

bool Admin::removeUser()
{
    int c = this->inputMinMax("Remove concret user(0) or from list(1)\n", 0, 1);

    if(!c)
    {
        return this->getUser(true);
    } else
    {
        std::vector<User> vUsers;
        if(!this->getUsers(vUsers)) return false;

        int index = this->inputMinMax("Input index to delet:", 0, vUsers.size() - 1);

        return vUsers[index].removeSelf();
    }
}