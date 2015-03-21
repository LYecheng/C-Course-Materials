//
//  btree.cpp
//  HW4.4
//
//  Created by Mingyang Yu on 2/1/15.
//  Copyright (c) 2015 Mingyang Yu. All rights reserved.
//

#include "btree.h"
#include <stddef.h>
#include <iostream>
#include <ostream>
using namespace std;

template <typename T> struct RemoveReference {
    typedef T type;
};

template <typename T> struct RemoveReference<T&> {
    typedef T type;
};

template <typename T> struct RemoveReference<T&&> {
    typedef T type;
};

template <typename T> typename RemoveReference<T>::type&& Move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}

class remote_integer {
public:
    remote_integer() {
        cout << "Default constructor." << endl;
        
        m_p = NULL;
    }
    
    explicit remote_integer(const int n) {
        cout << "Unary constructor." << endl;
        
        m_p = new int(n);
    }
    
    remote_integer(const remote_integer& other) {
        cout << "Copy constructor." << endl;
        
        if (other.m_p) {
            m_p = new int(*other.m_p);
        } else {
            m_p = NULL;
        }
    }
    
    remote_integer(remote_integer&& other) {
        cout << "MOVE CONSTRUCTOR." << endl;
        
        m_p = other.m_p;
        other.m_p = NULL;
    }
    
    remote_integer& operator=(const remote_integer& other) {
        cout << "Copy assignment operator." << endl;
        
        if (this != &other) {
            delete m_p;
            
            if (other.m_p) {
                m_p = new int(*other.m_p);
            } else {
                m_p = NULL;
            }
        }
        
        return *this;
    }
    
    remote_integer& operator=(remote_integer&& other) {
        cout << "MOVE ASSIGNMENT OPERATOR." << endl;
        
        if (this != &other) {
            delete m_p;
            
            m_p = other.m_p;
            other.m_p = NULL;
        }
        
        return *this;
    }
    
    ~remote_integer() {
        cout << "Destructor." << endl;
        
        delete m_p;
    }
    
    int get() const {
        return m_p ? *m_p : 0;
    }
    
private:
    int * m_p;
};

class remote_point {
public:
    remote_point(const int x_arg, const int y_arg)
    : m_x(x_arg), m_y(y_arg) { }
    
    remote_point(remote_point&& other)
    : m_x(Move(other.m_x)),
    m_y(Move(other.m_y)) { }
    
    remote_point& operator=(remote_point&& other) {
        m_x = Move(other.m_x);
        m_y = Move(other.m_y);
        return *this;
    }
    
    int x() const { return m_x.get(); }
    int y() const { return m_y.get(); }
    
private:
    remote_integer m_x;
    remote_integer m_y;
};

remote_point five_by_five() {
    return remote_point(5, 5);
}

remote_point taxicab(const int n) {
    if (n == 0) {
        return remote_point(1, 1728);
    }
    
    remote_point ret(729, 1000);
    
    return ret;
}

int main() {
    remote_point p = taxicab(43112609);
    
    cout << "(" << p.x() << ", " << p.y() << ")" << endl;
    
    p = five_by_five();
    
    cout << "(" << p.x() << ", " << p.y() << ")" << endl;
}