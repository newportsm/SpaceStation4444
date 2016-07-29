#include <iostream>
#include <fstream>
#include <string>

// get file contents
std::string getFileContents (std::ifstream&);          

int main(int argc, char *argv[])
{
    // open file with file path
    std::ifstream Reader ("graphics/title.txt");            

    // get file contents and place into ART
    std::string Art = getFileContents (Reader);
    
    //print contents to screen
    std::cout << Art << std::endl;               

    // close file
    Reader.close ();                    

    return 0;
}

std::string getFileContents (std::ifstream& File)
{
    // all lines into string
    std::string Lines = "";        
    
    // while file exists
    if (File)                      
    {
	while (File.good ())
	{
	    std::string TempLine;                  
	    std::getline (File , TempLine);        
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