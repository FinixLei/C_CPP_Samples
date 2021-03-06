#include <cstring>
#include <iostream>
using namespace std;


class String {
public:
    String(const char *str=NULL);
    String(const String& other);
    String(String&& other);
    String& operator= (const String& other);
    String& operator= (String&& other);
    virtual ~String();
    
    friend String operator+ (const String& a, const String& b);
    friend ostream& operator<< (ostream& out, const String& a);
    
private:
    int _len;
    char *_str; 
    
};

String::String(const char *str)
{
    cout << "Enter Constructor\n";
    
    // Must check NULL or nullptr, 
    // as "int len = strlen(NULL);" will trigger segment fault. 
    if (str == NULL) {  
        _len = 1; 
        _str = new char [1];
        _str[0] = '\0';
    }
    else {
        _len = strlen(str) + 1;
        _str = new char [_len];
        strcpy(_str, const_cast<char *>(str));
    }
}

String::String(const String& other)
{
    cout << "Enter normal copy constructor\n";
    _len = other._len;
    _str = new char [_len];
    strcpy(_str, other._str);
}

String::String(String&& other)
{
    cout << "Enter move copy constructor\n";
    _len = other._len;
    _str = other._str;
    other._str = new char [1];
    other._len = 1;
    other._str[0] = '\0';
}

// way-1 
// String& String::operator= (const String& other)
// {
//     cout << "Enter operator = \n";
//     
//     if (this == &other) return *this;
//     
//     _len = 0;
//     delete [] _str;
//     
//     _len = other._len;
//     _str = new char [_len];
//     strcpy(_str, other._str);
//     return *this;
// }

// way-2 
String& String::operator= (const String& other)
{
    cout << "Enter operator = \n";
    
    if (this != &other) {
        // Exception Safe, will not affect original instance
        String tmp(other);  // one more copy constructor than way-1
        
        swap(_len, tmp._len);
        swap(_str, tmp._str);
    }
    
    return *this;
}

String& String::operator= (String&& other)
{
    cout << "Enter operator = (&&) \n";
    
    if (this == &other) return *this;
    
    delete [] _str; 
    
    _len = other._len;
    _str = other._str;
    
    other._len = 1;
    other._str = new char [1];
    other._str[0] = '\0';
    return *this;
}

String::~String()
{
    delete [] _str;
    _len = 0;
}

String operator+ (const String& a, const String& b)
{
    String c;
    c._len = a._len + b._len - 1;
    c._str = new char [c._len];
    strcpy(c._str, a._str);
    strcpy(&c._str[a._len-1], b._str);
    return c;
}

ostream& operator<< (ostream& out, const String& a)
{
    out << a._str;
    return out;
}
