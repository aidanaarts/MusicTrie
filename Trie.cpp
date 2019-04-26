#include "Trie.hpp"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

int getNum(char c)
{
    int num = int(c) - 97;
    return num;
}

void deletesonglist(songNode* node)
{
  if (node == NULL)
    return;
  songNode* temp = node;
  while (node != NULL)
  {
    temp = node;
    node = node->next;
    delete temp;
  }
}

void deleteTrienode(node* node)
{
  if (node == NULL)
    return;
  for (int i = 0; i < 26; i++)
  {
    delete node->children[i];
  }
  if (node->parent != NULL)
  {
    delete node->parent;
  }
  delete node;
  return;
}

node* createTriNode(char name, node* parent)
{
  node* newnode = new node;
  newnode->name = name;
  newnode->parent = parent;
  return newnode;
}

void destructorHelp(node* node1, node* head)
{
  if (node1 != NULL)
  {
    bool x = true;
    for (int i = 0; i < 26; i++)
    {
      if (node1->children[i] != NULL)
      {
        destructorHelp(node1->children[i], head);
      }
    }
    if (x == true)
    {
      if (node1 != head)
      {
        delete node1;
      }
      return;
    }
   }
}

void triePrintHelper(node* node)
{
  for (int i = 0; i < 26; i++)
  {
    if (node->children[i] != NULL)
    {
      triePrintHelper(node->children[i]);
    }
  }
  if (node->head != NULL)
  {
    songNode* temp = node->head;
    while(temp != NULL)
    {
      cout<<"Song Name: "<<temp->name<<" by "<<temp->artist<<endl;
      temp = temp->next;
    }
  }
}

Trie::Trie()
{
    head = new node;
    for (int i = 0; i < 26; i++)
    {
        head->children[i] = new node;
        head->children[i]->name = getChar(i);
        head->children[i]->parent = head;
    }
}


Trie::~Trie()
{
    destructorHelp(head, head);
    head = NULL;
}

void Trie::addSong(songNode *song)
{
    //cout<<"Started Addsong"<<endl;
    int child = 0;
    node* temp = head;
    for (int i = 0; i < song->name.size(); i++)
    {
        //cout<<"Starting on letter "<<song.name[i]<<endl;
        child = getNum(song->name[i]);
        if (temp->children[child] != NULL)
        {
            //cout<<"Going to next node "<< temp->children[child]->name<<endl;
            temp = temp->children[child];
        }
        else
        {
            temp->children[child] = createTriNode(song->name[i], temp);
            temp = temp->children[child];
            //cout<<"Created new node "<<temp->name<<endl;
        }
        if (i == song->name.size()-1)
        {
            if(temp->head == NULL)
            {
                temp->head = song;
                //cout<<"Added song as first song"<<endl;
                return;
            }
            songNode* temp2 = temp->head;
            while (temp2->next != NULL)
            {
                temp2 = temp2->next;
            }
            temp2->next = song;
            temp->isempty = false;
            //cout<<"Added song as not first song"<<endl;
            return;
        }
    }

}


char Trie::getChar(int num)
{
  for(char a='a'; a < 'a' + 26; ++a)
  {
    if(int(a)-97 == num)
    {
      return a;
    }
  }
  return ' ';
}

songNode* Trie::findSong(string name, string artist)
{
  node* temp = head;
  int child = 0;
  for (int i = 0; i < name.size(); i++)
  {
    child = getNum(name[i]);
    if (temp->children[child] != NULL)
    {
      temp = temp->children[child];
    }
    else
    {
      cout<<"Can't Find Song Returning NULL"<<endl;
      return NULL;
    }
    if (i == name.size()-1)
    {
      if (temp->head != NULL)
      {
        songNode* temp2 = temp->head;
        while (temp2 != NULL)
        {
          if ((temp2->name == name) && (temp2->artist == artist))
          {
            return temp2;
          }
        }
        cout<<"Can't Find Song Returning NULL"<<endl;
        return NULL;
      }
      else
      {
        cout<<"Can't Find Song Returning NULL"<<endl;
        return NULL;
      }
    }
  }
  cout<<"Can't Find Song Returning NULL"<<endl;
  return NULL;
}

void Trie::printTrie()
{
  triePrintHelper(head);
}

node* Trie::gethead()
{
  return head;
}

void Trie::maxchecker(songNode* song)
{
   if (numtop5 < 5)
   {
     top5[numtop5] = song;
     numtop5++;
     return;
   }
   else
   {
     int min = 0;
     for (int i = 0; i < 5; i++)
     {
       if (i != 0)
       {
         if (top5[min]->priorityNum > top5[i]->priorityNum)
         {
           min = i;
         }
       }
     }
     if (top5[min]->priorityNum < song->priorityNum)
     {
       top5[min] = song;
     }
   }
}

void Trie::traversalHelper(node* node)
{
  if (node != NULL)
  {
    bool x = true;
    for (int i = 0; i < 26; i++)
    {
      if (node->children[i] != NULL)
      {
        //cout<<"Calling traversal"<<endl;
        traversalHelper(node->children[i]);
      }
    }
    if (node->head != NULL)
    {
      songNode* temp = node->head;
      while (temp != NULL)
      {
        //cout<<"Calling maxchecker"<<endl;
        maxchecker(temp);
        temp = temp->next;
      }
    }
   }
}

void Trie::printTop5(string name)
{
  for (int p = 0; p < 5; p++)
  {
    top5[p] = NULL;
    numtop5 = 0;
  }
  node* temp = head;
  int child = 0;
  for (int i = 0; i < name.size(); i++)
  {
    child = getNum(name[i]);
    if (temp->children[child] != NULL)
    {
      temp = temp->children[child];
    }
  }
  traversalHelper(temp);
  for (int j = 0; j < 5; j++)
  {
    if (top5[j] != NULL)
    {
      cout<<j+1<<". "<<top5[j]->name<<" by "<<top5[j]->artist<<endl;
    }
  }
}
songNode* Trie::getTop5(int num)
{
  if(num <=4)
  {
    return top5[num];
  }
  else
  {
    cout<<"Invalid Index"<<endl;
  }
}
