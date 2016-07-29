#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// get file contents
string getFileContents (ifstream&);          

int main(int argc, char *argv[])
{
    // open file with file path
    ifstream Title ("graphics/title.txt");

    // get file contents and place into ART
    string OpeningTitle = getFileContents (Title);
    
    //print contents to screen
    cout << OpeningTitle << endl;               

    // close file
    Title.close ();
    
    ifstream Space ("graphics/spaceship1.txt");
    string SpaceShip = getFileContents (Space);
    cout << SpaceShip << endl;               
    Space.close ();  

    string Title2 = "   _____                         _____ _        _   _ \n  / ____|                       / ____| |      | | (_)         \n | (___  _ __   __ _  ___ ___  | (___ | |_ __ _| |_ _  ___  _ __ \n  \\___ \\| '_ \\ / _` |/ __/ _ \\  \\___ \\| __/ _` | __| |/ _ \\| '_ \\ \n  ____) | |_) | (_| | (_|  __/  ____) | || (_| | |_| | (_) | | | | \n |_____/| .__/ \\__,_|\\___\\___| |_____/ \\__\\__,_|\\__|_|\\___/|_| |_| \n        | |       _  _   _  _   _  _   _  _                        \n        |_|      | || | | || | | || | | || |                      \n                 | || |_| || |_| || |_| || |_                     \n                 |__   _|__   _|__   _|__   _|                    \n                    | |    | |    | |    | |                      \n                    |_|    |_|    |_|    |_|";
    cout << Title2 << endl;
    
    return 0;
}

string getFileContents (ifstream& File)
{
    // all lines into string
    string Lines = "";        
    
    // while file exists
    if (File)                      
    {
	while (File.good ())
	{
	    string TempLine;                  
	    getline (File , TempLine);        
	    TempLine += "\n";                      
	    
	    Lines += TempLine;     
	}
	return Lines;
    }
    
    // if no file exists
    else                        
    {
	return "ERROR FILE DOES NOT EXIST";
    }
}