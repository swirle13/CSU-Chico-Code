// video.cpp
// Jones, Troy
// tjones71
#include "video.h"

std::string Video::getMovieTitle(Video* video)
{
	return video->mTitle;
}

std::string Video::getMovieURL(Video* video)
{
	return video->mURL;
}

std::string Video::getMovieComment(Video* video)
{
	return video->mComment;
}

double Video::getMovieLength(Video* video)
{
	return video->mLength;
}

std::string Video::getMovieRating(Video* video)
{
	return video->mRating;
}

void Video::print(Video* movie)
{
	using namespace std;
	cout << movie->mTitle << ", " << movie->mURL << ", " << movie->mComment << ", " << movie->mLength << ", " << movie->mRating << endl;
}

Video* Video::setMovie(Video *newMovie,std::string title, std::string url, std::string comment, double length, std::string rating)
{
	newMovie->mTitle = title;
	newMovie->mURL = url;
	newMovie->mComment = comment;
	newMovie->mLength = length;
	newMovie->mRating = rating;

	return newMovie;
}