/****************************************************
Name: Nathan Jones
Date: April 5, 2013
Problem Number: Program 5
Instructor: Komogortsev, TSU
*****************************************************/

#include <iostream>
#include <fstream>

#include "tsuPod.h"
#include "Song.h"

using namespace std;

int main()
{
	TsuPod tsuPod(25, 100);									// Constructor of TsuPod with 25 songs, 100 max memory
	int totalSongs = 0;										// Starting number of songs of blank TsuPod
	int totalMemory = 0;									// Starting memory of blank TsuPod

	cout << "Total memory: " << totalMemory << endl << endl;

	int retCode;											// Return code for error coding

	retCode = tsuPod.initTsuPod();							// Calls tsuPod member function initTsuPod, initiates tsuPod to all blank songs
	if(retCode == -1)
	{
		cout << "Unable to open file. Closing...";
		return -1;
	}

	retCode = tsuPod.showSongList();						// Calls tsuPod member function showSongList, shows list of songs in tsuPod

	cout << endl;

	// Following lines tests tsuPod input functionality by adding songs through tsuPod member function addSong

   	retCode = tsuPod.addSong("Comfort Eagle", "Cake", 4, 1, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Mr. Tambourine Man", "Bob Dylan", 7, 2, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Just Like Heaven", "The Cure", 5, 3, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Under the Bridge", "Red Hot Chili Peppers", 8, 4, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Pancho and Lefty", "Townes Van Zandt", 7, 5, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Space Oddity", "David Bowie", 12, 6, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Midnight City", "M83", 9, 7, totalMemory, totalSongs);
    retCode = tsuPod.addSong("Icky Thump", "The White Stripes", 4, 8, totalMemory, totalSongs);

	cout << "Return Code: " << retCode << endl << endl;

	tsuPod.showSongList();

	tsuPod.sortSongList(totalSongs);					// Calls tsuPod member function sortSongList, sorts songs in alphabetical order by title

	tsuPod.showSongList();

	cout << "Remaining memory: " << tsuPod.getRemainingMemory(totalMemory) << endl;		// Shows remaining memory in tsuPod

	retCode = tsuPod.removeSong("Midnight City", "M83", 8, 4, totalMemory, totalSongs);	// Removes song from tsuPod

	cout << "Remaining memory: " << tsuPod.getRemainingMemory(totalMemory) << endl << endl;

	tsuPod.showSongList();

	tsuPod.clearSongList();								// Calls tsuPod member function clearSongList, clears all songs within tsuPod

	tsuPod.showSongList();

	tsuPod.closeFile();									// Closes binary file

	return 0;
}
