from operator import *

global list_quotient,n

n= int(input("Enter the bit:"))
list_quotient=[]

def multiply_two_binary(binary1,binary2):
    return bin(binary_to_decimal(binary1)*binary_to_decimal(binary2)).replace('0b',"").zfill(n)

def power_to_binary(power):
    # string of binary of bit n
    binary ='0'.zfill(n)
    power.sort()
    # replace the 0 with 1 at the position of power from last
    for i in power:
        binary=binary[:n-1-i]+'1'+binary[n-i:]
    return binary

def binary_to_decimal(binary):
    return int(binary,2)

def decimal_to_binary(decimal):
    return bin(decimal).replace('0b',"").zfill(n)

def division_sub(num1, num2):
    return num1 ^ num2 

def remainder_gen(binary_divident,binary_divisor):
    pos_divident=0
    pos_divisor=0
    if(binary_to_decimal(binary_divisor)==1):
        for i in range(0,len(binary_divident)):
            if(binary_divident[i]=='1'):
                list_quotient.append(n-1-i)
        return decimal_to_binary(0)
    for i in range(0,len(binary_divident)):
        if(binary_divident[i]=='1'):
            pos_divident=i
            break

    for j in range(0,len(binary_divisor)):
        if(binary_divisor[j]=='1'):
            pos_divisor=j
            break
    power_to_multiplied=pos_divisor - pos_divident
    list_quotient.append(power_to_multiplied)
    intermediate=decimal_to_binary(binary_to_decimal(binary_divisor)<<power_to_multiplied)
    remainder = decimal_to_binary(division_sub(binary_to_decimal(binary_divident),binary_to_decimal(intermediate)))
    pos_remainder=0
    for j in range(0,len(remainder)):
        if(remainder[j]=='1'):
            pos_remainder=j
            break
    
    if(pos_remainder>pos_divisor):
        return remainder
    else:
        return remainder_gen(remainder,binary_divisor)




def Extended_Euclidean(modulo,number):
    t1='0'.zfill(n)
    t2='1'.zfill(n)
    r1=modulo
    r2=number
    while(r2>decimal_to_binary(0)):
        r= remainder_gen(r1,r2)
        q= power_to_binary(list_quotient)
        list_quotient.clear()
        r1=r2
        r2=r
        # t=t1-q*t2
        t=decimal_to_binary(division_sub(binary_to_decimal(t1),binary_to_decimal(multiply_two_binary(q,t2))))
        t1=t2
        t2=t
        print("The GCD is:",r1)
        print("The coefficients are:",t1,t2)
        print("The quotient is:",q)
        print("\n")
    return t1

a= str(input("Enter the polynomial(binary):"))
b= str(input("Enter the polynomial(binary) whose inverse is to be calculated:"))
irreducible_poly='100011011'
# if inverse is big modulus with irreducible polynomial
if(binary_to_decimal(b)>binary_to_decimal(irreducible_poly)):
    b=remainder_gen(b,irreducible_poly)
    print(f'The multiplicative inverse is {Extended_Euclidean(a,b)}')
else:
    print(f'The multiplicative inverse is {Extended_Euclidean(a,b)}')
# print(f'The multiplicative inverse is {Extended_Euclidean('100011011','000100000')}')

