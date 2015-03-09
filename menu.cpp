#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "Library.h"
#include "Patron.h"
#include "Book.h"
using namespace std;

//function prototypes
void ShowOptions();  //displays menu of options
int GetChoice();     //reads in user input and validates

int main()
{	system("clear");
	cout << "*********************" << endl;
	cout << "* LIBRARY SIMULATOR *" << endl;
	cout << "*********************" << endl;
	cout << "Welcome to the Watson Library.";

	int choice;
	Library watson;
	string bookID, bookTitle, bookAuth;
	
	
 	do //loop allows program to run until user chooses to exit
  {  	ShowOptions();
      choice = GetChoice();
      if (choice==1) //Add a book
      { string tempBookID, tempBookTitle, tempBookAuth;
      	cout << "You have selected to add a book to the library shelf." << endl;
    		cout << "Please enter the following book information:" << endl;
    		cout << "  Book ID Code: ";
    		getline(cin,tempBookID); //check holdings  before  calling constructor
    		while (watson.isBookIdUnique(tempBookID)==false)
    		{	cout << "  Book ID is not unique. Please re-enter the ID code: ";
    			getline(cin,tempBookID);
    		}
    		cout << "    Book ID accepted." << endl;
    		cout << "  Book Title: ";
    		getline(cin,tempBookTitle);
    		cout << "  Book Author: ";
    		getline(cin,tempBookAuth);
    		Book newBook(tempBookID,tempBookTitle,tempBookAuth); //call constructor
    		watson.addBook(newBook); //call function to push newBook into vector
      }
      else if (choice==2) //Add a library patron
      {	string tempPatronID, tempPatronName;
      	cout << "You have chosen to input a new library patron." << endl;
      	cout << "Please enter the following patron information:" << endl;
      	cout << "  ID Number: ";
      	getline(cin,tempPatronID);
      	while (watson.isPatronIdUnique(tempPatronID)==false)
    		{	cout << "  Patron ID is not unique. Please re-enter the ID number: ";
    			getline(cin,tempPatronID);
    		}
    		cout << "    Patron ID accepted." << endl;
    		cout << "  Patron Name: ";
				getline(cin,tempPatronName);
      	watson.addMember(tempPatronID, tempPatronName);
      }

			else if (choice==3) //Check out a book
     	{ string tempPatronID,tempBookID;
     		cout <<"You have selected to check out a book for a patron." << endl;
     		if (watson.getHoldings().empty())
					cout << "There are no books in the library to check out." 
					<< endl;
				
				if (watson.getMembers().empty())
					cout << "There are no patrons for whom to check out a book." 
					<< endl;
				
				if ((!watson.getHoldings().empty()) && (!watson.getMembers().empty()))
	     	{	do
	      	{	cout << "Please enter the ID of the patron (or type \"escape\" to "
	      		"return to the menu): ";
	     			getline(cin,tempPatronID);
						if (tempPatronID=="escape")
	     				break;
						if (watson.memberMatch(tempPatronID))
							break;     			
	     			else if (!watson.memberMatch(tempPatronID))
						{	cout << "No match for patron ID on file." << endl;
							continue;
	     			}
	     		}while (!watson.memberMatch(tempPatronID));
					
					if (tempPatronID !="escape")
					{	do
		      	{	cout << "Please enter the ID of the book (or type \"escape\" to "
		      		"return to the menu): ";
		     			getline(cin,tempBookID);
							if (tempBookID=="escape")
								break;
							if (watson.bookMatch(tempBookID))
								break;     			
							else if (!watson.bookMatch(tempBookID))
							{	cout << "No match for book ID in the library.";
								continue;
							}
		     		} while (!watson.bookMatch(tempBookID));
	     		}
	     		if (tempPatronID != "escape" && tempBookID != "escape")
	     			watson.checkOutBook(tempPatronID,tempBookID);
	    	}
	    }

	    else if (choice==4) //Return a book
      { string tempBookID;
      	cout << "You have selected to return a book." << endl;
    		
    		if (watson.getHoldings().empty())
				{	cout << "There are no books in the library to return." 
					<< endl;
				}
				else if (!watson.getHoldings().empty())
				{	do
	      	{	cout << "Please enter the ID of the book (or type \"escape\" to "
	      		"return to the menu): ";
	     			getline(cin,tempBookID);
						if (tempBookID=="escape")
							break;
						if (watson.bookMatch(tempBookID))
							break;     			
						else if (!watson.bookMatch(tempBookID))
						{	cout << "No match for book ID in the library.";
							continue;
						}
	     		} while (!watson.bookMatch(tempBookID));
	      	if (tempBookID != "escape")
	      		watson.returnBook(tempBookID);
      	}
      }

      else if (choice==5) //Request a book
      { string tempBookID, tempPatronID;
      	cout << "You have selected to request a book." << endl;
      	if (watson.getHoldings().empty())
				{	cout << "There are no books in the library to place on hold." 
					<< endl;
				}
				if (watson.getMembers().empty())
				{	cout << "There are no patrons for whom to request a book." 
					<< endl;
				}
				else if ((!watson.getHoldings().empty()) && 
								(!watson.getMembers().empty()))
	      {	do
	      	{	cout << "Please enter the ID of the patron (of type \"escape\" to "
	      		"return to the menu): ";
	     			getline(cin,tempPatronID);
						if (tempPatronID=="escape")
	     				break;
						if (watson.memberMatch(tempPatronID))
							break;     			
	     			else if (!watson.memberMatch(tempPatronID))
						{	cout << "No match for patron ID on file." << endl;
							continue;
	     			}
	     		}while (!watson.memberMatch(tempPatronID));
	     		
		    	if (tempPatronID != "escape") 
		    	{	do 
		      	{	cout << "Please enter the ID of the book (or type \"escape\" to "
		      		"return to the menu): ";
		     			getline(cin,tempBookID);
							if (tempBookID=="escape")
								break;
							if (watson.bookMatch(tempBookID))
								break;     			
							else if (!watson.bookMatch(tempBookID))
							{	cout << "No match for book ID in the library.";
								continue;
							}
		     		} while(!watson.bookMatch(tempBookID));
	      	}	
	      	if (tempPatronID != "escape" && tempBookID != "escape")
	      		watson.requestBook(tempPatronID,tempBookID);
     		}

      }
 	   
 	   	else if (choice==6) //Enter patron's fine payment
      { string tempPatronID;
      	char payC[20];
      	double pay; 
      	cout << "You have selected to enter a patron's payment for fines." << 
      	endl;
      	if (watson.getMembers().empty())
				{	cout << "There are no patrons for whom to enter payment." 
					<< endl;
				}
				else if (!watson.getMembers().empty())
				{	do
	      	{	cout << "Please enter the ID of the patron (of type \"escape\" to "
	      		"return to the menu): ";
	     			getline(cin,tempPatronID);
						if (tempPatronID=="escape")
	     				break;
						if (watson.memberMatch(tempPatronID))
							break;     			
	     			else if (!watson.memberMatch(tempPatronID))
						{	cout << "No match for patron ID on file." << endl;
							continue;
	     			}
	     		}while (!watson.memberMatch(tempPatronID));
	     		bool inputAccepted=false; //priming read
	     		
	     		if (tempPatronID != "escape") 
		     	{	do //parse payment
		     		{	cout << "Please enter the payment amount: ";
		     			cin.getline(payC,20);
		     		 for (int i=0; i < strlen(payC); i++)
		     		 {	if (payC[i] <46 || payC[i] > 57 || payC[i] ==47)
		     		 		{	inputAccepted = false;
		          		cout << "Invalid payment: ";
		            	break;
		        	 	}
		         		else
		         		{	inputAccepted = true;
		            	continue;
		         		}
		      		}
		   			} while (inputAccepted == false);
		    	}
		    	if (inputAccepted == true)
	      		pay = atof(payC);
		    	if (tempPatronID != "escape")
		    	watson.payFine(tempPatronID,pay);
	    	}
 	   	}
 	   	
 	   	else if (choice==7)
      { watson.incrementCurrentDate();
      }
	    else if (choice==8) //View Patron Information
      { string tempPatronID;
      	cout << "You have selected to view patron information." << endl;
      	if (watson.getMembers().empty())
					cout << "There are no patrons to view." << endl;

      	else if (watson.getMembers().empty()==false)
      	{	do
	      	{	cout << "Please enter the ID of the patron: (or type \"escape\" to"
	      		" return to the menu): ";
	     			getline(cin,tempPatronID);
						if (tempPatronID=="escape")
	     				break;
						if (watson.memberMatch(tempPatronID))
							break;     			
	     			else if (!watson.memberMatch(tempPatronID))
						{	cout << "No match for patron ID on file." << endl;
							continue;
	     			}
	     		} while (!watson.memberMatch(tempPatronID));
	     		watson.viewPatronInfo(tempPatronID);
      	}
      }
      else if (choice==9) //View Book Information
      { string tempBookID;
      	cout << "You have selected to view book information." <<endl;
      	if (watson.getHoldings().empty())
					cout << "There are no books to view." << endl;

      	else if (watson.getHoldings().empty()==false)
      	{	do
	      	{	cout << "Please enter the ID of the book (or type \"escape\" to "
	      		"return to the menu): ";
	     			getline(cin,tempBookID);
						if (tempBookID=="escape")
							break;
						if (watson.bookMatch(tempBookID))
							break;     			
						else if (!watson.bookMatch(tempBookID))
						{	cout << "No match for book ID in the library.";
							continue;
						}
	     		} while (!watson.bookMatch(tempBookID));
      		watson.viewBookInfo(tempBookID);
      	}
      }	
      else if (choice==10)
      { cout << "You are exiting the Library program. Goodbye." << endl;
				exit(EXIT_SUCCESS);
      }
   } while (choice !=10);
   return 0;
}

/******************************************************************************
 * Entry:   This function does not accept any arguments.
 * Exit:    This function is void, and does not return any values to main.
 * Purpose: A menu of options is displayed for the user.
 * ***************************************************************************/
void ShowOptions()
{  cout << endl << "----------------------------------------------------------"
	 "-----------------" << endl;
   cout << endl << "Please select from the following menu by entering a number"
   " from 1 to 10" << endl << endl;
   cout << left << setw(6) << "Enter" << left << setw(23) << "Command" << left
   << setw(53) << "Description" << endl;
   cout << left << setw(6) << "1" << left << setw(23) << "ADD BOOK" << left
   << setw(53)
   << "Enter a new book" << endl;
   cout << left << setw(6) << "2" << left << setw(23) << "ADD MEMBER" << left 
   << setw(53) << "Enter a new library patron" << endl;
   cout << left << setw(6) << "3" << left << setw(23) << "CHECK OUT BOOK" 
   << left << setw(53) << "Check out a book from the library" << 
   endl;
   cout << left << setw(6) << "4" << left << setw(23) << "RETURN BOOK" << left 
   << setw(53) << "Return a book to the library" << endl;
   cout << left << setw(6) << "5" << left << setw(23) << "REQUEST BOOK" << left 
   << setw(53) << "Hold a book for a patron" << endl;
   cout << left << setw(6) << "6" << left << setw(23) << "PAY FINE" << left <<
   setw(53) << "Accept patron's payment for late returns" << endl;
   cout << left << setw(6) << "7" << left << setw(23) << "INCREMENT DATE" << 
   left << setw(53) << "Increment current date" << endl;
   cout << left << setw(6) << "8" << left << setw(23) << "VIEW PATRON INFO" <<
   left << setw(53) << "View patrons' information" << endl;
   cout << left << setw(6) << "9" << left << setw(23) << "VIEW BOOK INFO" << 
   left << setw(53) << "View book information" << endl;
   cout << left << setw(6) << "10" << left << setw(23) << "QUIT" << left <<
   setw(53) << "Exit the program" << endl;
   cout << "------------------------------------------------------------------"
   "--------" << endl;
}
/******************************************************************************
 * Entry:   This function does not accept any arguments, but returns the user's
 *          choice.
 * Exit:    The user's input is validated and returned to main.
 * Purpose: This function allows the user to enter a menu option, and validates
 *          the input before returning it.
 * ***************************************************************************/
int GetChoice()
{
   int choice;
   cout << endl << "Please enter a command from the menu above: ";
   cin >> choice;
   while(cin.get() != '\n' || cin.fail() || choice <1 || choice >10)
   {  cin.clear();
      cin.ignore(1000,'\n');
      cout << "Invalid selection. Please re-enter menu selection: ";
      cin >> choice;
   }
   return choice;
}   