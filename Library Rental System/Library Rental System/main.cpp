#include <iostream>
#include "Library.h"
#include"Transaction.h"

using namespace std;

int menu()
{
	int option;
	cout << "1)View all items\n2)Borrow Items\n3)View Borrowed Items\n4)Return Borrowed Item\n5)Quit\nEnter Option : ";
	cin >> option;
	return option;
}
int login(Library lib)
{
	string id, pass;
	cout << endl;
	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter password: ";
	cin >> pass;
	return lib.validate(id, pass);
}
int main()
{
	//initializing a library instance
	string libraryId = "123";
	Library lib(libraryId);
	//is account validated?
	int accountIndex = login(lib);
	//if validated, show the menu
	if (accountIndex != -1)
	{
		//retreived the account object
		Account account = lib.getAccountList()[accountIndex];
		//holds the option, input for the menu option
		int option;
		do {
			option = menu();
			//Option 1 displays all items in the library both books and videos
			if (option == 1)
			{
				//implementation goes here
				//If the checkedout status of the book is false, its printed.
				for (int a = 0; a < lib.getItemList().size(); a++)
				{
					if (lib.getItemList()[a] != nullptr)
					{
						lib.getItemList()[a]->print();
					}

				}
			}
			//if option borrow item
			if (option == 2)
			{
				Transaction trans;
				int numItems;
				string itemId;
				cout << "\nHow many items to borrow: ";
				cin >> numItems;
				for (int i = 0; i < numItems; i++)
				{
					bool borrowed = false;

					cout << "\nEnter the ID of the item to borrow: ";
					cin >> itemId;
					//check if the itemId is borrowed by the user



					int foundInd = lib.SearchItem(itemId);
					if (foundInd != -1)
					{

						//borrow the item by calling the transaction object
						trans.borrowItems(lib.getItemList()[foundInd]);
						lib.removeItem(lib.getItemList()[foundInd]);
						//note that the item should not be available to be borrowed again if it is borrowed by a user



					}
					else
					{
						cout << "Item not found in the library..." << endl;
						i--;
					}

				}
				cout << "Items borrowed successfully..." << endl << endl;
				//add the transaction to the account
				account.addTransaction(trans);

			}
			//if option is to view borrowed items
			if (option == 3)
			{
				//View the borrowed items. Borrowed items can be of type book or video
				//All the items in the account vector is displayed.
				cout << "============== Borrowed Items =============" << endl << endl;

				for (int i = 0; i < account.getTransaction().size(); i++)
				{
					for (int j = 0; j < account.getTransaction()[i].getItemVector().size(); j++)
					{


						if (dynamic_cast<Book*>(account.getTransaction()[i].getItemVector()[j]))
						{
							dynamic_cast<Book*>(account.getTransaction()[i].getItemVector()[j])->print();
						}
						else
						{
							dynamic_cast<Video*>(account.getTransaction()[i].getItemVector()[j])->print();
						}


					}

				}
				cout << "========== End of Borrowed Items ==========" << endl;
			}
			//option to return an item back to the library
			if (option == 4)
			{
				//return the item back to the library
				Transaction returnitem;
				string itemId;

				cout << "\nEnter the ID of the item to return: ";
				cin >> itemId;
				int check = 0;

				//If itemid exists, the checkout status is set to false.
				for (int i = 0; i < account.getTransaction().size(); i++)
				{
					for (int j = 0; j < account.getTransaction()[i].getItemVector().size(); j++)
					{
						if (itemId == account.getTransaction()[i].getItemVector()[j]->getID())
						{
							check = 1;

							lib.addItem(account.getTransaction()[i].getItemVector()[j]->duplicate());
							vector<Transaction> trans = account.getTransaction();
							vector<Item*> item = trans[i].getItemVector();
							delete item[j];

							item.erase(item.begin() + j);
							trans[i].setItemVector(item);
							account.setTransaction(trans);

							cout << "Return successful...." << endl << endl;

							break;
						}
					}
				}

				if (check == 0)
				{
					cout << "Item not borrowed..." << endl;
				}

			}
		} while (option != 5); //end of do while
	}
	system("pause");
	return 0;
}




