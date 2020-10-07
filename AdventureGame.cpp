#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>


using namespace std;

typedef struct level {
  int id;
  string title;
  string body;
  int choiceCount;
  vector<int> choiceIDs;
  vector<string> choices;
}lvl;



// Separator for 'csv'                                                                               
string separator = ",,";
// Global game_csv is the file to load                                                               
string game_csv = "game.csv";

// load level for int                                                                                
level GotoLevel(int);



int main(int argc, char **argv) {
  
  int nextlevel = 0;

if (argc == 2) {
    game_csv = string(argv[1]);
  }
  for (int i = 1; i < argc; i++) {
    string test_arg = string(argv[i]);
    if (test_arg == "-f") {
      if (argc > i+1) {
	game_csv = string(argv[i+1]);
      }
    }
    if (test_arg == "-l") {
      if (argc > i+1) {
	nextlevel = atoi(argv[i+1]);
      }
    }
  }
  level l = GotoLevel(nextlevel);
  while (l.choiceIDs.size() > 0) {
    cout <<"_____________________________________________" << "\n\n\n" << endl;
    cout << "Page " << l.id << "\n" << endl;
    cout << "                 " << l.title << "\n\n";
    cout << l.body << "\n\n";
    for(int i = 0; i < l.choiceIDs.size();i++) {
      cout << l.choiceIDs[i] << ". " << l.choices[i] << "\n\n";
      
    }
 cin >> nextlevel;
 cout << "\n" << endl;
 if (find(l.choiceIDs.begin(), l.choiceIDs.end(), nextlevel) != l.choiceIDs.end()) {
 l = GotoLevel(nextlevel);
 } else {
   cout << "Invalid page, try again! \n" << endl;
 
  }
}

} 

level GotoLevel(int num) {
  // Read file, from the global game_csv converted to a C string (const char array)                  
  
  fstream file(game_csv.c_str());
  // Go to the beginning of the file                                                                 
  file.seekg(ios::beg);
  // skip to the line we want                                                                        
  for(int i = 0; i < num; i++) {
    // ignore the crap we don't want                                                                 
    file.ignore(numeric_limits<streamsize>::max(),'\n');
  }
  // make a new level                                                                                
  level l;
  // make a new line                                                                                 
  string line;
  // read what we have from the file, to the string line                                             
  getline(file, line);

  //LevelID,Title,Body,ChoiceCount,ChoiceID1,....ChoiceIDN,Choice1,....ChoiceN                       
  l.id = atoi(line.substr(0, line.find(separator)).c_str());
  line.erase(0, line.find(separator) + separator.length());

  l.title = line.substr(0, line.find(separator));
  line.erase(0, line.find(separator) + separator.length());;

  l.body = line.substr(0, line.find(separator));
  line.erase(0, line.find(separator) + separator.length());

  l.choiceCount = atoi(line.substr(0, line.find(separator)).c_str());
  line.erase(0, line.find(separator) + separator.length());

  for(int i = 0; i < l.choiceCount; i++) {
    int choice = atoi(line.substr(0, line.find(separator)).c_str());
    l.choiceIDs.push_back(choice);
    line.erase(0, line.find(separator) + separator.length());
  }
  for(int i = 0; i < l.choiceCount; i++) {
    string choice = line.substr(0, line.find(separator));
    l.choices.push_back(choice);
    line.erase(0, line.find(separator) + separator.length());
  }
  return l;


}
