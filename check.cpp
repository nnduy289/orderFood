#include "check.h"

bool checkValidInteger(string &str){
    for(int i = 0; i < str.size(); i++){
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}

bool checkUnsignInteger(string& str){
    if(checkValidInteger(str)){
        if(stoi(str) >= 0){
            return true;
        }else return false;
    }
    return false;
}

bool checkValidAccountIn4(string &str){
    bool check = true;
    if(str.size() >= 8 && str.size() <= 30){
        for(int i = 0; i < str.size(); i++){
            if(str[i] == ' '){
                 cout << "Don't allow white space in Account name or password\n";
               return false;
            }
        }
         return true;
    }
            cout << "At least 8 character or max 30 character!\n";
            return false;
}

