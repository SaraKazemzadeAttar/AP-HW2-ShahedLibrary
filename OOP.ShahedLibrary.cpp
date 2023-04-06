#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

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
    string getMemberId()
    {
        return memberIdCode;
    }
    bool isMemberAllowedToBorrow(Book book)
    {
        if (books.size() <= capacityToBorrow)
        {
            if (book.isTheBookBorrowed() == false)
            {
                AddBookToBorrowedBooks(book);
                return true;
            }
            else
            {
                throw "This book has been borrowed";
                return false;
            }
        }
        else
        {
            throw "You are not allowed to borrow more than capacity";
            return false;
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
    static int numOfMembers;

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
    Book getBook(int j)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (i == j)
            {
                return books[i];
            }
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
            if (book.getBookName() == books[i].getBookName())
            {
                throw "There is a book with this name in the library";
            }
        }
        Book newBook(book);
        books.push_back(newBook);
    }
    string getInfoOfBooksOfLib()
    {
        for (int i = 0; i < books.size(); i++)
        {
            return books[i].showInfo();
        }
    }
    vector<Book> listedByType(BookType type)
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
        for (int i = 0; i < Library::numOfMembers; i++)
        {
            if (memberId == members[i].getMemberId())
            {
                throw "This account has been registered";
            }
        }
        Member newMember(name, memberId);
        members.push_back(newMember);
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
    string getAllBooksInfo(int libId)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libId == libraries[i].getLibraryId())
            {
                return libraries[i].getInfoOfBooksOfLib();
            }
        }
        return " ";
    }
    vector<Book> filterByType(int libId, BookType type)
    {
        vector<Book> typeFilter;
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libId == libraries[i].getLibraryId())
            {
                return libraries[i].listedByType(type);
            }
        }
        throw "[]";
    }
    string filterByTypeAndShowInfo(int libId, BookType type)
    {
        string typeFilteredShowInfo = "";
        for (int i = 0; i < libraries.size(); i++) // find library
        {
            if (libId == libraries[i].getLibraryId())
            {
                for (int j = 0; j < libraries[i].listOfBooks().size(); j++) // find the book that has the same type
                {
                    if (type == libraries[i].listOfBooks()[j].getBookType())
                    {
                        typeFilteredShowInfo += to_string(j) + libraries[i].listedByType(type)[j].getBookName() + '\n';
                    }
                }
            }
        }
        return " ";
    }
    bool borrow(string memberId, int libId, string name)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libraries[i].getLibraryId() == libId)
            {
                for (int j = 0; j < members.size(); j++)
                {
                    if (members[i].getMemberId() == memberId)
                    {
                        for (int z = 0; z < libraries[i].listOfBooks().size(); z++)
                        {
                            if (libraries[i].listOfBooks()[z].getBookName() == name)
                            {
                                if (members[i].isMemberAllowedToBorrow(libraries[i].listOfBooks()[z]) == true)
                                bool borrowStatus = true;
                                libraries[i].listOfBooks()[z].setTheStatusOfBook(borrowStatus);
                                return true;
                            }
                            else
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    int size()
    {
        return Library::numOfLibraries;
    }
    vector<Library> listOfLibsHavetheBook(string name)
    {
        vector<Library> libsHaveThisBook;
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libraries[i].isThereThisBook(name) == true)
            {
                libsHaveThisBook.push_back(libraries[i]);
            }
        }
        if (libsHaveThisBook.size() == 0)
        {
            throw "-1";
        }
        return libsHaveThisBook;
    }
    Library findNearestLibraryByPosition(string name, int position)
    {
        listOfLibsHavetheBook(name);
        int left = 0, right = listOfLibsHavetheBook(name).size() - 1;
        while (left < right)
        {
            if (abs(listOfLibsHavetheBook(name)[left].getPosition() - position) <= abs(listOfLibsHavetheBook(name)[right].getPosition() - position))
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return listOfLibsHavetheBook(name)[left];
    }
    string sortLibrariesByDistance(vector<Library> libsHaveThisBook, int position)
    {
        for (int i = 0; i < libsHaveThisBook.size(); i++)
        {
            for (int j = 0; j < libsHaveThisBook.size() - 1; j++)
            {
                if (abs(libsHaveThisBook[j].getPosition()) > abs(libsHaveThisBook[j + 1].getPosition()))
                {
                    swap(libsHaveThisBook[j], libsHaveThisBook[j + 1]);
                }
            }
        }
        string sortedlibsHaveThisBook = "";
        for (int i = 0; i < libsHaveThisBook.size(); i++)
        {
            sortedlibsHaveThisBook += to_string(i) + ". " + libsHaveThisBook[i].getLibraryName() + " " + to_string(libraries[i].getPosition() - position) + '\n';
        }
        return sortedlibsHaveThisBook;
    }
    string findLibrariesHaveBook(string name, int position)
    {
        return sortLibrariesByDistance(listOfLibsHavetheBook(name), position);
    }
};

int Publisher::numOfPublishers = 0;
int Member::capacityToBorrow = 5;
int Book::numOfBooks = 0;
int Library::numOfLibraries = 0;
int Library::numOfMembers = 0;

int main()
{
}
