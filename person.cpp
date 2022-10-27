#include "person.h"
//#include "contact.h"
#include <fstream>
#include <sstream>
//library to converting everything to lowercase
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){

    //cout << "person destructor\n";
    delete birthdate;
    delete email;
    delete phone;
    //cout << "delete complete\n";
}


Person::Person(string fname, string lname, string bdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    
    string temp_email, type, addr;
    string temp_phone, typep,num;
    f_name = fname;
    l_name = lname;
    this->birthdate  = new Date(bdate);
    
    stringstream ess(email);
    int i = 0;
    while( ess >> temp_email){
        if( i == 0){
            type = temp_email;
        }
        if( i == 1){
            addr = temp_email;
        }
        i++;
    }
    type = type.substr(1,type.length()-2);
    this->email = new Email(type,addr);
    
    stringstream pss(phone);
    int j = 0;
    while( pss >> temp_phone){
        if( j == 0){
            typep = temp_phone;
        }
        if( j == 1){
            num = temp_phone;
        }
        j++;
    }
    typep = typep.substr(1,typep.length()-2);
    this->phone = new Phone(typep,num);
    
}


Person::Person(string filename){
    set_person(filename);
}



void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string  type, addr;
    string typep,num;
   
    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    
    
    cout << "Type of email address: ";
    std::getline(std::cin, type);
    
    cout << "Email address: ";
    std::getline(std::cin, addr);

    email = new Email(type,addr);
    
    cout << "Type of phone number: ";
    std::getline(std::cin, typep);
    
    cout << "Phone number: ";
    std::getline(std::cin, num);
    phone = new Phone(typep,num);
    
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.

    string temp,temp_phone,temp_email,num;
    string type_phone,type_email,addr;
    ifstream infile;
    infile.open(filename);
    // Open the file <filename>
    std::getline(infile,f_name);
    // Look at connection_template.txt
    // Line #1: first name (can have spaces!)
    // Line #2: last name (can have spaces!)
    std::getline(infile,l_name);
    if (!l_name.empty() && l_name[l_name.size() - 1] == '\r')
        l_name.erase(l_name.size() - 1);
    // Line #3: date of birth in string format
    std::getline(infile,temp);
    birthdate = new Date(temp);
    std::getline(infile,temp_phone);
    int first = temp_phone.find("(");
    int last = temp_phone.find(")");
    type_phone = temp_phone.substr(first+1,last-first-1);
    num = temp_phone.substr(last+2);
    phone = new Phone(type_phone,num);
    
    std::getline(infile,temp_email);
    first = temp_email.find("(");
    last = temp_email.find(")");
    type_email = temp_email.substr(first+1,last-first-1);
    addr = temp_email.substr(last+2);
    email = new Email(type_email,addr);

    infile.close();

}



bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    
     if ( (f_name == rhs.f_name) && 
         (l_name == rhs.l_name) && 
         (*birthdate == *(rhs.birthdate)))
        return true;
    else
        return false; 
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}

string Person::codeName(string str1,string str2){
    //concat both strings and make them all lowercase

    //remove spaces from strings
    string code = " ";
    str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end());
    str2.erase(remove(str2.begin(), str2.end(), ' '), str2.end());

    //convert to lower case
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

    code = str1 + str2;
    return code;

}


void Person::print_Person(){
    // Already implemented for you! Do not change!
    //Updated verion of this function for phase 2
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    vector<Person*>::iterator pers;
    pers = myfriends.begin();
    int size = myfriends.size();
    
    for(int i = 0; i < size; i++){

        string codename = codeName((*pers)->f_name,(*pers)->l_name);
        cout<<codename<<endl;
        pers++;
        
        /*if( i != (size-1)){
            *pers = myfriends[i+1];
        }
        */
        
    }

}

void Person::saveDB_Person(ostream& outfile){
    // Already implemented for you! Do not change!
    //Updated verion of this function for phase 2
    outfile << l_name <<", " << f_name << endl;
    birthdate->saveDB_date("M/D/YYYY", outfile);
    email->saveDB_print(outfile);
    phone->saveDB_print(outfile);
    vector<Person*>::iterator pers;
    pers = myfriends.begin();
    int size = myfriends.size();
    
    for(int i = 0; i < size; i++){

        string codename = codeName((*pers)->f_name,(*pers)->l_name);
        outfile<<codename<<endl;
        
        pers++;
        /*if( i != (size-1)){
            *pers = myfriends[i+1];
        }
        */
        
    }

}

void Person::makeFriend(Person* newFriend){
    //add the inout person into myfriends vector
    if(find(this->myfriends.begin(),this->myfriends.end(), newFriend)==this->myfriends.end()){
        this -> myfriends.push_back(newFriend);
    }
    if (find(newFriend -> myfriends.begin(), newFriend -> myfriends.end(), this) == newFriend -> myfriends.end()){
        newFriend -> myfriends.push_back(this);
    }
}
