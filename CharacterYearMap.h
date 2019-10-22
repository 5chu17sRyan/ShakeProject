/*******************************************************
CharacterYearMap.h - Object to store a map of all years 
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

class CharacterYearMap 
{
  public:
    CharacterYearMap(string fileName);
    bool yearMapSuccess();
	vector<CharacterProfile> createCharacterList(string year, string fileName);

  private:
    map< string, vector<int> > yearMap;
    bool success;
	vector<int> getCharacterIndecies(string year);
};