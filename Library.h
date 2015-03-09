
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.

#ifndef __examples__Library__
#define __examples__Library__

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "Patron.h"
#include "Book.h"
#include <string>
using namespace std;

class Patron;
class Book;

class Library
{
private:
    vector<Book> holdings;
    vector<Patron> members;
    int currentDate;
public:
    static const double DAILY_FINE = 0.1;
    Library();
    vector<Book> getHoldings();
    vector<Patron> getMembers();

    bool isBookIdUnique(string);
    bool isPatronIdUnique(string); 
    bool memberMatch(string);

    bool bookMatch(string);

    void addBook(Book);
    void addMember(string,string);
    void checkOutBook(string patronID, string bookID);

    void returnBook(string bookID);
    void requestBook(string patronID, string bookID);
    void incrementCurrentDate();
    
    int getCurrentDate(); //ADDED to get current date

    void payFine(string patronID, double payment);
    void viewPatronInfo(string patronID);
    void viewBookInfo(string bookID);
};

#endif /* defined(__examples__Library__) */
