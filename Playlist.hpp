#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct songNode {

  string name;
  string artist;
  string genre;
  songNode* next;
  float priorityNum;

  int length[2];
};

class Playlist
{
  public:
    Playlist();
    ~Playlist();
    void addSong(songNode* song);//adds song to the vector and increments counter
    void deleteSong(string song, string artist);//searches the vector and deletes pointer to matching song
    void displayMostRecent();//displays the playlist in order of most recently added
    void displayDateAdded();//displays the playlist in the order added
    songNode* shufflePlaylist();//returns a pointer to a random song in the playlist
    songNode* playTheList(int spot);//returns songnode* at an inputted spot.
    int getPlaylistLength();//gets the length of the playlist
    string getName();
    void changeName(string name1);
  private:
    vector<songNode*> mysongs;
    int playlistlength;
    string name;
};

#endif
