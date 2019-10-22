/*******************************************************
  NameMap.cpp - Object to store a map of all names and 
  the line numbers in the the file where the names 
  appear. It allows insertion and looking up of
  names and their location in the file.
 ******************************************************/
#include "CharacterNameMap.h"

//This is Ryan's second comment for the github lab. This is still a great class!
/*GITHUB Comment 1
WOW! What a great class!*/

/*
Creates a character name map.
Maps each name to a vector of file indices (File lines) 
like an inverted index.
e.g. John will be mapped to a vector of all the line numbers
containing the name John.

@param  fileName  Name of the data file to be read in order 
to create the map.
*/
CharacterNameMap::CharacterNameMap(string fileName)
{
  string name; // Each name component to be searched for
  string line; // Holds the rest of the data in the line that we aren't concerned about 
  string page_id; // Data at the beginning of the line, not relevant to mapping names 
  string fullName; // The full name to be searched for and parsed into name components
  
  ifstream infile;
  //filename="/home/class/SoftDev/marvel/marvel-wikia-data.csv";
  infile.open(fileName);
  
  int position = 1;
  /* If the file can be opened do the following code, 
  else report that name map creation did not succeed */
  if(infile.good())
  {
	getline(infile, line); // Store first line in database which does not give character data
    /* Keep going until we reach the end of the file */
    while(true)
    {
      //Gets full name from the datafile
      char delimiter = ',';
      getline(infile, page_id, delimiter);
      getline(infile, fullName, delimiter);
        //cout << "Full:" << fullName <<  endl;

      //Copies "fullName" string into a character array "characterData"
      char characterData[fullName.size() +1];
      strcpy(characterData, fullName.c_str());

      //Maps name components to their position in the file
      char delims[] = " ()\"";
      char * name;
      name = strtok(characterData, delims);
      while(name != NULL)
      {
          //cout << name << endl;
        nameMap[name].push_back(position);
        name = strtok(NULL, delims);
      }
      
      //Moves scanner to the end of the line
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
bool CharacterNameMap::nameMapSuccess()
{
  return success;
}


/*
Creates a vector of character profiles that match the name searched for by the user.

@param  string selectedName The name of the character being searched for
@param  CharacterNameMap nameMap  Name map mapping name to lines in the file containing that name
@return vector<CharacterProfile>  Vector containing a character profile for each character that matches the name searched
*/
vector<CharacterProfile> CharacterNameMap::createCharacterList(string selectedName, string fileName)
{
  vector<int> characterIndecies = getCharacterIndecies(selectedName);
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
vector<int> CharacterNameMap::getCharacterIndecies(string confirmedName)
{
  vector<int> profileLocations; // Create int vector to hold profile locations
  profileLocations = nameMap.at(confirmedName); //Set our new vector to the value of the vector in our map, mapped from the name "confirmedName".

  return profileLocations; // Return all locations of characters with the name "confirmedName"
}

