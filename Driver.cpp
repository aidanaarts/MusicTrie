#include "MusicLibrary.cpp"
#include "Playlist.cpp"
#include "Trie.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

void displaymenu()
{
  cout<<"Welcome to Your Personal Music Library!"<<endl;
  cout<<"---------------------------------------"<<endl;
  cout<<"We Have Already Filled the Library for You What would you like to do?"<<endl;
  cout<<endl;
  cout<<"1. Create a playlist "<<endl;
  cout<<endl;
  cout<<"2. Shuffle, Display, or Play a Playlist"<<endl;
  cout<<endl;
  cout<<"3. Add to Queue"<<endl;
  cout<<endl;
  //cout<<"4. Search for a Song"<<endl;
  cout<<endl;
  //cout<<"5. Play Current Queue"<<endl;
  cout<<endl;
  cout<<"6. Quit"<<endl;
  cout<<endl;
}
/*
wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
*/
int main(int argc, char* argv[])
{
  string line;
  ifstream myfile(argv[1]);
  MusicLibrary MyLibrary;
  if (myfile.is_open())
  {
    while(getline(myfile,line))
    {
      stringstream ss(line);
      string songname;
      string songartist;
      string songenre;
      string prionum;
      string s1;
      getline(ss, songname, ',');
      getline(ss, songartist, ',');
      getline(ss, songenre, ',');
      getline(ss, prionum, ',');
      getline(ss, s1, ',');
      //wstring s2 = s2ws(s1);
      //LPCWSTR mysongfile = s2.c_str();
      //MP3 mysong;
      //mysong.Load(mysongfile);
      MyLibrary.insertSong(songname, songartist, songenre, stof(prionum));
    }
    myfile.close();
  }
  else
  {
    cout<<"Unable to open song file"<<endl;
    return 0;
  }
  string choice = " ";
  while (choice != "6")
  {
    displaymenu();
    getline(cin, choice);
    if (choice == "1")
    {
      string choice1;
      cout<<"If at anytime you want to go back to main menu enter q6 when prompted for anything"<<endl;
      cout<<"You are Trying To Create A Playlist! What would you like to name your playlist?"<<endl;
      getline(cin, choice1);
      if (choice1 != "q6")
      {
        string playname = choice1;
        cout<<"Creating a Playlist with name: "<<choice1<<endl;
        MyLibrary.createPlaylist(playname);
        cout<<"Playlist created, would you like to add any songs to your playlist? (enter y for yes)"<<endl;
        getline(cin, choice1);
        while (choice1 == "y")
        {
          string name;
          string artist;
          cout<<"Please Enter The Name of the Song First, Then the Artist"<<endl;
          getline(cin, name);
          getline(cin, artist);
          if (name == "q6" || artist == "q6")
          {
            break;
          }
          MyLibrary.addTooPlaylist(playname, name, artist);
          cout<<"Would you like to add another song? (enter y for yes)"<<endl;
          getline(cin, choice1);
        }
        //cout<<"Playlist Created and Filled With: "<<MyLibrary.displayPlaylist(playname,false)<<endl;
      }
    }
    else if (choice == "2")
    {
      string choice2;
      string choice3;
      cout<<"If at anytime you want to go back to main menu enter q6 when prompted for anything"<<endl;
      cout<<"Would you like to: "<<endl;
      cout<<endl;
      cout<<"1. Shuffle Playlist: "<<endl;
      cout<<endl;
      cout<<"2. Display a Playlist"<<endl;
      cout<<endl;
      cout<<"3. Play a Playlist (inorder)"<<endl;
      cout<<endl;
      getline(cin, choice2);
      if (choice2 == "1")
      {
        cout<<"What Playlist Would you like to play? (enter list for a list)"<<endl;
        getline(cin,choice3);
        if (choice3 == "list")
        {
          MyLibrary.displayAllPlaylist();
        }
      }
      else if (choice2 == "2")
      {
        string list;
        cout << "which playlist would you like to display?" << endl;
        getline(cin, list);
        bool flag = false;
        MyLibrary.displayPlaylist(list,flag);
        break;
      }
    }
    else if (choice == "3")
    {
      string choicez;
      string choicez2;
      cout<<"enter song to add to queue press enter then type in the artist name"<<endl;
      getline(cin,choicez);
      getline(cin,choicez2);
      songNode *temp = MyLibrary.search(choicez,choicez2);
      MyLibrary.addToQueue(temp);
    }
  }
}
