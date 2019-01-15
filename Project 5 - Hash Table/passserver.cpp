#include "passserver.h"
#include "hashtable.h"
#include <iostream>
#include <utility>
#include <unistd.h>
#include <crypt.h>
#include <string>
#include <cstring>

using namespace std;
using namespace cop4530;


PassServer::PassServer(size_t size)
{
    userPassHash.forceHTSize(size);
}

PassServer::~PassServer()
{
    userPassHash.clear();
}

bool PassServer::load(const char *filename)
{
    return userPassHash.load(filename);
}

bool PassServer::load(const string filename)                // Used to parse string to cstring for loader
{
    return load(filename.c_str());
}

bool PassServer::addUser(std::pair<string,  string> & kv)
{
    pair<string,string>encryption(kv.first, encrypt(kv.second));
    return userPassHash.insert(encryption);
}

bool PassServer::addUser(std::pair<string, string> && kv)
{
    pair<string,string> copyOf(kv.first,kv.second);
    return addUser(kv);
}

bool PassServer::removeUser(const string & k)
{
    return userPassHash.remove(k);
}

bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
    pair<string,string> oldPairEncrypted(p.first,encrypt(p.second));
    pair<string,string> newPairEncrypted(p.first,encrypt(newpassword));

    if(oldPairEncrypted.second == newPairEncrypted.second || !userPassHash.contains(oldPairEncrypted.first) || !userPassHash.match(oldPairEncrypted)) // This last condition eventually will need to be encrypted
        return false;
    else
    {
        userPassHash.insert(newPairEncrypted);         // Uses insert's "update value from key if different" property
        return true;
    }
}

bool PassServer::find(const string & user)
{
    return userPassHash.contains(user);
}

void PassServer::dump()
{
    userPassHash.dump();
}

size_t PassServer::size()
{
    return userPassHash.size();
}

bool PassServer::write_to_file(const char *filename)
{
    return userPassHash.write_to_file(filename);
}

bool PassServer::write_to_file(const string filename)           // Used to parse string to cstring for writer
{
    return write_to_file(filename.c_str());
}


string PassServer::encrypt(const string & str)
{
    char salt [] = "$1$########";
    string encrypted = crypt(str.c_str(), salt);
    return encrypted.substr(12);                  // Trim off salt
}
