//
//  Book.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef Book_h
#define Book_h

#include <iostream>
#include <vector>
#include <string>
#include "Library.h"
#include "Patron.h"
using namespace std;

class Patron;
class Library;

enum Locale {ON_SHELF, ON_HOLD, CHECKED_OUT};

class Book
{
private:
    string idCode;
    string title;
    string author;
    Locale location;
    Patron* checkedOutBy;
    Patron* requestedBy;
    int dateCheckedOut;
public:
    static const int CHECK_OUT_LENGTH = 21;
    Book();
    Book(string idc, string t, string a);
    int getCheckOutLength();
    string getIdCode();
    string getTitle();
    string getAuthor();
    Locale getLocation();
    void setLocation(Locale lo);
    Patron* getCheckedOutBy();
    void setCheckedOutBy(Patron* p);
    void deleteCheckedOutBy(Patron*);
    Patron* getRequestedBy();
    void setRequestedBy(Patron* p);
    int getDateCheckedOut();
    void setDateCheckedOut(int d);
};

#endif
