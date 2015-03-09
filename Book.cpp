#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Book.h"
#include "Patron.h"
#include <string>
using namespace std;

Library watson;

/******************************************************************************
 * Entry:   This constructor does not accept arguments.
 * Exit:    No value is returned from the constructor.
 * Purpose: Default constructor.
 * ***************************************************************************/
Book::Book() {} //default constructor

/******************************************************************************
 * Entry:   This constructor accepts three string objects as arguments.
 * Exit:    idCode, title, author, location, checkedOutBy and requestedBy are
 											intiialized.
 * Purpose: This is a constructor.
 * ***************************************************************************/
Book::Book(string idc, string t, string a) //constructor
{	idCode =idc;
  title = t;
  author = a;
  location = ON_SHELF;
  checkedOutBy = NULL;
  requestedBy = NULL;
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    An int is returned to the calling function.
 * Purpose: Accessor function that returns the length of time a Book has been
 											checked out.
 * ***************************************************************************/
int Book::getCheckOutLength()
{	return (watson.getCurrentDate() - dateCheckedOut); 
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    A string is returned to the calling function.
 * Purpose: Accessor function that returns the Book object's idCode.
 * ***************************************************************************/
string Book::getIdCode() 
{ return idCode; 
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    A string is returned to the calling function.
 * Purpose: Accessor function that returns the Book object's title.
 * ***************************************************************************/
string Book::getTitle() 
{ return title; 
}
/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    An int is returned to the calling function.
 * Purpose: Accessor function that returns the Book object's author.
 * ***************************************************************************/
string Book::getAuthor() 
{ return author; 
}
/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    A Locale (enumerated data type) is returned.
 * Purpose: Accessor function that returns the Book object's location.
 * ***************************************************************************/
Locale Book::getLocation() 
{ return location; 
}

/******************************************************************************
 * Entry:   This function accepts a Locale enumerated data type as an argument.
 * Exit:    This is a void function (does not return a value).
 * Purpose: Mutator function that sets the Book object's location.
 * ***************************************************************************/
void Book::setLocation(Locale lo) 
{	location = lo; 
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    A pointer to Patron object is returned.
 * Purpose: Accessor function that returns the checkedOutBy pointer to the
 											calling function.
 * ***************************************************************************/
Patron* Book::getCheckedOutBy() 
{	return checkedOutBy; 
}

/******************************************************************************
 * Entry:   This function accepts a pointer to Patron as an argument.
 * Exit:    This is a void function (does not return a value).
 * Purpose: Mutator function that sets the requestedBy pointer.
 * ***************************************************************************/
void Book::setCheckedOutBy(Patron* p) 
{	checkedOutBy = p;
}

/******************************************************************************
 * Entry:   This function accepts a pointer to Patron as an argument.
 * Exit:    This is a void function (does not return a value).
 * Purpose: This function sets the pointer to Patron to NULL.
 * ***************************************************************************/
void Book::deleteCheckedOutBy(Patron* p) 
{ p = NULL;
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    A pointer to Patron object is returned.
 * Purpose: Accessor function that returns the requestedBy pointer.
 * ***************************************************************************/
Patron* Book::getRequestedBy() 
{ return requestedBy;
}

/******************************************************************************
 * Entry:   This function accepts a pointer to Patron as an argument.
 * Exit:    This is a void function (does not return a value).
 * Purpose: Mutator function that sets the requestedBy pointer.
 * ***************************************************************************/
void Book::setRequestedBy(Patron* p) 
{	requestedBy = p;
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    An int is returned to the calling function.
 * Purpose: Accessor function that returns the date a book was checked out.
 * ***************************************************************************/
int Book::getDateCheckedOut() 
{ return dateCheckedOut; 
}

/******************************************************************************
 * Entry:   This function accepts an int as an argument.
 * Exit:    This is a void function (does not return a value).
 * Purpose: Mutator function that sets the date checked out.
 * ***************************************************************************/
void Book::setDateCheckedOut(int d){ dateCheckedOut = d; }