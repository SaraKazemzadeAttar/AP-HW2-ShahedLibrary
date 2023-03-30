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

class Book
{
private:
    int bookId;
    string name;
    BookType type;
    Publisher publisher;
    bool isBorrowed;

public:
    static int numOfBooks;

    Book(string name, Publisher publisher, BookType type)
    {
        this->name = name;
        this->publisher = publisher;
        this->type = type;
        numOfBooks++;
        bookId = numOfBooks;
    }
    void showInfo()
    {
        cout << bookId << "." << name;
    }
    string getBookName()
    {
        return name;
    }
    BookType getBookType()
    {
        return type;
    }
    void BorrowBookToMember(Member member)
    {
        if (isBorrowed == false)
        {
            isBorrowed=true;
        }
        else
        {
            throw "This book is borrowed";
        }
    }
};
int Publisher::numOfPublishers = 0;
