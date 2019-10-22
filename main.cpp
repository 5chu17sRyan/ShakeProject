/***************************************************************************                   
 * namelookup.cpp  -  Program to display name statistics                                       
 *                                                                                             
 * copyright : (C) 2017 by Jim Skon                                                            
 *                                                                            
 * This program create an index US Census name                                       
 * Data on the frequency of names in response to requestes.                           
 * It then allows you to look up any name, giving the 10 closest matches               
 *                                                            
 *     
 *
 ***************************************************************************/
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "CharacterProfile.h"
#include "CharacterNameMap.h"
#include "CharacterYearMap.h"
#include <string>
#include "fifo.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


using namespace std;

/* Fifo names */
string receive_fifo = "Namerequest";
string send_fifo = "Namereply";

// File name for marvel data
const string fileName = "/home/class/SoftDev/marvel/marvel-wikia-data.csv";

void sendResults(vector<CharacterProfile> matchList, string &outMessage);

int main() {

  string inMessage, outMessage,search,type;
  int pos;
  
  // Build the name maps
  CharacterNameMap nameMap(fileName); 
  CharacterYearMap yearMap(fileName);
  vector<CharacterProfile> matchList; // place to stare the file locations of the matches
  
  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    inMessage = recfifo.recv();
    /* Parse the incoming message */
    /* Form:  $type*name  */
    pos=inMessage.find_first_of("*");
    if (pos!=string::npos) {
      type = inMessage.substr(0,pos);
      pos++;
    } else {
      type = "$Year";
      pos = 0;
    }
    search = inMessage.substr(pos,2000);
    cout << "Message: " << type << " : " << search << endl;
 
   if (type=="$Year") {
      matchList = yearMap.createCharacterList(search, fileName);
    } else if (type=="$Name"){
      matchList = nameMap.createCharacterList(search, fileName);
	}

    outMessage = "";
    sendResults(matchList, outMessage);

    cout << " Results: " << outMessage << endl;

    sendfifo.openwrite();
    sendfifo.send(outMessage);
    sendfifo.fifoclose();
    recfifo.fifoclose();
  }
  
return 0;
}


/*
Prints out character information. Data is used by namelookup.js. See the js function getMatches()

@param		vector<CharacterProfile>	matchList	List of character profiles that match the search. 
Data from each profile is printed 
@return		void

*/
void sendResults(vector<CharacterProfile> matchList, string &outMessage)
{
	for (int i = 0; i < matchList.size(); i++) {
		
		outMessage += matchList.at(i).name + "," + matchList.at(i).identity + "," + matchList.at(i).alignment + ",";
		outMessage += matchList.at(i).eyeColor + "," + matchList.at(i).hairColor + "," + matchList.at(i).sex + ",";
		outMessage += matchList.at(i).sexualOrientation + "," + matchList.at(i).living + ",";
		outMessage += matchList.at(i).numOfAppearances + "," + matchList.at(i).firstAppearanceDate + ",";
		outMessage += matchList.at(i).firstAppearanceYear + "," + matchList.at(i).urlSlug;
		
		if (i<matchList.size()-1)
		{
			outMessage += ","; // Only put out this comma if not last entry.
		}
		
	}
}


