// main.cpp
// Jones, Troy
// tjones71
#include "vlist.h"
#ifndef VLIST_H
#define VLIST_H
using namespace std;

void doThis(Video*, Vlist&, string, int&, int&);	// the working function in main
void printMovie(Video*);	// prints movie
string turnToStars(int);	// turns int rating to * rating
//////////////////////////////////////////////////////////////////////////
int main()
{
	string command;	// user command
	int moviesInList = 0;
	int returnCommand = 0;
	Vlist vlist;
	Video* video = NULL;

	while (getline(cin, command))
	{
		doThis(video, vlist, command, returnCommand, moviesInList);
		if (returnCommand == 1)
		{
			break;
		}
	}
	
	return returnCommand;
}
//////////////////////////////////////////////////////////////////////////
void doThis(Video* video, Vlist& vlist, string command, int &returnCommand, int &moviesInList)
{

	if (command == "insert")
	{
		string title;
		string url;
		string comment;
		double length;
		int rating;
		
		getline(cin, title);
		getline(cin, url);
		getline(cin, comment);
		cin >> length;
		cin >> rating;
		cin.ignore();
		string starRating = turnToStars(rating);	// turns int rating into asterisks
		Video *newMovie = new Video;
		newMovie->setMovie(newMovie, title, url, comment, length, starRating);
		bool success = vlist.insert(newMovie, moviesInList);	// inserts movie into linked list
		if (success)
		{
			returnCommand = 0;
		}
		else
		{
			cerr << "Could not insert video <" << title << ", already in list." << endl;
			returnCommand = 0;
		}
	}
	else if (command == "length")
	{
		cout << moviesInList << endl;
		returnCommand = 0;
	}
	else if (command == "lookup")
	{
		string title;
		getline(cin, title);
		video = vlist.lookup(title, moviesInList);	// checks to see if entered movie is in list
		if (video != NULL)
		{
			printMovie(video);	// if movie is in list, prints to console
		}
		else
		{
			cerr << "Title <" << title << "> not in list." << endl;
		}
		returnCommand = 0;
	}
	else if (command == "print")
	{
		if (moviesInList == 0)
		{
			returnCommand = 0;
		}
		else
		{
			vlist.printAll();	// prints whole list to console
			returnCommand = 0;
		}
	}
	else if (command == "remove")
	{	
		string title;
		getline(cin, title);
		bool removed = vlist.remove(title);	// removes title passed in by user
		if (!removed)
		{
			cerr << "Title <" << title << "> not in list, could not delete." << endl;
		}
		returnCommand = 0;
	}
	else
	{
		cerr << "<" << command << "> is not a legal command, giving up." << endl;
		returnCommand = 1;
	}
}

void printMovie(Video* movie)
{
	cout << movie->getMovieTitle(movie) << ", " << movie->getMovieURL(movie) << ", " <<
		movie->getMovieComment(movie) << ", " << movie->getMovieLength(movie) << ", " <<
		movie->getMovieRating(movie) << endl;
}

string turnToStars(int intRating)
{
	switch (intRating)
	{
	case 1:
		return "*";
		break;
	case 2:
		return "**";
		break;
	case 3:
		return "***";
		break;
	case 4:
		return "****";
		break;
	case 5:
		return "*****";
		break;
	default:
		return "space... the final frontier.";
		break;
	}
}

#endif