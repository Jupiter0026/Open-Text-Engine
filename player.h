#include <string>

typedef struct inventoryitem_s{
    std::string name;
    struct inventoryitem_s *next;
}inventoryitem;

//defines what a player is.

class Player{

    public:

    std::string name;
    std::string bio;
    int age;
    inventoryitem *inventory;

    Player(std::string name, std::string bio, int age);
    void inventoryadd(std::string name);
    void inventoryremove(std::string name);
    inventoryitem *inventorysearch(std::string name);
};
