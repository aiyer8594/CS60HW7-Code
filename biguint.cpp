#include "biguint.h"
#include <cmath>
#include <cassert>
#include <iostream>

//CONSTRUCTORS
biguint::biguint(unsigned int n, size_type m)
{
    capacity = ceil(log(n+1.0)/log(10));
    if(m > capacity){
        capacity = m;
    }
    data = new size_type[capacity];
    std::fill(data, data + capacity, 0);
    size_type i(0);
    while (n > 0){
        data[i] = n%10;
        n/=10;
        ++i;
    }
}

biguint::biguint(const std::string & s)
{
    capacity = s.size();
    data = new size_type[capacity];
    std::fill(data, data + capacity, 0);
    for(size_type i = 0; i<capacity; ++i){
        assert(isdigit(s[i]));
        data[capacity-1-i] = s[i] - '0';
    }
}

biguint::biguint(const biguint &b){
    capacity=b.capacity;
    data=new size_type[capacity];
    std::copy(b.data, b.data + capacity, data);
}

biguint::size_type biguint::operator[](size_type pos) const
{
    assert(pos < capacity);
    return data[pos];
}

biguint::biguint(const char s[]): biguint(std::string(s))
{
}
//DESTRUCTOR
// destructor
biguint::~biguint(){
    delete[] data;
}


int biguint::compare(const biguint &n) const
{
    if (n.digits()>digits()){
        return -1;
    }
    if(n.digits()<digits()){
        return 1;
    }
    for (int i = digits() -1; i >= 0; --i)
    {
        if (data[i] < n.data[i])
            return -1;
        if (data[i] > n.data[i])
            return 1;
    }
    return 0;
}
void biguint::ls()
{
    if(digits()==capacity)
    {
        reserve(capacity+1);
    }
    for (int i = capacity -1; i > 0; --i)
        data[i] = data[i-1];

    data[0] = 0;
}

QString biguint::toQString() const{
     QString dataString = "";
     int i(digits()-1);
     if(i == -1){
         return "0";
     }
     while(i >= 0){
            dataString += data[i--] + '0';
     }
     return dataString;
}

// pre: none
// post: returns the number of digits (no leading 0’s) in this biguint
biguint::size_type biguint::digits() const{
    int i = capacity - 1;
    while (i >= 0 && data[i] == 0){
        i--;
    }
    return i+1;
}
void biguint::reserve(size_type new_capacity)
{
    if (new_capacity < digits() || new_capacity == capacity)
        return;

    size_type *new_data = new size_type[new_capacity];
    std::fill(new_data, new_data + new_capacity, 0);
    std::copy(data, data+digits(), new_data);

    delete [] data;
    data = new_data;
    capacity = new_capacity;
    data = new size_type [capacity];
    std::fill(data, data+capacity, 0);
    std::copy(new_data, new_data +capacity, data);
    delete[] new_data;
}
//OPERATOR OVERLOAD (+,-,/,*)
biguint operator + (const biguint &a, const biguint &b)
{
    biguint ans(a);
    ans += b;
    return ans;
}

biguint operator - (const biguint & a, const biguint & b)
{
    biguint ans(a);
    ans -= b;
    return ans;
}

biguint operator *(const biguint & b, biguint::size_type d)
{
    biguint ans(b);
    ans *= d;
    return ans;

}

biguint operator *(const biguint & a, const biguint &b)
{
    biguint ans(a);
    ans *= b;
    return ans;
}
//OPERATOR OVERLOADING =, +=,-=,*=,/=, %=
// assigment operator
void biguint::operator =(const biguint & b){
    if(this==&b){
        return;
    }
    if(b.digits()>capacity){
        reserve(b.digits());
    }
    std::fill(data,data + digits(),0);
    std::copy(b.data, b.data+b.digits(), data);
}
void biguint::operator +=(const biguint & b)
{
    if(b.digits()>capacity){
        reserve(b.digits());
    }
    size_type carry(0), i;

    for (i = 0; i < b.digits(); ++i)
    {
        size_type sum = carry + data[i] + b.data[i];
        data[i] = sum % 10;
        carry = sum / 10;
    }
    if(carry>0){
        while(data[i] == 9 && i < digits()){
            data[i] = 0;
            i++;
        }
        if(i == capacity){
            reserve(capacity+1);
        }
        data[i] += carry;
    }
}
void biguint::operator -=(const biguint & b)
{
    if (compare(b) <= 0)
    {
        std::fill(data, data+capacity, 0);
        return;
    }
    size_type borrow(0), i;
    for (i = 0; i < b.digits(); ++i)
    {
        size_type t = b.data[i] + borrow;
        if (data[i] >= t)
        {
            data[i] -= t;
            borrow = 0;
        }
        else
        {
            data[i] += 10;
            data[i] -= t;
            borrow = 1;
        }
    }if(borrow > 0){
         while(data[i]==0){
             data[i] +=9;
             i++;
         }
         data[i] -= borrow;
    //borrow = 0;
    }
}

void biguint::operator *=(size_type d)
{
    //assert (d<= 9);

    if (d==0){
        std::fill(data, data+digits(), 0);
    }else{
        size_type carry(0), product(0), i;
        for (i = 0; i < digits(); ++i){
            product = carry + data[i] * d;
            data[i] = product % 10;
            carry = product/10;
        }
        if(carry>0)
        {
            if(i == capacity){
                reserve(capacity +1);
            }
            data[i] += carry;
        }
    }
}

void biguint::operator *=(const biguint &b)
{
   biguint answer(0u);
   int mostSig = digits()-1;
   while(mostSig>=0){
       answer.ls();
       answer=answer+b*data[mostSig];
       mostSig--;
   }
   /*delete[] data;
   capacity = answer.capacity;
   data=new size_type[capacity];*/
   reserve(answer.digits());
   std::copy(answer.data, answer.data + answer.capacity, data);
}

void biguint::operator /= (const biguint  & divisor){
    assert(divisor != biguint(0u, 1));
    biguint remainder(0, divisor.digits());
    biguint quotient(0, digits()); // too many, but can shrink later
    for (int i = digits()-1; i >= 0; --i){
       remainder.ls();
       remainder.data[0] = data[i];
       size_type count(0);
       while (remainder >= divisor){
           ++count;
           remainder -= divisor;
       }
       quotient.data[i] = count;
    }
    // at this point quotient = a/b and remainder = a % b
    // shrink *this and copy quotient/remainder back to *this
    std::fill(data, data+digits(), 0);
    std::copy(quotient.data, quotient.data+quotient.digits(), data);
}

void biguint::operator %= (const biguint & divisor){
    assert(divisor!=(0u));
    biguint remainder(0, divisor.digits());
    biguint quotient(0, digits()); // too many, but can shrink later
    for (int i = digits()-1; i >= 0; --i)
    {
        remainder.ls();
        remainder.data[0] = data[i];
        size_type count(0);
        while (remainder >= divisor)
        {
            ++count;
            remainder -= divisor;
        }
        quotient.data[i] = count;
    }
    // at this point quotient = a/b and remainder = a % b
    // shrink *this and copy quotient/remainder back to *this
    std::fill(data, data+digits(), 0);
    std::copy(remainder.data, remainder.data+remainder.digits(),data);
            //andrew
}

//OPERATOR OVERLOAD ++,--,
biguint biguint::operator ++(){
    *this += biguint(1);
    return *this;
}

biguint biguint::operator --(){
    *this -= biguint(1);
    return *this;
}

biguint biguint::operator ++(int){
    biguint ans(*this);
    *this += 1;
    return *this;
}

biguint biguint::operator --(int){
    biguint ans(*this);
    *this -= 1;
    return ans;
}

//COMPARE OVERLOAD
bool operator <(const biguint &a, const biguint &b){
    return a.compare(b) == 1;
}
bool operator <=(const biguint &a, const biguint &b){
    return a.compare(b) <= 0;
}
bool operator ==(const biguint & a, const biguint & b){
    return a.compare(b) == 0;
}
bool operator != (const biguint &a, const biguint &b){
    return a.compare(b) != 0;
}
bool operator >= (const biguint &a, const biguint &b){
    return a.compare(b) >=0;
}
bool operator > (const biguint &a, const biguint &b){
    return a.compare(b) == 1;
}

//INPUT AND OUTPUT OPERATORS
std::istream & operator >>(std::istream & is, biguint & b)
{
    std::string s;
    is >> s;
    b = biguint(s);
    return is;

}
std::ostream & operator << (std::ostream &os, const biguint & b)
{
    int i(b.digits()-1);
    if(i == -1){
        os << 0;
    }else{
        while (i >= 0)
        {
            os << b[i--];
        }
    }
   return os;
}
