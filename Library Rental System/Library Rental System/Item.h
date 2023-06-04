#pragma once
#include <iostream>
#include <string>
using namespace std;

class Item
{
public:
	//constructors
	Item()
	{
		id = "none";
		title = "none";
	}

	Item(string iid, string ititle)
	{
		id = iid;
		title = ititle;
	}

	Item(string iid)
	{
		id = iid;
		title = "none";
	}

	//getters and setters
	string getID()
	{
		return id;
	}

	//Include virtual function print
	virtual void print() = 0;

	virtual Item* duplicate()
	{
		return nullptr;
	}

	virtual ~Item()
	{
		//cout << "Item destructor" << endl;
	}


protected:
	//common attributes for video and book items
	string id;
	string title;


};

class Book : public Item
{
public:
	//Default constructor of Book, when author id and title initialized.
	Book(string author, string id, string title) : Item(id, title)
	{
		bauthor = author;
	}

	Book* duplicate()
	{
		Book* book = new Book(bauthor, id, title);
		return book;
	}

	//Prints output of books.
	virtual void print()
	{
		cout << "---------------Book Item----------------" << endl;
		cout << "Book Id: " << id << endl;
		cout << "Book title: " << title << endl;
		cout << "Book Author: " << bauthor << endl;
		cout << "-----------------------------------------" << endl << endl;
	}

	~Book()
	{
		//cout << "Book Destructor" << endl;
	}
private:
	string bauthor;
};

class Video : public Item
{
public:
	//Default constructor of Video, when genre, director, producer,  id and title initialized.
	Video(string genre, string director, string producer, string id, string title) : Item(id, title)
	{
		vgenre = genre;
		vdirector = director;
		vproducer = producer;
	}

	Video* duplicate()
	{
		Video* video = new Video(vgenre, vdirector, vproducer, id, title);
		return video;
	}

	//Prints output of Videos.

	virtual void print()
	{
		cout << "---------------Video Item----------------" << endl;
		cout << "Video Information:" << endl;
		cout << "Video Id: " << id << endl;
		cout << "Video Title: " << title << endl;
		cout << "Video Director: " << vdirector << endl;
		cout << "Video Genre: " << vgenre << endl;
		cout << "Video Producer: " << vproducer << endl;
		cout << "-----------------------------------------" << endl << endl;
	}

	~Video()
	{
		//cout << "video destructor" << endl;
	}
private:
	string vgenre, vdirector, vproducer;
};

