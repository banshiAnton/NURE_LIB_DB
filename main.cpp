#include "book.hpp"
#include "validator.hpp"
#include "person.hpp"
#include "admin.hpp"
#include "user.hpp"

#include <iostream>
#include <regex>
#include <string>

int main()
{
    while(true)
    {
        std::string c = "";

        std::cout << "\n1.Admin\n";
        std::cout << "2.User\n";
        std::cout << "3.Exit\n";
        std::cout << "Input... (1) (2) (3)\n";
        std::cin >> c;

        if(c == "3")
        {
            break;
        }

        if(c == "1")
        {
            while(true)
            {
                std::string b = "";
            
                std::cout << "\nInput 1 to Sign Up(create new account)\n";
                std::cout << "Input 2 to Sign In(auth to exist account)\n";
                std::cout << "Input 3 to go back one step\n";
                std::cin >> b;

                if(b == "3")
                {
                    break;
                }

                Admin a;

                bool auth = false;

                if(b == "1")
                {
                    auth = a.signUp();
                } else if(b == "2")
                {
                    auth = a.signIn();
                } else {
                    std::cout << "\nIncorrect";
                    continue;
                }

                if(auth)
                {
                        while(true)
                        {
                            std::string b1 = "";
            
                            std::cout << "\nInput 1 to Add book\n";
                            std::cout << "Input 2 to Remove book(s)\n";
                            std::cout << "Input 3 to Add User\n";
                            std::cout << "Input 4 to Get User Info\n";
                            std::cout << "Input 5 to Get Users Infos\n";
                            std::cout << "Input 6 to Remove User(s)\n";
                            std::cout << "Input 7 to Delet Account\n";
                            std::cout << "Input 8 to go back one step\n";
                            std::cin >> b1;

                            if(b1 == "8")
                            {
                                break;
                            }

                            if(b1 == "1")
                            {
                                a.addBook();
                            } else if(b1 == "2")
                            {
                                a.removeBook();
                            } else if(b1 == "3")
                            {
                                a.addUser();
                            } else if(b1 == "4")
                            {
                                a.getUser();
                            } else if(b1 == "5")
                            {   
                                a.getUsersInfo();
                            } else if(b1 == "6")
                            {
                                a.removeUser();
                            } else if(b1 == "7")
                            {
                                a.removeSelf();
                                break;
                            } else {
                                std::cout << "\nIncorrect";
                                continue;
                            }
                        }

                } else {
                    std::cout << "\nError auth\n";
                }
            }
        } else if(c == "2")
        {
            while(true)
            {
                std::string b = "";
            
                std::cout << "\nInput 1 to Sign Up(create new account)\n";
                std::cout << "Input 2 to Sign In(auth to exist account)\n";
                std::cout << "Input 3 to go back one step\n";
                std::cin >> b;

                if(b == "3")
                {
                    break;
                }

                User u;

                bool auth = false;

                if(b == "1")
                {
                    auth = u.signUp(1);
                } else if(b == "2")
                {
                    auth = u.signIn();
                } else {
                    std::cout << "\nIncorrect";
                    continue;
                }

                if(auth)
                {
                        while(true)
                        {
                            std::string b1 = "";
            
                            std::cout << "\nInput 1 to Get Info\n";
                            std::cout << "Input 2 to Get book(s)\n";
                            std::cout << "Input 3 to Unload book(s)\n";
                            std::cout << "Input 4 to Delet Account\n";
                            std::cout << "Input 5 to go back one step\n";
                            std::cin >> b1;

                            if(b1 == "5")
                            {
                                break;
                            }

                            if(b1 == "1")
                            {
                                u.getInfo();
                            } else if(b1 == "2")
                            {
                                u.getBook();
                            } else if(b1 == "3")
                            {
                                u.unloadBook();
                            } else if(b1 == "4")
                            {
                                u.removeSelf();
                                break;
                            } else {
                                std::cout << "\nIncorrect";
                                continue;
                            }
                        }
                        
                } else {
                    std::cout << "\nError auth\n";
                    continue;
                }
            }

        } else
        {
            std::cout << "\nIncorrect";
            continue;
        }
    }

    return 0;
}