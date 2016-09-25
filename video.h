// video.h
// Jones, Troy
// tjones71
#include <iostream>
#include <string>
class Video
{
public:
	void print(Video*);	// prints selected video
	std::string getMovieTitle(Video*);	
	std::string getMovieURL(Video*);
	std::string getMovieComment(Video*);
	double getMovieLength(Video*);
	std::string getMovieRating(Video*);
	Video* setMovie(Video*, std::string, std::string, std::string, double, std::string);
private:
	/* Variables */
	std::string mComment;
	double mLength;
	std::string mTitle;
	std::string mURL;
	std::string mRating;
};