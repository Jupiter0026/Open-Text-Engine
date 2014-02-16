#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "page.h"

std::string strip(std::string s){
    size_t start = s.find_first_not_of (" \t");
    size_t end = s.find_last_not_of (" \t");
    s.erase (0, start);
    if(end+1 < s.length()){
        s.erase (end+1, std::string::npos);
    }

    return s;
}

void parse(std::string filename){
    Page *p = NULL;
    std::string line;
    std::ifstream gamefile(filename.c_str());

    if(!gamefile.is_open()){
        std::cout << "Specified file does not exist: " << filename << "." << std::endl;
        exit(1);
    }

    while(getline(gamefile, line)){
        if(!line.length()){
            //This line is empty
            //A new line needs to be added to the description.
            if(!p){
                std::cout << "Found blank Content Text before first @addpage." << std::endl;
                exit(1);
            }
            else{
                p->appendcontent("\n");
            }
        }
        else if(line.at(0) == '@'){
            //This line is a command
            size_t start = 1;
            size_t end = line.find(' ');
            std::string command = line.substr(start, end-start);
            if(command == "addpage"){
                //Create a new page here
                start = end+1;
                end = line.find('|', start);
                std::string pagename = strip(line.substr(start, end-start));
                //testing purposes: std::cout << "Adding page: '" << pagename << "'" << std::endl;
                if(p){
                    p->clean();
                }
                p = new Page(pagename);
            }
            else if(command == "addchoice"){
                if(!p){
                    std::cout << "Found @addchoice before first @addpage." << std::endl;
                    exit(1);
                }
                start = end+1;
                end = line.find('|', start);
                std::string description = strip(line.substr(start, end-start));
                //testing purposes: std::cout << "Description: '" << description << "'" << std::endl;

                start = end+1;
                end = line.find('|', start);
                std::string destination = strip(line.substr(start, end-start));

                //testing purposes: std::cout << "Name: " << destination << std::endl;

                p->addchoice(description, destination);
            }
            else{
                std::cout << "Unknown command: '" << command << "'" << std::endl;
                exit(1);
            }
            if(end != std::string::npos){
                //There was something at the end of the line
                std::cout << "Unexpected content at end of line: " << line.substr(end) << std::endl;
                exit(1);
            }
        }
        else if(line.at(0) == '!'){
            //This is a comment
        }
        else{
            //This is Content Text
            if(!p){
                std::cout << "Found Content Text before first @addpage." << std::endl;
                exit(1);
            }
            p->appendcontent(line);
            p->appendcontent("\n");
        }
    }
    gamefile.close();
}

