#include<iostream>
#include<string>
#include<cstring>
using namespace std;


// function to remove anything other than alphabets and digits.
void cleanPlainText(char* plainTxt, int txtLen){
    
    int idx = 0;
    for(int i=0; i < txtLen; i++){

        char chr = plainTxt[i];
        bool validChars = ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z' ) ||(chr >= '0' && chr <= '9'));
        if(validChars){
            plainTxt[idx++] = plainTxt[i];
        }
    }

    plainTxt[idx] = '\0';
}


// 







int main(){

    
}