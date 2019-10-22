/*******************************************************
CharacterNameMap.h - Object to store a map of all names 
and the lines in the data file that name appears on.
******************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string.h>
#include <string>
#include <stdio.h>
#include "CharacterProfile.h"

using namespace std;

class CharacterNameMap 
{
  public:
    CharacterNameMap(string fileName);
    bool nameMapSuccess();
	vector<CharacterProfile> createCharacterList(string selectedName, string fileName);

  private:
    map< string, vector<int> > nameMap;
    bool success;
    void mapNameToPosition(char characterName[], int position);
	vector<int> getCharacterIndecies(string confirmedName);
};
