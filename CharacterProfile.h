/*******************************************************
CharacterProfile.h - Object to store a data on a 
character in the Marvel Character Database
******************************************************/

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#ifndef CHARACTERPROFILE_H
#define CHARACTERPROFILE_H

using namespace std;

class CharacterProfile 
{
  public:
  CharacterProfile(string fileName, int lineNumber);
  
  string name; // Full name of character
  string identity; // If the identity is secret or public
  string alignment; // If the character is good, bad, neutral etc.
  string eyeColor; // Eye color of character
  string hairColor; // Hair color of character
  string sex; // Sex of the character (Male/Female)
  string sexualOrientation; // Sexual orientation of the character
  string living; // If the character is alive or dead
  string numOfAppearances; // Number of comic book appearances
  string firstAppearanceDate; // Month and day of first appearance (Mon-XX; Apr-22)
  string firstAppearanceYear; // Year of first appearance
  string urlSlug; // Extension to wikia url that links to character's webpage
  private:
  //We are not using these variables in our code
  string page_id; 
  
};

#endif