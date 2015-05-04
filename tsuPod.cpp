/****************************************************
Name: Nathan Jones
Date: April 5, 2013
Problem Number: Program 5
Instructor: Komogortsev, TSU
*****************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "tsuPod.h"

using namespace std;

TsuPod::TsuPod()								// Default constructor
{
	numSongs = 0;
	maxSize = 0;
}

TsuPod::TsuPod(int CnumSongs, int CmaxSize)		// Constructor with parameters
{
	numSongs = CnumSongs;
	maxSize = CmaxSize;
}

int TsuPod::initTsuPod()
{
	Song s;																	// Declares a Song object for use within function

	fio.open("tsupod_memory.dat", ios::in | ios::out | ios::binary);		// Opens binary file for both input and output

	if(!fio)																// If unable to open fio, returns an error code to driver
		return -1;

	for(int i = 0; i < numSongs; i++)										// For loop initializes maximum number of songs to blank
	{
		fio.seekp((i)*sizeof(s), ios::beg);

		fio.write(reinterpret_cast<char *>(&s), sizeof(s));
	}

	return 0;
}

int TsuPod::addSong(string strTitle, string strArtist, int size, int songNum, int &totalMemory, int &totalSongs)
{
	Song s;													// Declares a Song object for use within function

	char songTitle[256];									// Temporary char arrays to hold string inputs
	char songArtist[256];

	if(songNum > numSongs)
	{
		cout << "Could not add song, song number cannot exceed " << getNumSongs() << endl << endl;
		return -2;
	}

	if(size < 0)
	{
		cout << "Could not add song, song size cannot be less than zero." << endl << endl;
		return -4;
	}

	if(strTitle == " " || strArtist == " ")
	{
		cout << "Could not add song, song artist or title cannot be blank." << endl;
		return -6;
	}

	totalSongs++;											// Increment total number of songs in TsuPod

	if(totalSongs > numSongs)
	{
		cout << "Could not add song(s), song limit exceeded" << endl;
		totalSongs--;
		return -3;
	}

	totalMemory += size;									// Adds size of song to memory of TsuPod

	if(totalMemory > maxSize)
	{
		cout << "Could not add song(s), TsuPod memory exceeded." << endl;
		totalMemory -= size;
		totalSongs--;
		return -5;
	}

	strcpy(songTitle, strTitle.c_str());					// Used to convert string inputs to char arrays for processing in Song.h
	strcpy(songArtist, strArtist.c_str());

	s.setTitle(songTitle);									// Assigns song's title to song object

	s.setArtist(songArtist);								// Assigns song's artist to song object

	s.setSize(size);										// Assigns song's size to song object

	s.setPosition(songNum);									// Assigns song's number to song object

	fio.seekp((songNum-1)*sizeof(s), ios::beg);

	fio.write(reinterpret_cast<char *>(&s), sizeof(s));		// Writes song's information to binary file

	fio.seekp(0L, ios::beg);

	return 0;
}

int TsuPod::removeSong(string strTitle, string strArtist, int size, int songNum, int &totalMemory, int &totalSongs)
{
	Song s;													// Declares a Song object for use within function

	totalSongs--;

	totalMemory -= size;

	if(totalMemory < 0)
	{
		totalSongs++;
		totalMemory += size;
		cout << "Total memory cannot be below zero, re-adding song";
		return -1;
	}

	strTitle = "<< empty >>";								// Following lines set song properties to blank song
	strArtist = "<< empty >>";
	size = 0;

	char songTitle[256];									// Temporary char arrays to hold string inputs
	char songArtist[256];

	strcpy(songTitle, strTitle.c_str());					// Used to convert string inputs to char arrays for processing in Song.h
	strcpy(songArtist, strArtist.c_str());

	s.setTitle(songTitle);

	s.setArtist(songArtist);

	s.setSize(size);

	fio.seekp((songNum-1)*sizeof(s), ios::beg);

	fio.write(reinterpret_cast<char *>(&s), sizeof(s));		// Replaces song in binary file with blank song

	fio.seekp(0L, ios::beg);

	return 0;
}

int TsuPod::showSongList()
{
	Song s;													// Declares a Song object for use within function

	cout << "Song List:" << endl << endl;

	for(int i = 0; i < numSongs; i++)						// For loop reads in and displays songs from binary file
	{
		fio.seekg((i)*sizeof(s), ios::beg);

		fio.read(reinterpret_cast<char *>(&s), sizeof(s));

		cout << "Song " << i + 1 << ": " <<  s.getTitle() << ", " << s.getArtist() << ", Size: "
					 << s.getSize() << "MB" << endl;
	}

	cout << endl;

	fio.clear();
	fio.seekg(0L, ios::beg);

	return 0;
}

int TsuPod::clearSongList()
{
	Song s;													// Declares a Song object for use within function

	for(int i = 0; i < numSongs; i++)						// For loop removes all songs in binary file, replaces with blank songs
	{
		fio.seekp((i)*sizeof(s), ios::beg);

		fio.write(reinterpret_cast<char *>(&s), sizeof(s));
	}

	return 0;
}

int TsuPod::sortSongList(int totalSongs)								// Sorts song list by title in alphabetical order
{
	Song s1;
	Song s2;
	Song sTemp;
	Song sBlank;

	bool swap = true;

	for(int i = 0; i < (totalSongs); i++)
	{
		fio.seekg((i)*sizeof(s1), ios::beg);							// Reads in song 1

		fio.read(reinterpret_cast<char *>(&s1), sizeof(s1));

		for(int j = i + 1; j < totalSongs + 1; j++)
		{
			fio.seekg((j)*sizeof(s2), ios::beg);						// Reads in song 2

			fio.read(reinterpret_cast<char *>(&s2), sizeof(s2));

			if(s2 < s1)													// Performs song swap
			{
				if(s2 != sBlank)
				{
					sTemp = s1;
					s1 = s2;
					s2 = sTemp;

					fio.seekp((j)*sizeof(s2), ios::beg);					// Writes in new song 2

					fio.write(reinterpret_cast<char *>(&s2), sizeof(s2));

					swap = true;
				}
			}
			else if(s2 > s1)
			{
				swap = false;
			}
			else if(s2 == s1)
			{
				swap = false;
			}
		}

		fio.seekp((i)*sizeof(s1), ios::beg);							// Writes in new song 1

		fio.write(reinterpret_cast<char *>(&s1), sizeof(s1));

	}

	return 0;
}

int TsuPod::closeFile()									     // Closes file input/output
{
	fio.close();

	return 0;
}

int TsuPod::getNumSongs() const								// Retrieves numSongs from TsuPod
{
	return numSongs;
}

int TsuPod::getTotalMemory() const							// Retrieves maxSize from TsuPod
{
	return maxSize;
}

int TsuPod::getRemainingMemory(int totalMemory) const		// Retrieves remaining memory within TsuPod
{
	return totalMemory;
}

void TsuPod::setSong(Song sTemp)							// Sets song object
{
	song = sTemp;
}
