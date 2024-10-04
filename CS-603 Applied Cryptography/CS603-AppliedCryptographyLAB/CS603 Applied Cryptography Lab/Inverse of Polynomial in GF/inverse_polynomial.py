def binary_to_int(binary_str):
    return int(binary_str, 2)

def int_to_binary(integer, length=8):
    return bin(integer)[2:].zfill(length)

def poly_add_sub(a, b):
    # Addition and subtraction are the same in GF(2)
    return a ^ b

def poly_mul(a, b, mod_polynomial):
    result = 0
    while b:
        if b & 1:
            result ^= a  # Add a to result if the lowest bit of b is set
        a <<= 1  # Multiply a by x (shift left)
        if a & 0x100:  # If degree of a exceeds 7 (i.e., if x^8 is present)
            a ^= mod_polynomial  # Reduce modulo the irreducible polynomial
        b >>= 1  # Move to the next bit in b
    return result

def poly_divmod(a, b):
    degree_a = a.bit_length() - 1
    degree_b = b.bit_length() - 1
    quotient = 0

    while degree_a >= degree_b:
        shift = degree_a - degree_b
        quotient ^= 1 << shift
        a ^= b << shift
        degree_a = a.bit_length() - 1

    return quotient, a  # Returns quotient and remainder

def extended_euclidean(a, b, mod_polynomial):
    r0, r1 = a, b
    t0, t1 = 0, 1

    while r1 != 0:
        quotient, remainder = poly_divmod(r0, r1)
        r0, r1 = r1, remainder
        t0, t1 = t1, poly_add_sub(t0, poly_mul(quotient, t1, mod_polynomial))

    if r0 != 1:
        raise ValueError("No multiplicative inverse exists.")
    
    return t0

def binary_to_polynomial(binary_str):
    terms = []
    for i, bit in enumerate(reversed(binary_str)):
        if bit == '1':
            if i == 0:
                terms.append("1")
            elif i == 1:
                terms.append("x")
            else:
                terms.append(f"x^{i}")
    return " + ".join(terms) if terms else "0"

def find_inverse(polynomial, mod_polynomial='100011011'):
    mod_polynomial_int = binary_to_int(mod_polynomial)
    poly_int = binary_to_int(polynomial)
    inverse_int = extended_euclidean(mod_polynomial_int, poly_int, mod_polynomial_int)
    return binary_to_polynomial(int_to_binary(inverse_int))

# Example usage:
modulus = '100011011'  # x^8 + x^4 + x^3 + x + 1

# Test Case 1: Find the inverse of x^4 (binary: 00010000)
polynomial = '00010000'
inverse = find_inverse(polynomial, modulus)
print(f"Inverse of {binary_to_polynomial(polynomial)} is {inverse}")

