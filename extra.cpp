#include <iostream>
#include <cstdlib>

#include "extra.h"
#include "page.h"

//forces the user to type a number between 1 and maxnum.

int getnumber(int maxnum){
    int num;
    std::string typed;
    while(1){
        std::cin >> typed;
        num = atoi(typed.c_str());
        if(num >= 1 && num <= maxnum){
            return num;
        }
        else{
            std::cout << "Please type a number between 1 and " << maxnum << "." << std::endl;
        }
    }
}

//starts the game at the specified page.

void startgame(std::string wheretostart){
    int choicenum;
    Page::verify();
    Page *p = Page::search(wheretostart);
    while(1){
        p->visit();
        //if no choices, game ends
        if(p->choicecount == 0){
            return;
        }
        //automatically jump to next page
        if(p->nextpage != ""){
            p = Page::search(p->nextpage);
            continue;
        }
        //otherwise print out the choices
        choicenum = getnumber(p->choicecount);
        p = p->getchoice(choicenum);
    }
}
