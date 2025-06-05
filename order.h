#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>

using namespace std;
void showin4(map<string, int>& mapInfor);   //show information of menu or order, depend on argument

class Account;
class Menu;
class User;

//Class Account used to define nameAccount, password
class Account {
    private:
        string nameAccount;
        string passWord;
    
    public:
        void input();                       //take input from user: name account, password 
        void print();                       //print user information in console
        void setNameAccount();              //change name account
        void setPassword();                 //change password
        int checkInput(string& account);    //check valid input from user
        string& getNameAccount();           //get name account
        string& getPassWord();              //get password
    friend class User;                      //to access nameAccount
};
    
// class inforSignUp inherited from Account, add more function: 
class inforSignUp : public Account {
    public:
        int checkInputSignUp();                 //check valid input from user when they sign up
        int checkExist(string nameAccount, map<string, string>& mapInfor_Main); //check if sign up name account existed 
        int writeToFile();                      //write valid account name and password to file
        int readFromFile(vector<string>& v);    //read account name and password from file
};
    
class inforSignIn : public Account {
    public:
        int checkInputSignIn();                    //check valid input from user when they sign in
        bool checkMatchWithFile(string, string, map<string, string>&);  //check if sign in name account and password match with sign up information file
};

class User{
    private:
    string accountName;     //store account name
    map<string, int> orderFood; //store name food(key) and quantity, if food same name and different quantity => overwrite
    public:
    void setNameAccount(string &);  //set user name = account name when they successfully sign in
    string getUserName();           //get user name
    void clearOrderFood();          //clear order food list of user
    void setOrderFood(Menu&);       //user choose what they want to eat from Menu
    void showOrderedFood();         //show ordered food list of user
   
    int getQuantity();              //take quantity of each feed user want to choose       
};

class Menu{             
    private:
    map<string, int> foodInMenu;    //store name food and price of each food
    public:
    void showMenu();                // display menu on console
    bool getMenu(vector<string>& );  //get Menu from Menu.txt, each line in file contain food and price, so need vector parameter

    friend class User;              //to access foodInMenu attribute to take name and price of food from Menu Class
    friend void showin4(map<string, string>&);  //to access foodInMenu attribute to take name and price of food from Menu Class
};


#endif