#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
#include <unordered_set>
using namespace std;


void handleAlphabetCase(string& text){
    string txt; // empty text
    // changing upper case to lower case
    for (char& ch : text){

        if(isalnum(ch)){
            ch = toupper(ch);
            txt += ch;
        }
    }
    text = txt;
}

void handleDiGraphs(string& text){
    
    //injecting 'X' in digraphs with common letters
    for(size_t i = 0; i< text.length(); i++ ){
        if(i+1 < text.length() & text[i] == text[i+1])
            text.insert(i+1, 1, 'X');
    }
}

void cleanPlainText(string& text){

    handleAlphabetCase(text);

    handleDiGraphs(text);

    // checking text even length
    if(text.length() % 2 != 0) text.push_back('X');
    
}

void printMatrix(char matrix[][6]){
    for (int i = 0; i< 6; i++){
        for(int j = 0; j<6; j++){
            cout << matrix[i][j] << '\t';
        }
    cout << '\n';
    }
}

void prepareKeyMatrix(string& key, char matrix[][6]){
    bool used[36] = {false};
    int row = 0,col = 0;
    
    handleAlphabetCase(key);

    // fillng matrix with key
    for (char ch: key){
        int idx = isdigit(ch) ? ch - '0'+26 : ch - 'A';
        if(!used[idx]){
            used[idx] = true;
            matrix[row][col++] = ch;
            if(col == 6) {
                col = 0;
                row++;
            }
        }
    }   

    // filling matrix with unused chars of alphabets
    for (char ch = 'A'; ch <= 'Z'; ch++){
        int idx = ch - 'A';
        if(!used[idx]){
            matrix[row][col++] = ch;
            if (col == 6){
                col = 0;
                row++;
            }
        }
    }

    // filling matrix with used digits
    for(char ch = '0'; ch <= '9'; ch++){
        int idx = ch - '0'+26;
        if(!used[idx]){
            matrix[row][col++] = ch;
            if (col == 6){
                col = 0;
                row++;
            }
        }
    }

}

void lookupMatrix(const char matrix[][6], char ch, int& row, int& col){
    for (int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(matrix[i][j] == ch){
                row = i;
                col = j;

            }
        }
    }
}

string Encrypt(const string& text, const char matrix[][6]){

    // This function uses Playfair 6x6 encryption
    string encryptedText;
    size_t len = text.length();
    
    for (size_t i = 0; i< len; i+= 2){
        int row1, row2, col1, col2;

        lookupMatrix(matrix, text[i], row1, col1);
        lookupMatrix(matrix, text[i+1], row2, col2);

        if(row1 == row2){
            //same row
            encryptedText += matrix[row1][(col1 + 1) % 6];
            encryptedText += matrix[row2][(col2 + 1) % 6];
        
        } else if(col1 == col2){
            //same col
            encryptedText += matrix[(row1+1) % 6][col1];
            encryptedText += matrix[(row2+1) % 6][col2];
        
        }else{
            // Non-same row && Non-same col
            encryptedText += matrix[row1][col2];
            encryptedText += matrix[row2][col1];

        }   
    }
    return encryptedText;

}

string removeFillerX(string& text){
    string finalText;
    for (size_t i = 0; i < text.length(); i++){
        if( i < text.length() && text[i] == text[i+2] && text[i+1] == 'X'){
        finalText += text[i];
        i++; 
    } else{
        finalText += text[i];
        }
    }
    return finalText;
}

string Decrypt(const string& text, const char matrix[][6]){

    // this function uses Playfair 6x6 Decryption
    string decryptText;
    size_t len = text.length();

    for (size_t i = 0; i< len; i+= 2){
        int row1, row2, col1, col2;

        lookupMatrix(matrix, text[i], row1, col1);
        lookupMatrix(matrix, text[i+1], row2, col2);

        if(row1 == row2){
            //same row
            decryptText += matrix[row1][(col1 + 6 -1)  % 6];
            decryptText += matrix[row1][(col2 + 6 -1) % 6];
        
        } else if(col1 == col2){
            //same col
            decryptText += matrix[(row1 + 6 -1) % 6][col1];
            decryptText += matrix[(row2 + 6 -1) % 6][col2];
        
        }else{
            // Non-same row && Non-same col
            decryptText += matrix[row1][col2];
            decryptText += matrix[row2][col1];

        }   
    }
    
    return decryptText;
}

bool isValid(const string& txt){
    unordered_set<char> seenChars;

    for (char ch: txt){
        if (!isalnum(ch)){
            return false;
        }

        if (seenChars.find(ch) != seenChars.end()){
            return false;
        }

        seenChars.insert(ch);
    }   
    return true;


}

void printPair(const string& txt){
    for (size_t i = 0; i < txt.length(); i+= 2){
        cout << txt[i]<<txt[i+1]<<"\t";
    }
}

int main(){

    string key;
    string text;
    cout << "Enter Key: " <<endl;
    getline(cin, key);

    if(!isValid(key)){
        cout<< "--------------------------------------------"<< endl;
        cout << "\nThe key you have entered an invalid. \nRe-run the program!";
        cout << "\n" <<"\n" << "--------------------------------------------"<<"\n";
        return 0;
    }

    cout << "Enter text:" <<endl;
    getline(cin, text);

    char matrix[6][6];
    string P = text;
    string E;
    string D;

    cleanPlainText(P);
    prepareKeyMatrix(key,matrix);
    cout<<"\n The Key Matrix used for encryption"<< endl;
    cout << "__________________________________________" << endl;
    printMatrix(matrix);
    cout<<"__________________________________________"<< endl;


    cout<< "Original Message M : " << "\t"<< text << endl;

    cout << "\nPlain Text P :   " ;
    cout<<"\t" ;
    printPair(P);

    E = Encrypt(P, matrix);
    cout << "\nEncrypted Text E :   " ;
    cout<<"\t" ;
    printPair(E);

    D = Decrypt(E, matrix);
    cout << "\nDecrypted Text D :   ";
    cout<<"\t" ;
    printPair(D);

    cout<< "\nDecrypted Message M_ : " << "\t"<< removeFillerX(D) << endl;




    
}