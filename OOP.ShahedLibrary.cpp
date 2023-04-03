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
    string showInfo()
    {
        string str = bookId + "." + name;
        return str;
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
    vector<Book> searchByType(BookType type)
    {
        vector<Book> typeOrganised;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getBookType() == type)
            {
                typeOrganised.push_back(books[i]);
            }
        }
        return typeOrganised;
    }
    bool isThereThisBook(string name)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getBookName() == name)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};

class LibrariesHandler
{
private:
    vector<Library> libraries;
    vector<Member> members;

public:
    void createLibrary(string name, int position)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libraries[i].getLibraryName() == name)
            {
                throw "A library with this name already exists";
            }
            else if (libraries[i].getPosition() == position)
            {
                throw "There is now a library in this place";
            }
            else
            {
                Library newLibrary(name, position);
                libraries.push_back(newLibrary);
            }
        }
    }
    void addBook(int libId, string name, Publisher publisher, BookType type)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libId == libraries[i].getLibraryId())
            {
                libraries[i].addBook(Book(name, publisher, type));
            }
        }
        throw "This library id is not available ";
    }
    void addBook(int libId, Book book)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libId == libraries[i].getLibraryId())
            {
                libraries[i].addBook(book);
            }
        }
        throw "This library id is not available ";
    }
    void addMember(string name, string memberId)
    {
        for (int i = 0; i < Library::numOfMembers; i++)//?
        {
            if (memberId != members[i].getMemberId())
            {
                Member newMember(name, memberId);
                members.push_back(newMember);
            }
            else
            {
                throw "This account has been registered";
            }
        }
    }
    vector<Book> getAllBooks(int libId)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libraries[i].getLibraryId() == libId)
            {
                return libraries[i].listOfBooks();
            }
        }
        throw "[]";
    }
};

int Publisher::numOfPublishers = 0;
