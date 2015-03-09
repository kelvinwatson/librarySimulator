#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Library.h"
#include "Patron.h"
#include "Book.h"
#include <string>
using namespace std;

/******************************************************************************
 * Entry:   The default constructor does not accept arguments.
 * Exit:    fineAmount is set to zero.
 * Purpose: This is the default constructor.
 * ***************************************************************************/
Patron::Patron() 
{	checkedOutBooks.reserve(100);
		fineAmount = 0;
}

/******************************************************************************
 * Entry:   This constructor accepts two string arguments.
 * Exit:    idNum,  name and fineAmount are initialized.
 * Purpose: This is a constructor.
 * ***************************************************************************/
Patron::Patron(string idn, string n)
{	idNum = idn;
		name = n;
		checkedOutBooks.reserve(100);
		fineAmount = 0;
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    Returns idNum of Patron object.
 * Purpose: Accessor function, retrieves ID number of Patron.
 * ***************************************************************************/
string Patron::getIdNum() 
{ return idNum; 
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    Returns name of Patron object.
 * Purpose: Accessor function, retrieves name of Patron.
 * ***************************************************************************/
string Patron::getName() 
{ return name; 
}

/******************************************************************************
 * Entry:   This function accepts a pointer to Book object(s) as an argument.
 * Exit:    Void return type, no value returned.
 * Purpose: Mutator function, pushes a Book object into the checkedOutBooks 
 			vector within Patron object.
 * ***************************************************************************/
void Patron::setCheckedOutBooks(Book *b)	
{	checkedOutBooks.push_back(b);
	vector<Book*>::iterator it;
	for (it = checkedOutBooks.begin(); it != checkedOutBooks.end(); ++it)
	{	//cout << (*it)->getIdCode() << endl; //for testing
	} 
}  

/******************************************************************************
 * Entry:   This function accepts an integer (by value) as an argument.
 * Exit:    Void return type, no value returned.
 * Purpose: Deletes an element (Book object) in a vector and shifts remaining
 			elements to the left.
 * ***************************************************************************/
void Patron::deleteCheckedOutBook(int ith) 
{	checkedOutBooks.erase(checkedOutBooks.begin()+ith); //delete the ith element 
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    This function regurns a vector of Book pointers.
 * Purpose: This function returns a vector of Book pointers to the calling
 											function.
 * ***************************************************************************/
vector<Book*> Patron::getCheckedOutBooks()	
{	return checkedOutBooks;	
}

/******************************************************************************
 * Entry:   This function accepts an integer (by value) as an argument.
 * Exit:    Void return type, no value returned.
 * Purpose: Deletes an element (Book object) in a vector and shifts remaining
 			elements to the left.
 * ***************************************************************************/
double Patron::getFineAmount() 
{ return fineAmount; 
}

/******************************************************************************
 * Entry:   This function accepts a double as an argument.
 * Exit:    Void return type, no value returned.
 * Purpose: Increases the fineAmount if value passed in is positive, and
 			decreases the fineAmount if value passed in is negative.
 * ***************************************************************************/
void Patron::amendFine(double amount)
{	fineAmount += amount;
	//cout << "FinesAmount is " << fineAmount << endl;
}