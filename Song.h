/****************************************************
Name: Nathan Jones
Date: April 5, 2013
Problem Number: Program 5
Instructor: Komogortsev, TSU
*****************************************************/

#ifndef SONG_H_
#define SONG_H_

#include <string>
#include <fstream>

using namespace std;

class Song
{
private:
	char artist[256];
	char title[256];
	int size;
	int position;
public:
	Song();
	Song(char*, char*, int, int);
	void setArtist(char*);
	void setTitle(char*);
	void setSize(int);
	void setPosition(int);
	const char* getArtist() const;
	const char* getTitle() const;
	int getSize() const;
	bool operator >(const Song &s);
	bool operator <(const Song &s);
	bool operator ==(const Song &s);
	bool operator !=(const Song &sBlank);
};

#endif /* SONG_H_ */
