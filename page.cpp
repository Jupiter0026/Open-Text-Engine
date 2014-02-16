#include <iostream>
#include <cstdlib>

#include "page.h"

int Page::count = 0;
Page *Page::allpages[];

//creates a page and adds it to the allpages array.

Page::Page(std::string name){
    if(Page::count >= MAXPAGES){
        std::cout << "Maximum pages exceeded. Crashing." << std::endl;
        exit(1);
    }
    this->name = name;
    this->content = "";
    this->choicecount = 0;
    this->nextpage = "";
    this->varcount = 0;
    allpages[Page::count] = this;
    Page::count++;
}

//xxx why do we have 2 constructors?

Page::Page(std::string name, std::string content){
    if(Page::count >= MAXPAGES){
        std::cout << "Maximum pages exceeded. Crashing." << std::endl;
        exit(1);
    }
    this->name = name;
    this->content = content;
    this->choicecount = 0;
    this->nextpage = "";
    this->varcount = 0;
    allpages[Page::count] = this;
    Page::count++;
}

//This searches the pages for a specific name.

Page *Page::search(std::string name){
    for(int i = 0;i < Page::count;i++){
        if(allpages[i]->name == name){
            return allpages[i];
        }
    }
    std::cout << "Page not found: '" << name << "'. Crashing." << std::endl;
    exit(1);
}

//ensures all pages referred to exist.

void Page::verify(){
    for(int i = 0;i < Page::count;i++){
        Page *p = allpages[i];
        for(int j = 0;j < p->choicecount;j++){
            Page::search(p->allchoices[j].destination);
        }
    }
}

//adds choices.

void Page::addchoice(std::string description, std::string destination){
    if(this->choicecount > MAXCHOICES){
        std::cout << "Maximum choices exceeded. Crashing." << std::endl;
        exit(1);
    }
    this->allchoices[this->choicecount].description = description;
    this->allchoices[this->choicecount].destination = destination;
    this->choicecount++;
}

Page *Page::getchoice(int choicenum){
    return Page::search(this->allchoices[choicenum-1].destination);
}

void Page::after(std::string nextpage){
    this->nextpage = nextpage;
}

void Page::appendcontent(std::string content){
    this->content+=content;

}

void Page::setvariable(std::string name, int value){
    int i;
    for(i = 0; i < this->varcount; i++){
        if(this->varnames[i] == name){
            //We found it
            this->varvalues[i] = value;
        }
    }
    this->varnames[i] = name;
    this->varvalues[i] = value;
    this->varcount++;
}

int Page::getvariable(std::string name){
    int i;
    for(i = 0; i < this->varcount; i++){
        if(this->varnames[i] == name){
            //We found it
            return this->varvalues[i];
        }
    }
    std::cout << "Variable not found: " << name << ". Crashing." << std::endl;
    exit(1);
}

void Page::visit(){
    std::cout << this->content << std::endl;
    for(int i = 0;i < this->choicecount;i++){
        std::cout << this->allchoices[i].description << " press " << i+1 << "." << std::endl;
    }
}

//better line wrapping, so it doesn't cut off a word between lines
//add functionality for author to color text at will
//add functionality so the author can change the console size, or size in general
//for later: custom current placement in scroll. for instance, if you've got a long Content Text, allow it to start a top. or esle?

void Page::clean(){
    size_t end = this->content.find_last_not_of ("\n");
    if(end+2 < this->content.length()){
        this->content.erase(end+2);
    }
}
