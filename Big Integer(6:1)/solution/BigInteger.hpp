#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

class BigInteger {
private:
    const int BASE = 1e9; // база внутренней СС
    const int DIGIT_LEN = log10(BASE); // длина разряда в 10 СС
    std::vector<int> digits;
public:
    BigInteger();
    BigInteger(std::string&);
    BigInteger(const BigInteger&);
    BigInteger& operator= (BigInteger&&);
    BigInteger& operator+= (const BigInteger&);
    BigInteger& operator-= (const BigInteger&);
    BigInteger& operator*= (const BigInteger&);
    BigInteger& operator*= (const int);
    BigInteger& operator/= (BigInteger&);
    BigInteger& operator/= (const int);
    BigInteger& operator^= (BigInteger&);
    BigInteger& operator^= (int);
    friend BigInteger operator+ (const BigInteger, const BigInteger&);
    friend BigInteger operator- (const BigInteger, const BigInteger&);
    friend BigInteger operator* (const BigInteger, const BigInteger&);
    friend BigInteger operator* (const BigInteger, const int);
    friend BigInteger operator* (const int, const BigInteger);
    friend BigInteger operator/ (const BigInteger, const BigInteger&);
    friend BigInteger operator/ (const BigInteger, const int);
    friend BigInteger operator^ (const BigInteger, const BigInteger&);
    friend BigInteger operator^ (const BigInteger, const int);
    friend std::ostream& operator<< (std::ostream&, const BigInteger&);
    friend std::istream& operator>> (std::istream&, BigInteger&);
    friend bool operator< (const BigInteger&, const BigInteger&);
    friend bool operator> (const BigInteger&, const BigInteger&);
    friend bool operator== (const BigInteger&, const BigInteger&);
};
