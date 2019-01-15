#include "passserver.h"
#include "hashtable.h"
#include <curses.h>
#include <iostream>

using namespace std;

void Menu();
string customGetLine();
string hiddenGetLine();

int main()
{
    char selection = ' ';
    int reqSize;

    cout << "Enter preferred hash table capacity: ";
    cin >> reqSize;

    if (reqSize > 1301081)
    {
        cerr << "** input too large for prime_below()\n";
        cerr << "set to default capacity" << endl << endl;
        reqSize = 11;
    }
    else if (reqSize <= 1)
    {
        cerr << "** input too small \n";
        cerr << "set to default capacity" << endl << endl;
        reqSize = 11;
    }

    cout << reqSize << endl;

    PassServer SERVER (reqSize);

    Menu();

    while(selection != 'x')
    {
        cin >> selection;

        if(selection == 'l')
        {
            string infile;

            cout << "Enter password file name to load from: ";

            infile = customGetLine();

            if(SERVER.load(infile))
            {
                cout << "File '" << infile << "' loaded sucessfully." << endl;
            }
            else
                cout << "Error: Cannot open file " << infile << endl;
        }
        else if(selection == 'a')
        {
            string user;
            string pass;

            cout << "Enter a username: ";

            user = customGetLine();

            // Support for Usernames With Spaces (Corrects to _)
            for(int i = 0; i < user.length(); i++)
            {
                if(user[i] == ' ')
                  user[i] = '_';
            }

            cout << "Enter a password: " << endl;
            pass = hiddenGetLine();

            cout << endl;

            if(!SERVER.find(user))
            {
                SERVER.addUser(pair<string,string>(user,pass));
                cout << "User " << user << " added." << endl;
            }

            else
                cout << "*****Error: User already exists. Could not add user." << endl;
        }
        else if(selection == 'r')
        {
            string user;

            cout << "Enter username: ";

            user = customGetLine();

            // Support for Usernames With Spaces (Corrects to _)
            for(int i = 0; i < user.length(); i++)
            {
                if(user[i] == ' ')
                  user[i] = '_';
            }

            cout << endl;

            if(SERVER.removeUser(user))
                cout << "User " << user << " deleted." << endl;
            else
                cout << "*****Error: "<< user << " not found.  Could not delete user" << endl;
        }
        else if(selection == 'c')
        {
            string user;
            string pass;
            string newpass;

            cout << "Enter username: ";

            user = customGetLine();

            // Support for Usernames With Spaces (Corrects to _)
            for(int i = 0; i < user.length(); i++)
            {
                if(user[i] == ' ')
                  user[i] = '_';
            }

            cout << "Enter a password: " << endl;
            pass = hiddenGetLine();

            cout << "Enter new password: " << endl;

            newpass = hiddenGetLine();

            cout << endl;

            if(SERVER.changePassword(pair<string,string>(user,pass), newpass))
                cout << "Password changed for user " << user << endl;
            else
                cout << "*****Error: Could not change user password" << endl;
        }
        else if(selection == 'f')
        {
            string user;

            cout << "Enter username: ";

            user = customGetLine();

            // Support for Usernames With Spaces (Corrects to _)
            for(int i = 0; i < user.length(); i++)
            {
                if(user[i] == ' ')
                  user[i] = '_';
            }

            cout << endl << "User '"<< user;

            if(SERVER.find(user))
                cout << "' found. ";
            else
                cout << "' not found.";
        }
        else if(selection == 'd')
        {
            SERVER.dump();
        }
        else if(selection == 's')
        {
            cout << "Size of hashtable: " << SERVER.size();
        }
        else if(selection == 'w')
        {
            string outfile;

            cout << "Enter password file name to write to: ";

            outfile = customGetLine();

            if(SERVER.write_to_file(outfile))
            {
                cout << "File '" << outfile << "' saved sucessfully." << endl;
            }
            else
                cout << "Error: Cannot save file " << outfile << endl;
        }
        else if(selection == 'x')
        {
            break;
        }
        else
        {
            cout << endl <<  "*****Error: Invalid entry.  Try again." << endl << endl << endl;
            Menu();
        }
        Menu();
    }

    return 0;
}

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

string customGetLine()
{
  string returnString;

  while(isspace(cin.peek())&&!cin.eof())
      cin.get();

  getline(cin, returnString);

  return returnString;
}

string hiddenGetLine()
{
  char cpass[64];
  initscr();
  noecho();

  getstr(cpass);

  string returnString(cpass);

  echo();
  endwin();
  return returnString;
}
