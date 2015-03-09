//
//  Patron.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef __examples__Patron__
#define __examples__Patron__

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "Library.h"
#include "Book.h"
using namespace std;

class Book;
class Library;

class Patron
{
private:
    string idNum;
    string name;
    vector<Book*> checkedOutBooks;
    double fineAmount;
public:
    Patron(); //default constructor
    Patron(string,string); //constructor
    string getIdNum();
    string getName();

    void setCheckedOutBooks(Book *b);    

    vector<Book*> getCheckedOutBooks();

    void deleteCheckedOutBook(int); 
    
    void addBook(Book* b);
  //  void removeBook(Book* b);
    double getFineAmount();
    void amendFine(double amount);
};

#endif /* defined(__examples__Patron__) */
