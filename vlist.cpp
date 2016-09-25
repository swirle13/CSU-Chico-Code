// vlist.cpp
// Jones, Troy
// tjones71
#include "vlist.h"

bool Vlist::insert(Video *video, int &vidsInList)
{	
	// if mHead is NULL or if video title in list is greater than inserted video title
	if (mHead == NULL || mHead->mVideo->getMovieTitle(mHead->mVideo) > video->getMovieTitle(video))
	{
		// if mHead is NULL or if video title in list is equal to inserted video title
		if (mHead != NULL && mHead->mVideo->getMovieTitle(mHead->mVideo) == video->getMovieTitle(video))
		{
			return false;
		}
		else
		{
			mHead = new Node(video, mHead);
			vidsInList++;
			return true;
		}
	}
	else
	{
		ptr = mHead;
		// while the next node is NULL and the next node video title is less than the inserted video
		while (ptr->mNext != NULL && ptr->mNext->mVideo->getMovieTitle(ptr->mNext->mVideo) < video->getMovieTitle(video))
		{
			ptr = ptr->mNext;
		}
		vidsInList++;
		ptr->mNext = new Node(video, ptr->mNext);
		return true;
	}
}

Video* Vlist::lookup(std::string title, int moviesInList)
{
	ptr = mHead;
	bool found = false;
		// while ptr is not NULL or requested title does not equal title in list
		while (ptr != NULL || title != ptr->mVideo->getMovieTitle(ptr->mVideo))
		{
			if (ptr->mVideo->getMovieTitle(ptr->mVideo) == title)
			{

				found = true;
				break;
			}
			ptr = ptr->mNext;
			if (ptr == NULL)
			{
				return NULL;
				break;
			}
		}
		
	if (found)
	{
		return ptr->mVideo;
	}
	else
	{
		return NULL;
	}
}

void Vlist::printAll()
{
	ptr = mHead;
	while (ptr != NULL)
	{
		ptr->mVideo->print(ptr->mVideo);
		ptr = ptr->mNext;
	}	
}

bool Vlist::remove(std::string title)
{
	if (mHead == NULL)
	{
		return false;
	}
	else if (mHead->mVideo->getMovieTitle(mHead->mVideo) == title)
	{
		Node* temp = mHead;
		mHead = mHead->mNext;
		delete temp;
		return true;
	}
	else
	{
		ptr = mHead;
		// if next ptr is not NULL and if the next video title in list is not equal to requested video title
		while (ptr->mNext != NULL && ptr->mVideo->getMovieTitle(ptr->mNext->mVideo) != title)
		{
			ptr = ptr->mNext;
		}
		// if next ptr is not NULL and if the next video title in list is equal to requested video title
		if (ptr->mNext != NULL && ptr->mVideo->getMovieTitle(ptr->mNext->mVideo) == title)
		{
			Node* temp = ptr->mNext;
			ptr->mNext = ptr->mNext->mNext;
			delete temp;
			return true;
		}
	}
	return false;
}