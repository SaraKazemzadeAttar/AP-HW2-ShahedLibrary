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

    Publisher()
    {
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
            isBorrowed = true;
        }
        else
        {
            throw "This book is borrowed";
        }
    }
};

class Member
{
private:
    string memberIdCode;
    string name;
    vector<Book> books;

public:
    static int capacityToBorrow;
    Member(string id, string name)
    {
        memberIdCode = id;
        this->name = name;
    }
    void getBookFromMember(Book book)
    {
        if (books.size() <= capacityToBorrow)
        {
            books.push_back(book);
        }
        else
        {
            throw "You are not allowed to borrow more than capacity";
        }
    }
};
class Library
{
private:
    int libId;
    string name;
    vector<Book> books;
    int position;

public:
    static int numOfLibraries;

    Library(string name, int position)
    {
        this->name = name;
        this->position = position;
        numOfLibraries++;
        libId = numOfLibraries;
    }
    string getLibraryName()
    {
        return name;
    }
    int getLibraryId()
    {
        return libId;
    }
    int getPosition()
    {
        return position;
    }
    vector<Book> listOfBooks()
    {
        return books;
    }
    Book getBook()
    {
        for (int i = 0; i < books.size(); i++)
        {
            return books[i];
        }
    }
    Book searchByName(string name)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (name == books[i].getBookName())
            {
                return books[i];
            }
        }
        throw "This book is not in this library";
    }
    void addBook(Book book)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (book.getBookName() != books[i].getBookName())
            {
                Book newBook(book);
                books.push_back(newBook);
            }
        }
    }
    string getInfoOfBooksOfLib()
    {
        for (int i = 0; i < books.size(); i++)
        {
            return books[i].showInfo();
        }
    }
};

int Publisher::numOfPublishers = 0;
