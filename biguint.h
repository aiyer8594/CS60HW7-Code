#ifndef BIGUINT_H
#define BIGUINT_H
#include <iostream>
#include <string>
#include <QString>

class biguint
{
public:
    //TYPES AND CONSTANTS
    typedef std::size_t size_type;
// default constructor
// pre: none
// post: creates a biguint whose value is n and whose capacity is at least m
// (default n = 0, m = 1)
// NOTE: a decimal integer n requires log(n+1.0)/log(10) (rounded UP) digits
biguint(unsigned int n = 0, size_type m = 1);

biguint(const std::string & s);

// destructor
~biguint();

// CONSTRUCTORS

// pre: none
// post: creates a biguint with given unsigned int value
//       (default value = 0)

//biguint(unsigned int = 0);
// pre: s.size() <= CAPACITY && s consists of decimal digits only
// post: creates a biguint whose digits are given in a string s
//       rightmost digit of s corresponds to the least significant
//       digit
biguint (const char s[]);

biguint (const biguint &);

// CONSTANT FUNCTIONS
// pre: pos < CAPACITY
// post: returns the (pos+1)^st digit from the right of this biguint
size_type operator [](size_type pos) const;

// pre: none
// post: return 0 if n == this biguint
//             -1 if n > this biguint
//              1 if n < this biguint
int compare(const biguint & n) const;

// pre: none
// post: b has been added to this biguint
//       overflow digit will be thrown away, if any
void operator +=(const biguint &b);

// pre: none
// post: if b > this biguint, then this biguint is reset to 0
//       else b is subtracted from this biguint
void operator -=(const biguint & b);

// pre: d <= 9;
// post: this biguint has been multiplied by d
void operator *= (size_type d);

void operator *= (const biguint & b);

// pre: none
// post: digits of this biguint has been left shifted by 1 positio
//       the former most significant digit is discarded
//       the new least significiant digit is 0
void ls();

QString toQString() const;

void reserve(size_type new_capacity);

// assigment operator
void operator =(const biguint & b);

// pre: none
// post: returns the number of digits (no leading 0’s) in this biguint
size_type digits() const;

// division and remainder operators
// pre: b != 0
// post: returns the quotient/remainder of this biguint divided by divisor
// NOTE: also implement the corresponding nonmember operators / and %
void operator /= (const biguint & divisor);
void operator %= (const biguint & divisor);

// pre-increment/decrement operators
// pre: none
// post: this biguint has been incremented/decremented by 1
// return value is the NEW value
biguint operator ++();
biguint operator --();

// post-increment/decrement operators
// pre: none
// post: this biguint has beeen incremented/decremented by 1
// return value is the ORIGINAL value
// there is actually no input paramenter
biguint operator ++(int);

// int is used to distinguish between
// post-increment from pre-increment (which
// has no input parameters)
biguint operator --(int);


private:
size_type *data;
size_type capacity;
// data[0..capacity-1 is a dynamic array
// data[i] corresponds to the coefficient of 10^i for 0 <= i < capacity
};

std::ostream & operator << (std::ostream &, const biguint & b);
std::ostream & operator >> (std::ostream &, biguint &);

bool operator <(const biguint &, const biguint &);

bool operator <=(const biguint &, const biguint &);

bool operator ==(const biguint &, const biguint &);
bool operator != (const biguint &, const biguint &);
bool operator >= (const biguint &, const biguint &);
bool operator >(const biguint &, const biguint &);
biguint operator + (const biguint &a, const biguint &b);
biguint operator - (const biguint & a, const biguint & b);
biguint operator *(const biguint & b, biguint::size_type d);
biguint operator *(const biguint & a, const biguint &b);
biguint operator /(const biguint &a, const biguint &b);
biguint operator % (const biguint &a, const biguint &b);
#endif // BIGUINT_H
