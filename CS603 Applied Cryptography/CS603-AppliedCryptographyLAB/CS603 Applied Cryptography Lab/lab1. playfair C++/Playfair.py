key = input("Enter the key with no duplicates: ")
plain = input("Enter the plaintext: ")

def PlayfairMatrix(key):
    alphabets = 'abcdefghijklmnopqrstuvwxyz0123456789'
    matrix = []

    for char in key:
        matrix.append(char)

    for char in alphabets:
        if char not in key:
            matrix.append(char)
    
    return [matrix[i:i + 6] for i in range(0, 36, 6)]

Display = PlayfairMatrix(key)
for row in Display:
    print(' '.join(map(str, row)))

def encrypt(matrix, plain):
    plain = plain.replace(' ', '')
    cipher = ''
    
    if len(plain) % 2 != 0:
      plain += 'x'
    
    def enumerated(matrix, char):
      for i, row in enumerate(matrix):
          if char in row:
              return i, row.index(char)
      return None

    i = 0
    while i < len(plain):
        a = plain[i]
        b = plain[i + 1]
        
        a_row, a_column = enumerated(matrix, a)
        b_row, b_column = enumerated(matrix, b)

        if a_row == b_row:
            cipher += matrix[a_row][(a_column + 1) % 6]
            cipher += matrix[b_row][(b_column + 1) % 6]
        elif a_column == b_column:
            cipher += matrix[(a_row + 1) % 6][a_column]
            cipher += matrix[(b_row + 1) % 6][b_column]
        else:
            cipher += matrix[a_row][b_column]
            cipher += matrix[b_row][a_column]
        
        i += 2
    
    return cipher

ciphertext = encrypt(Display, plain)
print('Ciphertext: ')
print(ciphertext)
