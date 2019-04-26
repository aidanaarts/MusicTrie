#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "Playlist.hpp"

using namespace std;

Playlist::Playlist()
{

}

Playlist::~Playlist()
{

}
void Playlist::changeName(string name1)
{
  name = name1;
}
string Playlist::getName()
{
  return name;
}
void Playlist::addSong(songNode* song)
{

  // for (int i = 0; i < mysongs.size(); i++)
  // {
  //   if (mysongs[i].name == song->name)
  //   {
  //     return;
  //   }
  // }

  mysongs.push_back(song);
  playlistlength++;

}

void Playlist::deleteSong(string song, string artist)
{
  //search vector, delete pointer to matching song

  for (int i = 0; i < mysongs.size(); i++)
  {
    if (mysongs[i]->name == song && mysongs[i]->artist == artist)
    {
      mysongs.erase(mysongs.begin() + i);
      return;
    }
    else {
      cout << "Song not found in playlist" << endl;
    }
  }
}

void Playlist::displayMostRecent()
{
  //displays playlist in order of most recently added
  for (int i = 0; i < mysongs.size()-1; i--)
  {
    cout << mysongs[i]->name <<" by "<<mysongs[i]->artist<<endl;
  }
  return;

}

void Playlist::displayDateAdded()
{
  //display playlist in order added
  for (int i = 0; i < mysongs.size(); i++)
  {
    cout << mysongs[i]->name <<" by "<<mysongs[i]->artist<<endl;
  }
  return;
}

songNode* Playlist::shufflePlaylist()
{
  //return pointer to random song in playlist

  int random = rand() % mysongs.size();

  return (mysongs[random]);

}

songNode* Playlist::playTheList(int spot)
{
  //returns songNode at inputted spot
  return (mysongs[spot]);
}

int Playlist::getPlaylistLength()
{
  //gets length of playlist

  return mysongs.size();
}
