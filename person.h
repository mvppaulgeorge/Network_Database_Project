
#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <vector>

class Person{
    friend class Network;

private:
	string f_name;
	string l_name;
	Date *birthdate;
    Email *email;
    Phone *phone;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    vector<Person*> myfriends;
  

public: 
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string bdate, string email, string phone);
	void print_Person();
    void saveDB_Person(ostream& outfile);
	void set_person();
	void set_person(string filename);
    void makeFriend(Person* newFriend);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    string codeName(string str1,string str2);
};


#endif
