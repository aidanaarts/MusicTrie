#include <iostream>
#include <vector>
#include <queue>
#include "Playlist.hpp"
#include "MusicLibrary.hpp"

using namespace std;

//linked list structure of songNode pointers with add, remove, display,
//add to queue and delete from queue options
MusicLibrary::MusicLibrary()
{

}

MusicLibrary::~MusicLibrary()
{

}
/*
void MusicLibrary::removeSong(string name,string artist)
{
  songNode *temp = search(name,artist);
  mytrie.deleteSong(temp);
}
*/
void MusicLibrary::viewSongInfo(string songName, string artist)
{
  songNode *temp = search(songName,artist);
  cout<<endl<<endl;
  cout<<"________________________________________"<<endl;
  cout<<"Song Name: "<<temp->name<<endl;
  cout<<"Artist Name "<<temp->artist<<endl;
  cout<<"Genre: "<<temp->genre<<endl;
  cout<<"priorityNum: "<<temp->priorityNum<<endl;
  cout<<"________________________________________"<<endl;
}

void MusicLibrary::shuffle(string playlistName)
{
  for(int i = 0; i < myplaylists.size();i++)
  {
    string name = myplaylists[i].getName();
    if(playlistName == name)
    {
      myplaylists[i].shufflePlaylist();
    }
  }
}
void MusicLibrary::createPlaylist(string name2)
{
  Playlist newPlaylist;
  newPlaylist.changeName(name2);
  myplaylists.push_back(newPlaylist);
}

void MusicLibrary::addTooPlaylist(string playlistName,string songName,string artist)
{
  for(int i = 0; i < myplaylists.size();i++)
  {
    string name = myplaylists[i].getName();
    if(playlistName == name)
    {
      songNode *temp = search(songName,artist);
      myplaylists[i].addSong(temp);
    }
  }
}
void MusicLibrary::addToQueue(songNode* song)
{
  myqueue.push(song);
}

void MusicLibrary::displayAllPlaylist()
{
  for(int i = 0; i < myplaylists.size();i++)
  {
    string name = myplaylists[i].getName();
    cout<<name<<endl;
  }
}

void MusicLibrary::insertSong(string name, string artist, string genre, float priorityNum)
{
  songNode *newSong = new songNode;
  newSong->name = name;
  newSong->artist = artist;
  newSong->genre = genre;
  newSong->priorityNum = priorityNum;
  //newSong->mysong = mysong;
  mytrie.addSong(newSong);
}

void MusicLibrary::displayPlaylist(string playlistName, bool x)
{
  //calll the displaylist function in playlists for myplaylists[num]
  //boool represents which display output to call
  if (x)
  {
    for(int i = 0; i < myplaylists.size();i++)
    {
      string name = myplaylists[i].getName();
      if(playlistName == name)
      {
        myplaylists[i].displayMostRecent();
      }
    }
  }
  else
  {
    for(int i = 0; i < myplaylists.size();i++)
    {
      string name = myplaylists[i].getName();
      if(playlistName == name)
      {
        myplaylists[i].displayDateAdded();
      }
    }
  }
}

songNode* MusicLibrary::search(string songName, string artist)
{
  songNode *returnNode = mytrie.findSong(songName, artist);
  return returnNode;
}
/*
void MusicLibrary::removeFromQueue(songNode* song)
{
  for (int i = 0; i < myqueue.size(); i++)
  {
    if (song == myqueue[i])
    {
      myqueue.erase(myqueue.begin()+i);
      return;
    }
  }
  cout<<"Song not found in Queue"<<endl;
}
*/
void MusicLibrary::viewQueue()
{
  if (myqueue.empty())
  {
    cout<<"Oh No! Looks like your Queue is Empty!"<<endl;
    return;
  }
  vector<songNode*> temp;
  int queuesize = myqueue.size();
  cout<<"QueueSize is: "<<queuesize<<endl;
  for (int i = 0; i < myqueue.size(); i++)
  {
    temp.push_back(myqueue.front());
    cout<<temp[i]->name<<" by "<<temp[i]->artist<<endl;
    myqueue.pop();
  }
  for (int j = queuesize; j >= 0; j--)
  {
    myqueue.push(temp[j]);
  }
}

void MusicLibrary::displayTop5(string myword)
{
  mytrie.printTop5(myword);
}

songNode* MusicLibrary::getTop5(int num)
{
  songNode* temp = mytrie.getTop5(num);
  return temp;
}
