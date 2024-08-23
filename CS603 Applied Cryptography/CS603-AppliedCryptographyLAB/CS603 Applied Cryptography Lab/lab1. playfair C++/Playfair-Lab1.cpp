#include <iostream>
#include <string>
#include <cctype>  // For toupper, isalpha

using namespace std;

const int MATRIX_SIZE = 6; // 6x6 matrix

void prepareKey(const string& key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    bool used[36] = {false}; // Track used characters (26 letters + 10 digits)
    int row = 0, col = 0;

    for (char ch : key) {
        ch = toupper(ch);
        if (isalnum(ch)) {
            if (ch == 'J') ch = 'I'; // Replace 'J' with 'I'
            int index = isdigit(ch) ? ch - '0' + 26 : ch - 'A';
            if (!used[index]) {
                used[index] = true;
                matrix[row][col++] = ch;
                if (col == MATRIX_SIZE) {
                    col = 0;
                    ++row;
                }
            }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (ch == 'J') continue; // Skip 'J' (already replaced by 'I')
        int index = ch - 'A';
        if (!used[index]) {
            matrix[row][col++] = ch;
            if (col == MATRIX_SIZE) {
                col = 0;
                ++row;
            }
        }
    }
    for (char ch = '0'; ch <= '9'; ++ch) {
        int index = ch - '0' + 26;
        if (!used[index]) {
            matrix[row][col++] = ch;
            if (col == MATRIX_SIZE) {
                col = 0;
                ++row;
            }
        }
    }
}

// Utility function to prepare the plaintext
void preprocessText(string& text) {
    // Convert to uppercase and replace 'J' with 'I'
    for (char& ch : text) {
        ch = toupper(ch);
        if (ch == 'J') ch = 'I';
    }

    // Handle digraphs
    for (size_t i = 0; i < text.length(); ++i) {
        if (i + 1 < text.length() && text[i] == text[i + 1]) {
            text.insert(i + 1, 1, 'X');
        }
    }

    // Ensure even length
    if (text.length() % 2 != 0) {
        text.push_back('X');
    }
}

// Utility function to find the position of a character in the matrix
void findPosition(const char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int& row, int& col) {
    for (int r = 0; r < MATRIX_SIZE; ++r) {
        for (int c = 0; c < MATRIX_SIZE; ++c) {
            if (matrix[r][c] == ch) {
                row = r;
                col = c;
                return;
            }
        }
    }
}

// Function to encrypt the text using Playfair cipher
string encryptPlayfair(const string& text, const char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    string encryptedText;
    size_t len = text.length();

    for (size_t i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(matrix, text[i], row1, col1);
        findPosition(matrix, text[i + 1], row2, col2);

        if (row1 == row2) {
            // Same row
            encryptedText += matrix[row1][(col1 + 1) % MATRIX_SIZE];
            encryptedText += matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            // Same column
            encryptedText += matrix[(row1 + 1) % MATRIX_SIZE][col1];
            encryptedText += matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else {
            // Rectangle
            encryptedText += matrix[row1][col2];
            encryptedText += matrix[row2][col1];
        }
    }

    return encryptedText;
}

// Function to decrypt the text using Playfair cipher
string decryptPlayfair(const string& text, const char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    string decryptedText;
    size_t len = text.length();

    for (size_t i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(matrix, text[i], row1, col1);
        findPosition(matrix, text[i + 1], row2, col2);

        if (row1 == row2) {
            // Same row
            decryptedText += matrix[row1][(col1 + MATRIX_SIZE - 1) % MATRIX_SIZE];
            decryptedText += matrix[row2][(col2 + MATRIX_SIZE - 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            // Same column
            decryptedText += matrix[(row1 + MATRIX_SIZE - 1) % MATRIX_SIZE][col1];
            decryptedText += matrix[(row2 + MATRIX_SIZE - 1) % MATRIX_SIZE][col2];
        } else {
            // Rectangle
            decryptedText += matrix[row1][col2];
            decryptedText += matrix[row2][col1];
        }
    }

    return decryptedText;
}

// Function to get user input and handle encryption
void handleEncryption() {
    string key;
    string text;

    // Get key and plaintext from user
    cout << "Enter key: ";
    getline(cin, key);
    cout << "Enter plaintext: ";
    getline(cin, text);

    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    string preparedText = text;
    string encryptedText;
    string decryptedText;

    // Prepare the Playfair matrix
    prepareKey(key, matrix);

    // Prepare the plaintext
    preprocessText(preparedText);

    // Encrypt the plaintext
    encryptedText = encryptPlayfair(preparedText, matrix);
    cout << "Encrypted text: " << encryptedText << endl;

    // Decrypt the ciphertext
    decryptedText = decryptPlayfair(encryptedText, matrix);
    cout << "Decrypted text: " << decryptedText << endl;
}

int main() {
    handleEncryption();
    return 0;
}