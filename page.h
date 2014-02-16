#include <string>

#define MAXCHOICES 9
#define MAXVARS 9
#define MAXPAGES 64

//a choice is a path between pages.

typedef struct{
    std::string description;
    std::string destination;
}choice;

//defines what a new page has in it.

class Page{

    public:

    //This is the maximum amount of pages your game may contain.

    static Page *allpages[MAXPAGES];
    static int count; //measures how many pages are in the array.

    std::string name;
    std::string content;
    std::string nextpage;

    choice allchoices[MAXCHOICES];
    int choicecount;

    std::string varnames[];
    int varvalues[];
    int varcount;

    Page(std::string name);
    Page(std::string name, std::string content);
    static Page *search(std::string name);
    static void verify();
    void addchoice(std::string description, std::string destination);
    Page *getchoice(int choicenum);
    void after(std::string nextpage);
    void appendcontent(std::string content);

    void setvariable(std::string name, int value);
    int getvariable(std::string name);

    virtual void visit();
    void clean();
};
