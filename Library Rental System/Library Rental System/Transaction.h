#pragma once

using namespace std;

class Transaction
{
public:
	//Default transaction constructor
	Transaction()
	{
	}

	//Destructor, copy constructor and assignment operator. Does not work.

	Transaction(const Transaction& trans)
	{
		for (int i = 0; i < trans.itemVector.size(); i++)
		{
			itemVector.push_back(trans.itemVector[i]->duplicate());
		}

	}

	Transaction& operator=(const Transaction& trans)
	{
		for (int i = 0; i < itemVector.size(); i++)
		{
			delete itemVector[i];
			itemVector[i] = nullptr;
		}
		itemVector.clear();

		for (int i = 0; i < trans.itemVector.size(); i++)
		{
			itemVector.push_back(trans.itemVector[i]->duplicate());
		}
		return *this;
	}

	~Transaction()
	{
		//cout << "Trans Destructor" << endl;
		for (int i = 0; i < itemVector.size(); i++)
		{
			delete itemVector[i];
			itemVector[i] = nullptr;
		}
		itemVector.clear();
	}

	//this function adds an item to the itemVector
	void borrowItems(Item* item)
	{
		itemVector.push_back(item);
	}

	//this function returns the itemVector
	vector<Item*> getItemVector()
	{
		return itemVector;
	}

	//this function is a setter to the itemVector attribute
	void setItemVector(vector<Item*> iVector)
	{
		itemVector = iVector;
	}
	//this function returns the index location of the found item in the a transaction.
	//the function return -1 if the item is not found
	int findBorrowedItem(Item* item)
	{
		int index = -1;
		for (int i = 0; i < itemVector.size(); i++)
		{
			if (itemVector[i] == item)
			{
				index = i;
				return index;
			}
		}
		return index;
	}



private:
	//holds the items borrowed in the vector
	vector<Item*> itemVector;
};

class Account
{
public:
	//Todo: default constructor and a non-default constructor that takes in the ID and password
	// Default constructor for account, sets id and password to none.
	Account()
	{
		id = "none";
		pass = "none";
	}

	//Non default constructor which initializes id and password.
	Account(string accid, string accpass)
	{
		id = accid;
		pass = accpass;

	}

	string getaccountid()
	{
		return id;
	}

	string getaccountpass()
	{
		return pass;
	}

	//Todo: getTransaction that function returns the vector of all transactions for the account
	vector<Transaction> getTransaction()
	{
		return translist;
	}

	//Todo: addTransaction function that adds a transaction to the transaction list
	void addTransaction(Transaction transaction)
	{
		translist.push_back(transaction);
	}


	//Todo: setTransaction function set the transaction vector in the account
	void setTransaction(vector<Transaction> iTransaction)
	{
		translist = iTransaction;
	}

	//Todo: Any required operators that is to be overloaded
private:
	//id holds the id of the account, pass holds the password
	string id, pass;
	//vector holds all the transactions associated to the account
	vector<Transaction> translist;
};
