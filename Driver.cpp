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
  cout<<endl<<endl;
  cout<<"Welcome to Your Personal Music Library!"<<endl;
  cout<<"---------------------------------------"<<endl;
  cout<<"We Have Already Filled the Library for You What would you like to do?"<<endl;
  cout<<endl;
  cout<<"1. Create a playlist "<<endl;
  cout<<endl;
  cout<<"2. Shuffle, Display, or Play a Playlist"<<endl;
  cout<<endl;
  cout<<"3. Add to Queue or view queue"<<endl;
  cout<<endl;
  cout<<"4. View a songs information"<<endl;
  cout<<endl;
  cout<<"5. Search for song"<<endl;
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
        cout<<"________Which playlist would you like to display?________"<<endl;
        cout<<"--------Below is a list of your current playlists--------"<<endl;
        MyLibrary.displayAllPlaylist();
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
      string choicez3;
      cout<<"Enter 1 to add to queue"<<endl;
      cout<<"Enter 2 to view your queue"<<endl;
      getline(cin,choicez3);
      if(choicez3 == "1")
      {
        cout<<"enter song to add to queue press enter then type in the artist name"<<endl;
        getline(cin,choicez);
        getline(cin,choicez2);
        songNode *temp = MyLibrary.search(choicez,choicez2);
        MyLibrary.addToQueue(temp);
      }
      else if(choicez3 == "2")
      {
        MyLibrary.viewQueue();
      }
      else
      {
        cout<<"Invalid Choice"<<endl;
      }

    }
    else if(choice =="4")
    {
      string choicez4;
      string choicez5;
      cout<<"enter song to add to queue press enter then type in the artist name"<<endl;
      getline(cin,choicez4);
      getline(cin,choicez5);
      MyLibrary.viewSongInfo(choicez4,choicez5);
    }
    else if (choice == "5")
    {
      string choice4;
      string updatingchoice;
      cout<<"Enter the name of the song you would like to search!"<<endl;
      getline(cin,choice4);
      updatingchoice = choice4;
      MyLibrary.displayTop5(choice4);
      bool br = true;
      while(br)
      {
        cout<<"If you would like to select an option enter the corresponding number, else keep typing"<<endl;
        cout<<updatingchoice;
        if (choice4 == "1" || choice4 == "2" || choice4 == "3" || choice4 == "4" || choice4 == "5")
        {
          br = false;
          break;
        }
        getline(cin,choice4);
        updatingchoice = updatingchoice + choice4;
        MyLibrary.displayTop5(updatingchoice);
      }
      songNode* mysong4 = MyLibrary.getTop5(stoi(choice4));
      cout<<"What would you like to do with your song?"<<endl;
      cout<<"1. Add to playlist"<<endl;
      cout<<"2. Add to queue"<<endl;
      cout<<"3. Play Song"<<endl;
      getline(cin,choice4);
      while(choice4 != "1" && choice4 != "2" && choice4 != "3")
      {
        cout<<"Not a valid selection please try again"<<endl;
        getline(cin,choice4);
      }
      if (choice4 == "1")
      {
        cout<<"What playlist would you like to add too?"<<endl;
        MyLibrary.addTooPlaylist(choice4, mysong4->name, mysong4->artist);
      }
      else if (choice4 == "2")
      {
        cout<<"Adding to Queue"<<endl;
        MyLibrary.addToQueue(mysong4);
      }
      else if (choice4 == "3")
      {
        cout<<"Playing "<<mysong4->name<<" by "<<mysong4->artist<<endl;
      }
    }
  }
}
