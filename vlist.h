// vlist.h
// Jones, Troy
// tjones71
#include "video.h"

class Vlist : public Video
{
public:
	/* Variables */

	/* Functions */
	Vlist() { mHead = NULL; };
	bool insert(Video*, int&);	// passes pointer to Vlist to be inserted
	Video* lookup(std::string, int);	// looks for a movie according to title
	void printAll();	// public function for ability to print list
	bool remove(std::string);	// removes chosen title if available
private:
	int vidsInList = 0;	// keeps track of amount of videos in list
	class Node
	{
	public:
		/* Functions */
		Node(Video *video, Node *next)
		{
			mVideo = video;
			mNext = next;
		}
		/* Variables */
		Node *mNext;
		Video *mVideo;
	};
	Node *mHead;	// beginning of linked list
	Node* ptr;	// ptr to be used in vlist functions
};