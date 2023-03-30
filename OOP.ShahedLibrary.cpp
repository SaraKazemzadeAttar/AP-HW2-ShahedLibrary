#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

enum BookType
{
    SCIENTIFIC,
    CRIME,
    FANTASY,
    HORROR,
    CLASSICS,
};

class Publisher
{
private:
    int publisherId;
    string name;
    string location;

public:
    static int numOfPublishers;

    Publisher(string name, string location)
    {
        this->name = name;
        this->location = location;
        numOfPublishers++;
        publisherId = numOfPublishers;
    }

    string getPublisherName()
    {
        return name;
    }
    
};
int Publisher::numOfPublishers = 0;
