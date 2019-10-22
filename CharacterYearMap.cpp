/*******************************************************
  CharacterYearMap.cpp - Object to store a map of all names and 
  the line numbers in the the file where the names 
  appear. It allows insertion and looking up of
  names and their location in the file.
 ******************************************************/
#include "CharacterYearMap.h"


/*
Creates a character year map.
Maps each year to a vector of file indices (File lines) 
like an inverted index.
e.g. 1984 will be mapped to a vector of all the line numbers
containing the name 1984.

@param  fileName  Name of the data file to be read in order 
to create the map.
*/
CharacterYearMap::CharacterYearMap(string fileName)
{
  ifstream infile;
  infile.open(fileName);
  
  int position = 1; //Skip first line (line 0)
  string line;
  /* If the file can be opened do the following code, 
  else report that name map creation did not succeed */
  
  if(infile.good())
  {
    getline(infile, line); //Skipping line	  
    /* Keep going until we reach the end of the file */
    while(true)
    {
      //Parses line
      char delimiter = ',';
      string junk; // Data at the beginning of the line, not relevant to mapping the year
      for(int i = 0; i < 12; i++)
      {
        getline(infile, junk, delimiter);
      }
      string year;
      infile >> year;
      //cout << "Year: " << year << endl;
      yearMap[year].push_back(position);
      getline(infile, line);


      //If we reach the end of the file exit the loop
      if(infile.fail())
      {
        break;
      }
      position = infile.tellg(); //Get the position of the next line (Get the line number)
    }
    infile.close(); // Close the file
    success = true; // Report that map creation was a success
  }
  else
  {
    success = false; 
  }
}



/*
Checks if map creation for CharacterNameMap was a success and returns
value as a boolean.

@return bool success  Whether or not the map creation was a success
*/
bool CharacterYearMap::yearMapSuccess()
{
  return success;
}



/*
Creates a vector of character profiles that match the year searched for by the user.

@param  string year The year of first appearance of the character being searched for
@param  CharacterYearMap yearMap  Year map mapping year of first appearance to lines in the file containing that year
@return vector<CharacterProfile>  Vector containing a character profile for each character that matches the year searched
*/
vector<CharacterProfile> CharacterYearMap::createCharacterList(string year, string fileName)
{
  vector<int> characterIndecies = getCharacterIndecies(year);
  vector<CharacterProfile> characterMatches;
  for(int i = 0; i < characterIndecies.size(); i++)
  {
    CharacterProfile newCharacter = CharacterProfile(fileName, characterIndecies.at(i));
    characterMatches.push_back(newCharacter);
  }
  return characterMatches;
}


/*
Gets the characters that correspond to the name searched for. 
Uses the CharacterNameMap to lookup the vector of line numbers that reference the character's name.
Each line contains all of the information in a character's profile.

@param  string characterName  The name of the the character that the user wants to lookup.
We use getNameMatches() to make sure the name the user inputs exists if not they are allowed to choose the closest one. 
  Prevents program errors due to user errors typos
@return vector<int> profileLocations  The list of line locations for character profiles/data that contain the name searched for.
*/
vector<int> CharacterYearMap::getCharacterIndecies(string year)
{
  vector<int> profileLocations; // Create int vector to hold profile locations
  profileLocations = yearMap.at(year); //Set our new vector to the value of the vector in our map, mapped from the name "confirmedName".

  return profileLocations; // Return all locations of characters with the name "confirmedName"
}