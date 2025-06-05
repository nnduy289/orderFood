#include "order.h"
#include "check.h"

//set user name = account name when they successfully sign in
void User::setNameAccount(string &userName){
     this->accountName = userName;
}

//get user name
string User::getUserName(){
    return this->accountName;
}

//clear order food list of user
void User::clearOrderFood(){
    this->orderFood.clear();
}

//user choose what they want to eat from Menu
void User::setOrderFood(Menu& menu){
   
    int option, temp; //check int here
    string string_temp;
    map<string, int>::iterator it; //it for menu food
    map<string, int>::iterator it2; //it for order of user

    do{
        showin4(menu.foodInMenu);
        cout << "0. Confirm your order ?\n";
        cout << "Choose your order: ";
        
        do{
            cout << "please enter valid value: \n";
            getline(cin, string_temp);
            bool check = checkUnsignInteger(string_temp);
            if(check){
                int num_temp = stoi(string_temp);
                if(num_temp >= 0 && num_temp <= 4){
                    break;
                }
            }
        }while(1);

        option = stoi(string_temp);
        if(!option){
            return;
        }
        temp = option;
        it = menu.foodInMenu.begin();
        while(--temp){
            ++it;       //increase pointer to food to match with menu
        }       
                //if find food exist in order list, then delete and insert new value from user
                it2 = orderFood.find(it->first);
                if(it2 != orderFood.end()){
                    orderFood.erase(it2);
                }
                orderFood.insert({it->first, this->getQuantity() * it->second});
        
    }while(option != 0);
}

//show ordered food list of user
void User::showOrderedFood(){
    cout << "this is your order and price to pay:\n";
    showin4(orderFood);
}

//take quantity of each feed user want to choose  
int User::getQuantity(){
    int quantity;
    string string_temp;
    cout << "Choose your quantity: ";

    do{
        cout << "please enter valid value: \n";
        getline(cin, string_temp);
        bool check = checkUnsignInteger(string_temp);
        if(check){
            int num_temp = stoi(string_temp);
            if(num_temp >= 0 && num_temp <= 100){
                break;
            }
            cout << "Please choose between 0 to 100\n";
        }
    }while(1);

    quantity = stoi(string_temp);
    return quantity;
}

//get Menu from Menu.txt, each line in file contain food and price, so need vector parameter
bool Menu::getMenu(vector<string>& vMenu){
    vector<string> v_temp;
    vector<string>::iterator it;
     // ifstream is used for reading files
    // We'll read from a file called Sample.txt
    std::ifstream inf{ "Menu.txt" };

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Menu.txt could not be opened for reading!\n";
        return false;
    }

    // While there's still stuff left to read
    std::string strInput{};
    
    while (std::getline(inf, strInput)){
       // std::cout << strInput << '\n';
        vMenu.push_back(strInput);
    }
    for(auto x : vMenu){
        stringstream ss(x);
        string word;
        while(ss >> word){
            v_temp.push_back(word);
        }
         it = v_temp.begin();
        this->foodInMenu.insert(make_pair(*v_temp.begin(), stoi(*(++it))));
        v_temp.clear();
    }

    return true;
}

//show information of menu or order, depend on argument
 void showin4(map<string, int>& mapInfor){
    map<string, int>::iterator it;
    int count = 1;
    cout << "***********************\n";
    cout << "No" << "-----" << "Food" << "--------" << "Price\n";
    for(it = mapInfor.begin(); it != mapInfor.end(); ++it){
        cout << count << ".      " << it->first << "     " << it->second << endl;
        count++;
    }
}

// display menu on console
void Menu::showMenu(){
    cout << "This is our menu:\n";
    showin4(this->foodInMenu);
}

 //take input from user: name account, password 
void Account::input() {
    do{
        cout << "Enter Account name: \n";
        getline(cin, this->nameAccount);
        
        cout << "Enter password: \n";
        getline(cin, this->passWord);
    }while(!(checkValidAccountIn4(this->nameAccount) && checkValidAccountIn4(this->passWord)));
    
}

//print user information in console
void Account::print() {
    cout << "Account name: " << nameAccount << " password: " << passWord << '\n';
}

 //change name account
void Account::setNameAccount(){
    cout << "Enter Account name: \n";
    getline(cin >> ws, this->nameAccount);
}

 //change password
void Account::setPassword(){
    cout << "Enter password: \n";
    getline(cin >> ws, this->passWord);
}

//check valid input from user
int Account::checkInput(string& str) {
    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' '){
            cout << "Don't allow whitespace!\n";
            return 0;
        }
    }
    int count = str.length();
    stringstream ss(str);
    string word;
    vector<string> v;
    while (ss >> word) {
        v.push_back(word);
        if (v.size() > 1) {
            return 0;
        }
    }
    return 1;
}

//get name account
string& Account::getNameAccount() {
    return nameAccount;
}

//get password
string& Account::getPassWord() {
    return passWord;
}

 //check valid input from user when they sign up
int inforSignUp::checkInputSignUp() {
    return (Account::checkInput(Account::getNameAccount()) && Account::checkInput(Account::getPassWord()));
}

//check if sign up name account existed 
int inforSignUp::checkExist(string nameAccount, map<string, string>& mapInfor_Main) {
    int count = mapInfor_Main.count(nameAccount);
    if (count > 0) {
        cout << "Already exist name\nPlease enter another name\n";
        return 1;
    }
    return 0;
}

 //write valid account name and password to file
int inforSignUp::writeToFile() {
    ofstream outf{ "Sample1.txt", ios::app };
    if (!outf) {
        cerr << "Uh oh, Sample1.txt could not be opened for writing!\n";
        return -1;
    }
    outf << Account::getNameAccount() << " ";
    outf << Account::getPassWord() << '\n';
    outf.close();
    return 1;
}

//read account name and password from file
int inforSignUp::readFromFile(vector<string>& v) {
    ifstream inf{ "Sample1.txt" };
    if (!inf) {
        cerr << "Uh oh, Sample1.txt could not be opened for reading!\n";
        return -1;
    }
    string strInput{};
    while (getline(inf, strInput)) {
        cout << strInput << '\n';
        v.push_back(strInput);
    }
    inf.close();
    return 1;
}

//check valid input from user when they sign in
int inforSignIn::checkInputSignIn() {
    return (Account::checkInput(Account::getNameAccount()) && Account::checkInput(Account::getPassWord()));
}

//check if sign in name account and password match with sign up information file
bool inforSignIn::checkMatchWithFile(string nameAccount, string passWord, map<string, string>& mapInfor_Main) {
    bool check;
    auto account_exist = mapInfor_Main.find(nameAccount);
    if (account_exist != mapInfor_Main.end()) {
        
        cout << "Account name: " << account_exist->first << endl;
        if (account_exist->second != passWord) {
            cout << "Wrong password\n";
            check = false;
        }
        else {
            cout << "Password: " << account_exist->second << endl;
            check = true;
        }
    }
    return check;
}