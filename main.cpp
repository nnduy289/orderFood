#include "order.h"
#include "check.h"



void orderFood(Menu& ourMenu, User& person, vector<string>& vMenu, vector<User>& manageUser){
    int optionOrder;
    string string_temp;
    bool checkExistUser = false;
   vector<User>::iterator it2;
    map<string, int> orderFood;
    
    do{ 
        cout << "Hello " << person.getUserName() << endl;
        cout << "0. Exit order program!\n";
        cout << "1. Show menu\n";
        cout << "2. Fill your order\n";
        cout << "3. Show your order\n";
        cout << "4. Clear your order\n";
        cout << "ORDER FOOD: Choose your option: \n";

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

        optionOrder = stoi(string_temp);


        // cin >> optionOrder;
        // cin.ignore();
        
                    switch(optionOrder){
                        case 1:
                            ourMenu.getMenu(vMenu);
                            ourMenu.showMenu();
                            break;
                        case 2:
                        ourMenu.getMenu(vMenu);
                        //check if user exist, then delete old in4 to store new in4
                        for(it2 = manageUser.begin(); it2 != manageUser.end(); ++it2){
                                if(it2->getUserName() == person.getUserName()){
                                    checkExistUser = true;
                                    break;
                                }
                            }
                            if(checkExistUser){
                                it2->setOrderFood(ourMenu);
                            }else{
                                person.setOrderFood(ourMenu);
                                person.getUserName();
                                manageUser.push_back(person);
                            }
                            break;
                        case 3:

                            cout << "order of " << person.getUserName() << endl;
                            cout << "************************\n";    
                            for(it2 = manageUser.begin(); it2 != manageUser.end(); ++it2){
                                if(it2->getUserName() == person.getUserName()){
                                    it2->showOrderedFood();
                                    break;
                                }
                            }
                            break;
                        case 4:
                            cout << "Clearing your order...\n";
                            for(it2 = manageUser.begin(); it2 != manageUser.end(); ++it2){
                                if(it2->getUserName() == person.getUserName()){
                                    it2->clearOrderFood();
                                    break;
                                }
                            }
                            break;
                        case 0:
                            person.clearOrderFood();
                            cout << "Exiting order program ...\n";
                            return;
                        default:
                            return;
                    }       
    }while(optionOrder != 0);
    return;
}

int main(){
    std::ifstream outf{ "Sample1.txt"}; 
    
    int optionAccount;
    int count = 0;
    bool checkSignIn = false;

    inforSignUp personSignUp;
    inforSignIn personSignIn;
    map<string, string> myInfoUser = {};
    
    vector<User> manageUser;
    string userName;
    string string_temp;

    User person;
    Menu ourMenu;
    vector<string> vMenu;
    do{
        cout <<"***************************************\n";
       
        cout << "1. Sign up\n";
        cout << "2. Sign in\n";
        cout << "0. Exit program!\n";
        cout << "Choose your option: \n";

        //Need to check integer here
        do{
            cout << "please enter valid value: \n";
            getline(cin, string_temp);
            bool check = checkUnsignInteger(string_temp);
            if(check){
                int num_temp = stoi(string_temp);
                if(num_temp >= 0 && num_temp <= 2){
                    break;
                }
            }
        }while(1);
        optionAccount = stoi(string_temp);

        // cin >> optionAccount;
        // cin.ignore();
        switch(optionAccount){
            case 1:
                    personSignUp.input();
                
                    if(!personSignUp.checkExist(personSignUp.getNameAccount(), myInfoUser)){
                        cout << "Successfully sign up!\n";
                        myInfoUser.insert({personSignUp.getNameAccount(), personSignUp.getPassWord()});
                        personSignUp.writeToFile();
                    } 
                
                break;
            case 2:
                    personSignIn.input();
                    if(personSignIn.checkMatchWithFile(personSignIn.getNameAccount(), personSignIn.getPassWord(), myInfoUser)){
                        checkSignIn = true;
                        cout << "Successfully sign in!\n";
                    }else{
                        cout << "Account don't exist!\nPlease sign up!\n";
                        checkSignIn = false;
                    }
                if(checkSignIn){
                    map<string, string>::iterator it;
                    it = myInfoUser.find(personSignIn.getNameAccount());
                    cout << "user name is : " << it->first << endl;
                    cout << "***************************\n";
                    userName = it->first;
                    person.setNameAccount(userName);

                    orderFood(ourMenu, person, vMenu, manageUser);
                    cout << "Confirm your order below:\n";
                    vector<User>::iterator it2;
                    for(it2 = manageUser.begin(); it2 != manageUser.end(); ++it2){
                        if(it2->getUserName() == person.getUserName()){
                            it2->showOrderedFood();
                            break;
                        }
                    }
                }
                break;     
            case 0:
                return 0;
        }
        }while(optionAccount != 0);

}