#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Library.h"
#include "Book.h"
#include "Patron.h"

using namespace std;

/******************************************************************************
 * Entry:   This is the default constructor.
 * Exit:    The library instance is initialized with a zero for current date.
 						Also, the reserve function ensures that the vector can accomodate
 						at least 100 elements (books/patrons).
 * Purpose: Initializes an instance of the library class.
 * ***************************************************************************/
Library::Library() 
{	holdings.reserve(100);
	members.reserve(100);
	currentDate = 0;
}

/******************************************************************************
 * Entry:   This function takes in a string object by value.
 * Exit:    This function returns a bool value to the main.
 * Purpose: Determines whether or not the user-inputted book ID is unique. 
 						False is returned if the ID is the same as a book ID in the 
 						holdings vector, and true is returned otherwise. 
 * ***************************************************************************/
bool Library::isBookIdUnique(string idOfBook) 
{ bool unique=true;
	for (int i=0; i<holdings.size(); i++)
	{	if (idOfBook==holdings[i].getIdCode())
		{	unique=false;
			break;
		}
		else continue;
	}
	return unique;
}

/******************************************************************************
 * Entry:   This function takes in a string object by value.
 * Exit:    This function returns a bool value to the main.
 * Purpose: Determines whether or not the user-inputted patron ID is unique. 
 						False is returned if the ID is the same as a patron ID in the 
 						holdings vector, and true is returned otherwise. 
 * ***************************************************************************/
bool Library::isPatronIdUnique(string idOfPatron) 
{ bool unique=true;
	for (int i=0; i<members.size(); i++)
	{	if (idOfPatron==members[i].getIdNum())
		{	unique=false;
			break;
		}
		else continue;
	}
	return unique;
}

/******************************************************************************
 * Entry:   This function takes in a string object by value.
 * Exit:    This function returns a bool value to the main.
 * Purpose: Determines whether or not the patron ID provided by the user 
 						matches any ID's within the members vector.
 * ***************************************************************************/
bool Library::memberMatch(string pID)
{	bool match=false;
	for (int i=0; i<members.size(); i++)
	{	if (pID == members[i].getIdNum())
		{	match = true;	
			break;
		}
		else continue;
	}
	return match;
}

/******************************************************************************
 * Entry:   This function takes in a string object by value.
 * Exit:    This function returns a bool value to the main.
 * Purpose: Determines whether or not the book ID provided by the user 
 						matches any ID's within the holdings vector.
 * ***************************************************************************/
bool Library::bookMatch(string bID)
{ bool match=false;
	for (int i=0; i<holdings.size(); i++)
	{	if (bID == holdings[i].getIdCode())
		{	match = true;	
			break;
		}
		else continue;
	}
	return match;
}

/******************************************************************************
 * Entry:   This function does not take any arguments.
 * Exit:    This function returns a vector of Book objects.
 * Purpose: Retrieves the vector of Book objects in the library class.
 * ***************************************************************************/
vector<Book> Library::getHoldings() 	
{	return holdings;
}

/******************************************************************************
 * Entry:   This function does not take any arguments.
 * Exit:    This function returns a vector of Patron objects.
 * Purpose: Retrieves the vector of Patron objects in the library class.
 * ***************************************************************************/
vector<Patron> Library::getMembers()	
{	return members; 
}

/******************************************************************************
 * Entry:   This function takes in a Book object by value.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Pushes a Book object into the holdings vector.
 * ***************************************************************************/
void Library::addBook(Book aBook) 
{	holdings.push_back(aBook);
	//for (int i=0; i<holdings.size(); i++) //testing only
		//{	cout << "&holdings[i] is " << &holdings[i] << " "; }//testing only
	cout << endl << "Thank you, you have successfully added a "
  "book." << endl << endl;
}

/******************************************************************************
 * Entry:   This function takes in two string objects as arguments.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Pushes a Patron object into the members vector.
 * ***************************************************************************/
void Library::addMember(string pID, string pName) 
{	Patron nPatron(pID,pName);
	members.push_back(nPatron);
	cout << "Thank you, you have successfully added a new patron." << endl;
}

/******************************************************************************
 * Entry:   This function takes in two string objects as arguments.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Determines if a Book object can be CHECKED_OUT, and if so, checks
 						out the Book and assigns it to the Patron's CheckedOutBooks vector.
 						Books that are ON_HOLD will be checked out for the user who 
 						requested it, if available/returned/ON_SHELF.
 * ***************************************************************************/
void Library::checkOutBook(string patronID, string bookID)
{	bool patronIDMatch = false, bookIDMatch = false;
	int bookOnFile=-1, patronOnFile=-1; //which book/patron w/in holdings/patron vectors
	
	for (int i=0; i<members.size(); i++)
	{	if (patronID==members[i].getIdNum())
		{	patronIDMatch=true;
			patronOnFile=i;
			break;
		}
		else continue;
	}
	for (int i=0; i<holdings.size(); i++)
	{ if (bookID==holdings[i].getIdCode())
		{	bookIDMatch=true;
			bookOnFile=i;
			break;
		}
		else continue;
	}
	Patron* matchPatron = &members[patronOnFile]; //gets address of patron on file
	if (patronIDMatch==true && bookIDMatch==true) //patron and book on file
	{	if (holdings[bookOnFile].getLocation()==ON_SHELF) //is book on shelf?
		{	
			holdings[bookOnFile].setCheckedOutBy(matchPatron);
			holdings[bookOnFile].setLocation(CHECKED_OUT); //change location
			holdings[bookOnFile].setDateCheckedOut(currentDate); //set current date
			members[patronOnFile].setCheckedOutBooks(&holdings[bookOnFile]);  
			cout << members[patronOnFile].getName() << " has successfully checked "
			"out " << holdings[bookOnFile].getTitle() << ".";
		}
		else if (holdings[bookOnFile].getLocation()==CHECKED_OUT)
		{	Patron* patronPointer = holdings[bookOnFile].getCheckedOutBy();
			cout << "Sorry, " << holdings[bookOnFile].getTitle() << " is currently "
			"checked out by: " << (*patronPointer).getName() << " (ID: " 
			<< (*patronPointer).getIdNum() << ")" << endl;
		}
		else if (holdings[bookOnFile].getLocation()==ON_HOLD)
		{	Patron* patronPointer = holdings[bookOnFile].getRequestedBy();
			string patronIDWhoRequested = (*patronPointer).getIdNum();		
			string patronNameWhoRequested = (*patronPointer).getName();
			if (patronIDWhoRequested != patronID)	
				cout << "Sorry, " << holdings[bookOnFile].getTitle() << " is on hold "
				"for " << patronNameWhoRequested << endl;
			else if (patronIDWhoRequested == patronID)
			{	patronPointer = NULL;
				holdings[bookOnFile].setRequestedBy(patronPointer);
				holdings[bookOnFile].setCheckedOutBy(matchPatron);	
				holdings[bookOnFile].setLocation(CHECKED_OUT); //change location
				holdings[bookOnFile].setDateCheckedOut(currentDate); //set current date
				members[patronOnFile].setCheckedOutBooks(&holdings[bookOnFile]);
				cout << members[patronOnFile].getName() << "has successfully checked "
				"out: " << holdings[bookOnFile].getTitle() << ".";	
			}
		}
	}
	else if (patronIDMatch==false || bookIDMatch==false)
		cout << "Sorry, no matching patron ID or book ID on file.";
}

/******************************************************************************
 * Entry:   This function takes in a string objects as an argument.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Returns a book to the shelf if checked out.
 * ***************************************************************************/
void Library::returnBook(string bookID)
{	bool bookIDMatch=false;
	string tempPatronID;
	int bookOnFile=-1; //particular book w/in holdings
	for (int i=0; i<holdings.size(); i++)
	{ if (bookID==holdings[i].getIdCode())
		{	bookIDMatch=true;
			bookOnFile=i;
			break;
		}
		else continue;
	}
	if (holdings[bookOnFile].getLocation()==ON_SHELF)
			cout << "Cannot return " << holdings[bookOnFile].getTitle() << 
			" - this book is on the library shelf.";
	else if (holdings[bookOnFile].getLocation()==CHECKED_OUT)
	{	Patron* patronPointer = holdings[bookOnFile].getCheckedOutBy(); 
		(*patronPointer).deleteCheckedOutBook(bookOnFile);
		holdings[bookOnFile].deleteCheckedOutBy(patronPointer);
		holdings[bookOnFile].setLocation(ON_SHELF);
		cout << holdings[bookOnFile].getTitle() << " has been returned to the "
		"shelf." << endl;
	}
	//if the book has a requester, then we place it ON_HOLD
	Patron* patronPointer2 = holdings[bookOnFile].getRequestedBy();
	if (patronPointer2 != NULL) //this means the book has been requested
	{	holdings[bookOnFile].setCheckedOutBy(patronPointer2);
		holdings[bookOnFile].setLocation(CHECKED_OUT); //change location
		holdings[bookOnFile].setDateCheckedOut(currentDate); //set current date
		bool patronIDMatch=false;
		int patronOnFile=-1;
		for (int i=0; i<members.size(); i++)
		{	if ((*patronPointer2).getName() == members[i].getName())
			{	patronIDMatch=true;
				patronOnFile=i;
				break;
			}
			else continue;
		}
		members[patronOnFile].setCheckedOutBooks(&holdings[bookOnFile]);  
		cout << (*patronPointer2).getName() << " has now checked out " << 
		holdings[bookOnFile].getTitle() << ".";

		//cout << holdings[bookOnFile].getTitle() << " has now been placed on hold "
		//"as it was requested previously by "<< (*patronPointer2).getName() << " "
		//"(ID: " << (*patronPointer2).getIdNum() << ")" << endl;
		//holdings[bookOnFile].setLocation(ON_HOLD);
	}
}

/******************************************************************************
 * Entry:   This function takes in two string objects as arguments.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Sets a Book's location to ON_HOLD if not already ON_HOLD.
 * ***************************************************************************/
void Library::requestBook(string patronID, string bookID)
{ bool patronIDMatch = false, bookIDMatch = false; //determine which book it is
	int bookOnFile=-1, patronOnFile=-1;
	for (int i=0; i<holdings.size(); i++)
	{ if (bookID==holdings[i].getIdCode())
		{	bookIDMatch=true;
			bookOnFile=i;
			break;
		}
		else continue;
	}
	for (int i=0; i<members.size(); i++)
	{	if (patronID==members[i].getIdNum())
		{	patronIDMatch=true;
			patronOnFile=i;
			break;
		}
		else continue;
	}
	
	Patron* patronPointer = holdings[bookOnFile].getRequestedBy();
	if (patronPointer == NULL) //book has not yet been requested
	{	holdings[bookOnFile].setRequestedBy(&members[patronOnFile]); //Patron
		holdings[bookOnFile].setLocation(ON_HOLD);
		cout << holdings[bookOnFile].getTitle()	<< " has been placed on hold for "
		<<  members[patronOnFile].getName() << "." << endl;
	}
	else if (patronPointer != NULL) //book has already been requested		
	{	cout << "Unable to reserve as " << holdings[bookOnFile].getTitle()	<< 
		" has already been requested by " << (*patronPointer).getName() << endl;
	}
}

/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Increments the current date and amends the Patron's fine(s).
 * ***************************************************************************/
void Library::incrementCurrentDate() 
{	currentDate++; 
	cout << "Current Date has been changed from " << currentDate-1 << " to " 
	<< currentDate << endl;
	int i=0;
	for (i=0; i<members.size();i++)
	{	vector<Book*> checkedOut = members[i].getCheckedOutBooks(); //store
		if (!checkedOut.empty())  
		{	for (int x=0; x<checkedOut.size(); x++)
			{	int length = (currentDate - (*checkedOut[x]).getDateCheckedOut());
				if (length>21) 
				{	cout << " (" <<(*checkedOut[x]).getTitle() << " is overdue)" << 
					endl; 
					members[i].amendFine(DAILY_FINE);
				}
			} 
		}	
	}
}
    
/******************************************************************************
 * Entry:   This function does not accept arguments.
 * Exit:    This function returns an int value.
 * Purpose: Accessor function that gets the current date.
 * ***************************************************************************/    
int Library::getCurrentDate()
{ return currentDate;
} 

/******************************************************************************
 * Entry:   This function accepts a string and a double as arguments.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Decreases the Patron's fine(s).
 * ***************************************************************************/ 
void Library::payFine(string patronID, double payment)
{	payment *= -1; //convert payment into a negative number
	for (int i=0; i<members.size(); i++)
	{	if (patronID==members[i].getIdNum())
		{	members[i].amendFine(payment);
			cout << fixed << showpoint << setprecision(2);
			if (members[i].getFineAmount() >=0)
				cout << "Fines for " << members[i].getName() << " are now $" << 
				members[i].getFineAmount() << endl;
			else if (members[i].getFineAmount() <0)
				cout << members[i].getName() << " now has a credit balance of $" << 
				-1 * members[i].getFineAmount() << endl;
		}
	}
}

/******************************************************************************
 * Entry:   This function accepts a string as an argument.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Allows the user to view a specific Patron's information.
 * ***************************************************************************/ 
void Library::viewPatronInfo(string patronID)
{ int patronMatch;
	cout << "You have selected to view patron information." << endl;
	for (int i=0; i<members.size(); i++)
	{	if (patronID == members[i].getIdNum())
		{	patronMatch = i;
			cout << "  ID: " << members[i].getIdNum() << endl;
			cout << "  Name: " << members[i].getName() << endl;
		}
	}
	vector<Book*> checkedOut = members[patronMatch].getCheckedOutBooks(); //local
	if (checkedOut.empty())
 		cout << "  This patron does not have any checked-out books." << endl;
 	else if (!checkedOut.empty())	 		
 	{	cout << "  This patron has " << checkedOut.size() << " checked-out book(s): " 
 		<< endl;
 		for (int i=0; i<checkedOut.size(); i++)
 		{	cout << "    Book ID: " << (*checkedOut[i]).getIdCode();
 			cout << "  Title: " << (*checkedOut[i]).getTitle();
 			cout << "  Author: " << (*checkedOut[i]).getAuthor() << endl;
 		}
	}
	cout << fixed << showpoint << setprecision(2);
	if (members[patronMatch].getFineAmount() >=0)
		cout << "  Current Fines: $" << members[patronMatch].getFineAmount() << 
		endl;
	else if (members[patronMatch].getFineAmount() <0)
		cout << "  Credit Balance: $" << -1 * members[patronMatch].getFineAmount() 
		<< endl;
}

/******************************************************************************
 * Entry:   This function accepts a string as an argument.
 * Exit:    This function is void, and as such, does not return a value.
 * Purpose: Allows the user to view a specific Book's information.
 * ***************************************************************************/ 
void Library::viewBookInfo(string bookID)
{ int bookOnFile=-1;
	for (int i=0; i<holdings.size(); i++)
	{	if (bookID == holdings[i].getIdCode())
		{	bookOnFile=i;
			cout << "  Book ID: " << holdings[i].getIdCode() << endl;
			cout << "  Title: " << holdings[i].getTitle() << endl;
			cout << "  Author: " << holdings[i].getAuthor() << endl;
			int holdingLocation = holdings[bookOnFile].getLocation();
			if (holdingLocation==0)
				cout << "  Location: On Shelf" << endl;
			else if (holdingLocation==1)
			{	cout << "  Location: On Hold" << endl;
				Patron* patronPointer = holdings[bookOnFile].getRequestedBy(); 
				cout << "    Requested by: " << (*patronPointer).getName() << " (ID: "
				<< (*patronPointer).getIdNum() << ")" << endl;
			}
			else if (holdingLocation==2)
			{	cout << "  Location: Checked Out" << endl;
				Patron* patronPointer = holdings[bookOnFile].getCheckedOutBy();
				cout << "    Checked out by: " << (*patronPointer).getName() << 
				" (ID: " << (*patronPointer).getIdNum() << ")" << endl;
				cout << "    Due Date: " << holdings[bookOnFile].getDateCheckedOut() + 
				Book::CHECK_OUT_LENGTH << endl;
			}
		}
	}
}