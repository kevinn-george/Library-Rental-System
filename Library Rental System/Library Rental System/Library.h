#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Item.h"
#include "Transaction.h"
using namespace std;

class Library
{
public:
	//Todo: constructor that takes a library ID (string)
	//Initializes libId and reads book.txt, video.txt and account.txt
	Library(string libID)
	{
		libId = libID;

		readBookItems();
		readVideoItems();
		readAccount();
	}
	//Copy constructor that copies id, vector of itemlist and accountlist.
	//copies all objects in lib.itemlist and lib.accountlist, and copies libId

	Library(const Library& lib)
	{
		libId = lib.libId;
		for (int i = 0; i < lib.itemList.size(); i++)
		{
			itemList.push_back(lib.itemList[i]->duplicate());

		}

		for (int i = 0; i < lib.accountList.size(); i++)
		{
			accountList.push_back(lib.accountList[i]);
		}
	}

	//Operator= which clears the itemlist and account list vectors, then copies id, vector of itemlist and accountlist.
	//copies all objects in lib.itemlist and lib.accountlist, and copies libId

	void operator=(const Library& lib)
	{
		for (int i = 0; i < itemList.size(); i++)
		{
			delete itemList[i];
		}
		itemList.clear();
		accountList.clear();
		libId = lib.libId;
		for (int i = 0; i < lib.itemList.size(); i++)
		{
			itemList.push_back(lib.itemList[i]->duplicate());
		}

		for (int i = 0; i < lib.accountList.size(); i++)
		{
			accountList.push_back(lib.accountList[i]);
		}

	}

	//Library destructor which deletes itemlist vector and sets it to null ptr.
	~Library()
	{
		//cout << "Library Destructor" << endl;
		for (int i = 0; i < itemList.size(); i++)
		{
			delete itemList[i];
			itemList[i] = nullptr;
		}
		itemList.clear();
		accountList.clear();
	}

	// Todo: readBookItems function reads from the book.txt, creates the book object and
	//stores them in the ItemList vector. Note the name of the file is “book” followed by the library ID.
	//Renames book file and copies all data into vector itemlist.
	void readBookItems()
	{
		string tempbookid, tempbookauthor, tempbooktitle;
		ifstream infile;
		string filename = "book" + libId + ".txt";

		infile.open(filename);
		if (infile.fail())
		{
			cout << "Book file failed to open..." << endl;
			exit(0);
		}
		int i = 0;
		while (!infile.eof())
		{
			infile >> tempbookid;
			infile.ignore();
			getline(infile, tempbooktitle);
			getline(infile, tempbookauthor);


			addItem(new Book(tempbookauthor, tempbookid, tempbooktitle));


		}

		infile.close();

	}
	// Todo: readVideoItems function that reads from the video.txt, creates the video
	//object and stores them in the ItemList vector. Note the name of the file is “video” followed by the library ID.
	//Renames video file and copies all data into vector itemlist.
	void readVideoItems()
	{

		string tempvidid, tempvidtitle, tempvidgenre, tempviddirector, tempvidproducer;
		ifstream infile;
		string filename = "video" + libId + ".txt";


		infile.open(filename);
		if (infile.fail())
		{
			cout << "Video file failed to open..." << endl;
			exit(0);
		}
		int i = 0;
		while (!infile.eof())
		{

			infile >> tempvidid;
			infile.ignore();
			getline(infile, tempvidtitle);
			infile >> tempvidgenre;
			infile.ignore();
			getline(infile, tempviddirector);
			getline(infile, tempvidproducer);

			addItem(new Video(tempvidgenre, tempviddirector, tempvidproducer, tempvidid, tempvidtitle));
		}

		infile.close();

	}
	// Todo: readAccount function reads from the account.txt, creates the account object
	//and stores them in the accountList vector. Note the name of the file is “account” followed by the library ID.
	//Renames account file and copies all data into vector accountlist.
	void readAccount()
	{

		ifstream infile;
		string filename = "account" + libId + ".txt";


		infile.open(filename);
		if (infile.fail())
		{
			cout << "Account file failed to open..." << endl;
			exit(0);
		}
		string tempid, temppass;
		int i = 0;
		while (!infile.eof())
		{
			infile >> tempid;
			infile >> temppass;
			Account account(tempid, temppass);
			accountList.push_back(account);

		}

		infile.close();
	}
	// Todo: validate function validates the passed id and password.
	//the function returns -1 if invalid, and the index of the account if valid
	//if id and password exists it returns the index else it returns -1.
	int validate(string aid, string apass)
	{
		int index = -1;
		for (int a = 0; a < accountList.size(); a++)
		{

			if (aid == accountList[a].getaccountid() && apass == accountList[a].getaccountpass())
			{
				index = a;
				return index;
			}
		}
		cout << "Wrong ID or Password" << endl;
		return index;
	}
	// Todo: getItemList function returns the vector of Items addresses
	//
	vector<Item*> getItemList()
	{
		return itemList;
	}
	// Todo: addItem function adds an Item into the itemList
	//
	void addItem(Item* item)
	{
		itemList.push_back(item);
	}
	// Todo: getAccountList function returns the accountList
	//
	vector<Account>getAccountList()
	{
		return accountList;
	}
	// Todo: removeItem function removes an item from the itemList and returns true if
	//item is found and removed successfully
	//If id in vector itemlist matched the id entered by user, it is removes from vector, and returns true.
	bool removeItem(Item* item)
	{
		for (int i = 0; i < itemList.size(); i++)
		{
			if (itemList[i]->getID() == item->getID())
			{
				if (i < itemList.size())
				{
					itemList.erase(itemList.begin() + i);
					return true;
				}
				else {
					break;
				}
			}
		}
		return false;
	}
	//SearchItem function searches for an item.
	//the function returns the index of the found item. If no item is found,
	//the function returns -1
	//
	int SearchItem(string id)
	{
		int index = -1;
		for (int i = 0; i < itemList.size(); i++)
		{
			if (id == itemList[i]->getID())
			{
				index = i;
				return index;
			}
		}
		return index;
	}


private:
	//libId: holds the library ID
	string libId;
	//itemList hold the items objects in the library
	vector<Item*> itemList;
	//accountList hold the account objects
	vector<Account> accountList;

};
