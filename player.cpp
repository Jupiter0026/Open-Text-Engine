#include <iostream>
#include <cstdlib>
#include "player.h"

//creates a player with information from the keyboard.

Player::Player(std::string name, std::string bio, int age){
    this->name = name;
    this->bio = bio;
    this->age = age;
    this->inventory = NULL;
}

//adds a new item to the inventory

void Player::inventoryadd(std::string name){
    inventoryitem *newitem;
    newitem = new inventoryitem;
    newitem->name = name;
    newitem->next = this->inventory;
    this->inventory = newitem;
}

//removes an item from the inventory

void Player::inventoryremove(std::string name){
    inventoryitem *i = this->inventory;
    inventoryitem *last;
    if(this->inventory && this->inventory->name == name){
        i = this->inventory;
        this->inventory = this->inventory->next;
        delete i;
        return;
    }
    i = this->inventory->next;
    last = this->inventory;
    while(i != NULL){
        if(i->name == name){
            last->next = i->next;
            delete i;
            return;
        }
        last = last->next;
        i = i->next;
    }
    return;
}

//searches the inventory for a specific named item.

inventoryitem *Player::inventorysearch(std::string name){
    inventoryitem *i = this->inventory;
    while(i != NULL){
        if(i->name == name){
            return i;
        }
        i = i->next;
    }
    return NULL;
}
