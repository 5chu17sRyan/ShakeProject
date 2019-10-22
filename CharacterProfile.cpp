/*******************************************************
CharacterProfile.cpp - Object to store a data on a 
character in the Marvel Character Database. Gets
character data from lines containing the name of the 
character.
******************************************************/

#include "CharacterProfile.h"


/*
Creates a profile with data about a marvel character.
Data is read from the file "fileName" at the position "lineNumber".

@param  string fileName Data is read from the file "fileName"
@param  int lineNumber  Data is read starting at position "lineNumber" in the file "fileName"
*/
CharacterProfile::CharacterProfile(string fileName, int lineNumber)
{
  ifstream infile;
  infile.open(fileName); // Set file input stream to "fileName"
  infile.seekg(lineNumber, infile.beg); // Set position of beginning of stream to "lineNumber"

  string profileData; // String containing all character profile data
  getline(infile, profileData); // Store line with all character data into profileData
  istringstream characterStream(profileData); // Create string stream 

  /* Parses string stream by comma deliminator, 
  stores each datum in its respective variable */
  getline(characterStream, page_id, ',');
  getline(characterStream, name, ',');
  getline(characterStream, urlSlug, ',');
  getline(characterStream, identity, ',');
  getline(characterStream, alignment, ',');
  getline(characterStream, eyeColor, ',');
  getline(characterStream, hairColor, ',');
  getline(characterStream, sex, ',');
  getline(characterStream, sexualOrientation, ',');
  getline(characterStream, living, ',');
  getline(characterStream, numOfAppearances, ',');
  getline(characterStream, firstAppearanceDate, ',');
  getline(characterStream, firstAppearanceYear, ',');
}