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
        string str = to_string(bookId) + ". " + name;
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
    void setTheBorrowStatusOfBook(bool BorrowStatus)
    {
        if (BorrowStatus == false)
        {
            isBorrowed = false;
        }
        else
        {
            isBorrowed = true;
        }
    }
    bool isTheBookBorrowed()
    {
        if (isBorrowed == false)
        {
            return false;
        }
        else
        {
            return true;
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
    void AddBookToBorrowedBooks(Book book)
    {
        books.push_back(book);
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
    bool returnBookFromMember(Book book)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getBookName() == book.getBookName())
            {
                books.erase(books.begin() + i);
                return true;
            }
        }
        throw "This book has not been borrowed";
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
    string showInfoOfLib()
    {
        string str = to_string(libId) + ". " + name;
        return str;
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
        string infoOfallBooks="";
        for (int i = 0; i < books.size(); i++)
        {
            infoOfallBooks+=books[i].showInfo() +'\n';
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
            if (libraries[i].getLibraryId() == libId)
            {
                for (int j = 0; j < libraries[i].listOfBooks().size(); j++)
                {
                    if (libraries[i].listOfBooks()[j].getBookName() == name)
                    {
                        throw "This library already has this Book";
                    }
                }
                libraries[i].addBook(Book(name, publisher, type));
            }
        }
    }
    void addBook(int libId, Book book)
    {
        for (int i = 0; i < libraries.size(); i++)
        {
            if (libraries[i].getLibraryId() == libId)
            {
                for (int j = 0; j < libraries[i].listOfBooks().size(); j++)
                {
                    if (libraries[i].listOfBooks()[j].getBookName() == book.getBookName())
                    {
                        throw "This library already has this Book";
                    }
                }
                libraries[i].addBook(book);
            }
        }
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
                                {
                                    bool borrowStatus = true;
                                    libraries[i].listOfBooks()[z].setTheBorrowStatusOfBook(borrowStatus);
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
    }
    bool returnBook(string memberId, int libId, string name)
    {
        for (int i = 0; i < libraries.size(); i++) // for libraries
        {
            if (libraries[i].getLibraryId() == libId) // find library id
            {
                for (int j = 0; j < libraries[i].listOfBooks().size(); j++) // for members of books vector
                {
                    if (libraries[i].listOfBooks()[j].getBookName() == name) // find the name of the book
                    {
                        for (int z = 0; j < members.size(); z++) // for members
                        {
                            if (members[i].getMemberId() == memberId) // find member id
                            {
                                if ((members[i].returnBookFromMember(libraries[i].listOfBooks()[z])) == true)
                                {
                                    bool borrowStatus = false;
                                    libraries[i].listOfBooks()[z].setTheBorrowStatusOfBook(borrowStatus);
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            } // end of finding member id
                        }     // end of for members
                    }         // end of finding the name of the book
                }             // end of for members of books vector
            }                 // end of finding library id
        }                     // end of for libraries
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
    LibrariesHandler allOfLibraries;
    Publisher ItsPublisher("ReadMore", "Tehran");
    Publisher ItsPublisher2("Porteghal", "Shiraz");
    Book firstBook("Clean Code", ItsPublisher, SCIENTIFIC);
    Book secondBook("Blindness", ItsPublisher, CLASSICS);
    Library firstLib("Markazi", 20);
    Library secondLib("Computer", 12);
    Library thirdLib("Fani", 4);
    try
    {
        // cout <<firstBook.showInfo() <<endl;
        allOfLibraries.createLibrary("Markazi", 20);
        allOfLibraries.createLibrary("Computer", 12);
        // cout<<firstLib.showInfoOfLib()<<endl;//markazi
        // cout << secondLib.showInfoOfLib() << endl;//com
        //allOfLibraries.filterByTypeAndShowInfo(SCIENTIFIC);
        allOfLibraries.addBook(1, firstBook);
        allOfLibraries.addBook(2, firstBook);
        allOfLibraries.addBook(3, firstBook);
        cout << allOfLibraries.findLibrariesHaveBook("Clean Code", 4);
    }
    catch (char const *e)
    {
        cout << "erorr :" << e << '\n';
    }
}
