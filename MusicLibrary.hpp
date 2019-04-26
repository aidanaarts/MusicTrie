#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <queue>
//#include "MP3.cpp"
#include "Trie.hpp"
#include "Playlist.hpp"

using namespace std;

/*
struct songNode {

  string name;
  string artist;
  string genre;
  songNode* next;
  float priorityNum;
  MP3 mysong;

  int length[2];
};
*/
class MusicLibrary
{
public:
  MusicLibrary();
  ~MusicLibrary();
  void insertSong(string name, string artist, string genre, float priorityNum);
  void removeSong(string name,string artist);
  void displayPlaylist(string playlistName,bool x);
  //void skipSong();
  void goback();
  void shuffle(string name);
  void displayAllPlaylist();
  songNode* search(string songName, string artist);
  void createPlaylist(string name);
  void displayCurrentSong();
  void addTooPlaylist(string playlistName,string songName,string artist);
  void addToQueue(songNode* song);
  void viewSongInfo(string songName, string artist);
  //void removeFromQueue(songNode* song);
  void viewQueue();
  songNode* getQueueSongnode(int i);
  void displayTop5(string myword);
  songNode* getTop5(int num);
  //void playSong(songNode* song);
  //void pauseSong();

private:
  Trie mytrie;
  vector<Playlist> myplaylists;
  songNode* currsong;
  vector<songNode*> history;
  queue<songNode*> myqueue;
};
