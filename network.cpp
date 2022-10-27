#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);

}

Network::~Network(){ // Destructor to delete the person node from memory
    // Copy from lab5 
    Person* ptr = head;
    while(head != NULL){
        ptr=head->next;
        delete head;
        head=ptr;
    }
    head=NULL;
    tail=NULL;
}


void Network::push_front(Person* newEntry){
    // Adds a new Person (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head; // Make the next pointer of new node point to the previous first node

    if (head != NULL)
        head->prev = newEntry; // Adjust the prev pointer of the first node
    else
        tail = newEntry; // Adjust the tail pointer
    
    head = newEntry; // Make head point to the new node
    count++;

}


void Network::push_back(Person* newEntry){
    // Adds a new Person (newEntry) to the back of LL
    // Copy from your lab5
    newEntry->prev = tail;
    newEntry->next = NULL;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
    
    tail = newEntry;
    count++;
}


Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Copy from lab5 
    Person* ptr = head;
    while(ptr != NULL){
        if (*ptr == *searchEntry)   
            return ptr;
        ptr = ptr->next; // Traverse through the list to search using == operator
    }
    return NULL; // Return NULL if not found
}


Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly.
    Person* ptr = head;
    while(ptr != NULL){
        if (ptr -> f_name == fname & ptr -> l_name == lname){ // Check the fname and lname of each node with the pointer
            return ptr;
        }
        ptr = ptr->next; // Traverse through the list
    }
    return NULL;
}

Person* Network::search(string code){
    Person* ptr_search = head;
    while(ptr_search != NULL){
        //cout << codeName(ptr_search -> f_name, ptr_search -> l_name) << endl;
        if (codeName(ptr_search -> f_name, ptr_search -> l_name) == code){
            return ptr_search;
        }
        ptr_search=ptr_search->next;
        }
    return NULL;
    
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of Person: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_Person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Person, not good! You will fix this in PA2.
    ofstream outfile;
    outfile.open(filename);
    Person* ptr = head;
    while(ptr != NULL){
        ptr->saveDB_Person(outfile);
        outfile<< "--------------------" << endl;
        ptr = ptr->next;
    }
    outfile.close();
}


void Network::loadDB(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Person class,
    // Person::Person(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements
    string f_name_string;
    string l_name_string;
    string birth_string;
    string email_string;
    string phone_string;
    string friend_string;
    Person* ptr;

    //cout << "Initialized\n";
    // Open the file <filename>
    fstream f;
    f.open(filename.c_str());
    // Look at connection_template.txt
    //cout << "while loop\n";
    while ( !f.eof() ){//read everything in the file
        //cout << "read\n";
        friend_string = "";
        vector<Person*> myfr;
        // Line #1: first name (can have spaces!)
        std::getline(f,l_name_string,',');
        if(f.eof())
            break;
        l_name_string = l_name_string.substr(l_name_string.find_first_not_of(" "));
        //cout << f_name_string << endl;
        std::getline(f,f_name_string);
        f_name_string = f_name_string.substr(f_name_string.find_first_not_of(" "));
        //cout << l_name_string << endl;
        // Line #2: last name (can have spaces!)
        std::getline(f,birth_string);
        //cout << birth_string << endl;

        // Line #3: date of birth in string format
        std::getline(f,email_string);
        //cout << email_string << endl;

        std::getline(f,phone_string);
        //cout << phone_string << endl;

        ptr = new Person(f_name_string, l_name_string, birth_string, email_string, phone_string);
        //ptr -> print_Person();
        //ptr -> myfriends = myfr;
        while(friend_string != "--------------------"){
            std::getline(f,friend_string);
            Person* ptr_search = search(friend_string);
            if(ptr_search!=NULL){
                    ptr -> makeFriend(ptr_search);
                }
            if(f.eof())
                break;
        }
        this -> push_back(ptr);
    }


    f.close();


}


bool Network::remove(string fname, string lname){
    // We modified the definition of == for Person in Person definition itself, 
    // So we should not be worried about changes we made in Person to modify this method!
    // Copy from lab5
    Person* ptr = NULL;
    Person* prev_f = NULL;
    Person* next_f = NULL;

    ptr = search(fname, lname);
    if (ptr != NULL){
        if (ptr != head & ptr != tail){ // If found but not at head or tail
            prev_f = ptr -> prev;
            next_f = ptr -> next;
            prev_f -> next = next_f; // Make the next of previous node point to the next node
            next_f -> prev = prev_f; // Make the prev of next node point to the previous node
        }
        else if(ptr == head & ptr == tail){ // If found at head and tail
            head = NULL;
            tail = NULL;
        }
        else if(ptr == head){ // If found at head
            next_f = ptr -> next;
            next_f -> prev = NULL; // Make the prev pointer point to NULL
            head = next_f;
        }
        else{
            prev_f = ptr -> prev;
            prev_f -> next = NULL; // Make the next of last node point to NULL
            tail = prev_f;
        }
        ptr->print_Person();
        delete ptr; // Delete the node
        ptr = NULL;
        count--;
        return true;
    }
    else return false;

}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you,
    // You should add code before, between and after prompts!


    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new Person \n";
        cout << "4. Remove a Person \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "9. Connect \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        string fname2,lname2; //for Connect option
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            string fileName;
            cin>>fileName;
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            // Take a look into sample_files.cpp
            cout << "Enter the name of the load file: ";
            cin >> fileName;
            fstream check_file_exit;
            check_file_exit.open(fileName);
            if(!check_file_exit){
                // If file with name FILENAME does not exist:
                cout << "File FILENAME does not exist!" << endl;
                check_file_exit.close();
            }
            else{
                check_file_exit.close();
                cout << "start\n";
                loadDB(fileName);
                // If file is loaded successfully, also print the count of Persons in it:
                cout << "Network loaded from " << fileName << " with " << count << " Persons \n";
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back
            // Add a new Person ONLY if it does not exists!
            
            cout << "Adding a new Person \n";
            Person* p1 = new Person;
            if(search(p1) == NULL){
                push_front(p1);
            }
            printDB();
            cout << "Finish\n";

        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Removing a Person \n";
            string fname, lname;
            cout << "First name: ";
            cin>>fname;
            cout<<endl;
            cout << "Last name: ";
            cin>>lname;
            cout<<endl;
            Person* p1 = search(fname,lname);
            if(p1 !=NULL){
                vector<Person*>::iterator pers;
                pers = p1->myfriends.begin();
                int size = p1->myfriends.size();
                for(int i = 0; i < size; i++){
                    string codename = codeName((*pers)->f_name,(*pers)->l_name);
                    pers++;
                    Person* p_friend=search(codename);
                    if(p_friend!=NULL){
                        p_friend->myfriends.erase(std::remove(p_friend->myfriends.begin(), p_friend->myfriends.end(), p1), p_friend->myfriends.end());
                    }
                    
                }
            }
            bool found = remove(fname,lname);
            if(found){
                cout << "Remove Successful! \n";
                Person* p = search(fname,lname);
            }
            else{
                cout << "Person not found! \n";
            }
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
        }
        else if (opt==5){
            // TODO: Complete me!
            string fname, lname;
            cout << "Searching: \n";
            cout << "First Name: ";
            cin>>fname;
            cout<<endl;
            cout << "Last Name: ";
            cin>>lname;
            cout<<endl;
            Person* p1 = search(fname,lname);
            if(p1 != NULL){
                p1->print_Person();
            }
            else{
                cout << "Not found! \n";
            }
            // if found: print Person
            // if not, cout << "Not found! \n";
        }
        else if (opt==6){
            // Note: Completed!
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Person* ptr = search(fname, lname);
            if (ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_Person();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Option currently not available\n";
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else if ( opt == 9){
            //Part1: print each persons info
            //Part2: delete the print functions and make each object friends 
            cout << " Make friends \n";
            cout << "Connection 1 \n";
            cout << "First Name: \n";
            std::getline(std::cin, fname);
            cout << "Last Name: \n";
            std::getline(std::cin, lname);
            Person* p1 = search(fname,lname);
            if(p1 == NULL){
                cout << "Connection not found! \n";
            }
            else{
                //p1->print_Person();
                cout << " Connection 2 \n";
                cout << "First Name: \n";
                std::getline(std::cin, fname2);
                cout << "Last Name: \n";
                std::getline(std::cin, lname2);
                Person* p2 = search(fname2,lname2);
                if(p2 == NULL){
                    cout << "Connection not found \n";
                }
                else{
                    p1->print_Person();
                    p2->print_Person();
                    p1->makeFriend(p2);
                }
            }

        }


        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

