#include <iostream>
#include <vector>
#include <limits>
#include <regex>
using namespace std;


struct node {
    string Name, Priority; 
    int FlightNumber,queuenumber; 
    node *next; 
};

node *head = NULL;
int totpassenger = 0;
vector<string> oplog;
regex pattern("[a-zA-Z ]+");



void AddPassenger();
void RemovePassenger();
void ViewPassengers();
void SearchPassenger();
void QueueStatistics();
void LoggingSystem(int op);
void ModifySystem();
void Alphabetically_sorted();
void FlightNumber_sorted();
void Priority_sorted();
void SearchbyName();
void SearchbyFlightNumber();

int main() {
    int operation;

    while(true) {
        cout << endl << "Please enter an operation to make: " << endl;
        cout << "1) Add a Passenger" << endl;
        cout << "2) Remove a Passenger" << endl;
        cout << "3) View the entire Queue" << endl;
        cout << "4) Search for a passenger" << endl;
        cout << "5) View the Queue's statistics" << endl;
        cout << "6) Show Log" << endl;
        cout << "7) Modify a Passenger" << endl;
        cout << "8) To Exit the program" << endl << endl;
        
        if(!(cin >> operation)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "#################################" << endl;
            cout << "Please enter a correct operation." << endl;
            cout << "#################################" << endl;
            continue;
        }
        if(operation == 1) {
            AddPassenger();
        } 
        else if(operation == 2) {
            RemovePassenger();
        } 
        else if(operation == 3) {
            ViewPassengers();
        } 
        else if(operation == 4) {
            SearchPassenger();
        } 
        else if(operation == 5) {
            QueueStatistics();
        } 
        else if(operation == 6) {
            LoggingSystem(0);
        }
        else if(operation == 7){
            ModifySystem();
        }
        else if(operation == 8) {
            break; 
        }
        else {
            cout << "#################################" << endl;
            cout << "Please Enter a Valid Option." << endl; 
            cout << "#################################" << endl;
            continue;
        }
    }
}

void AddPassenger() {
    int FNumber, count;
    string Pname, Prio;
    node *new_node = new node; 
    node *last;

    cout << "Please enter the name of the passenger: ";
    cin.ignore();
    getline(cin,Pname);

    if(!regex_match(Pname, pattern)) {
        cout << "#################################" << endl;
        cout << "ERROR: Enter a name." << endl;
        cout << "#################################" << endl;
        return;
   }

    cout << "#################################" << endl;
    cout << "Please enter the Flight number of the passenger: ";

    if(!(cin >> FNumber)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "#################################" << endl;
    cout << "Please enter the correct flight number: " << endl;
    cout << "#################################" << endl;
    return;
    }

    cout << "#################################" << endl;
    cout << "Please enter the Passenger registered Class:  ";
    cout << "1) Business   ";
    cout << "2) Special Needs   ";
    cout << "3) Regular   ";
    cin >> Prio;
    cout <<"#################################" << endl;
    if(Prio == "1"){
        Prio = "Business";
    }
    else if(Prio == "2"){
        Prio = "Special Needs";
    }
    else if(Prio == "3"){
        Prio = "Regular";
    }
    else{
        cout << "#################################" << endl;
        cout << "Please enter a valid option." << endl;;
        cout << "#################################" << endl;
        return;
    }

    totpassenger++;

    if(Prio != "Business" && Prio != "Special Needs" && Prio != "Regular") {
        cout << endl << "#################################" << endl;
        cout << "ERROR: Please enter one of the Classes Mention above" << endl;
        cout << "#################################" << endl;
    } else {
        new_node -> FlightNumber = FNumber;
        new_node -> Name = Pname;
        new_node -> Priority = Prio;
        new_node -> queuenumber = totpassenger;

        if(head != NULL) {
            last = head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new_node;
            new_node->next = NULL;
        } else {
            head = new_node; 
        }
    }
    LoggingSystem(1);
}

void RemovePassenger() {
    string name, Prio;
    node *leader = head;
    node *follower = NULL;
    int fnum;

    cout << "#################################" << endl;
    cout <<"Please Enter the passenger name you want to remove from the flight: ";
    cin.ignore();
    getline(cin,name);
    cout << "#################################" << endl;
    cout << "flight number?: ";
    if(!(cin >> fnum)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "#################################" << endl;
            cout << endl << "Please enter the correct flight number" << endl;
            cout << "#################################" << endl;
            return;
        }
    cout << "#################################" << endl;
    cout << "the Passenger registered Class:  ";
    cout << "1) Business   ";
    cout << "2) Special Needs   ";
    cout << "3) Regular   ";
    cin >> Prio;
    if(Prio == "1"){
        Prio = "Business";
    }
    else if(Prio == "2"){
        Prio = "Special Needs";
    }
    else if(Prio == "3"){
        Prio = "Regular";
    }
    else{
        cout << endl << "#################################" << endl;
        cout << "Please enter a valid option." << endl;
        cout << "#################################" << endl;
        return;
    }
    
    if(head == NULL) {
        cout << "#################################" << endl;
        cout << "ERROR: There is no one infront of the queue." << endl;
        cout << "#################################" << endl;
        return;
    }

    if(head -> Name == name && head -> FlightNumber == fnum && head -> Priority == Prio) {
        head = head -> next;
        delete leader;
        cout << endl << "#################################" << endl;
        LoggingSystem(2);
        totpassenger--;
        return;
    }

    while(leader != NULL && (leader -> Name != name || leader -> FlightNumber != fnum || leader -> Priority != Prio)) {
        follower = leader;
        leader = leader -> next;
    }

    if(leader == NULL) {
        cout << "#################################" << endl;
        cout << "ERROR: Passenger not found." << endl;
        cout << "#################################" << endl;
        return;
    }
    
    follower -> next = leader -> next;
    delete leader;
    cout << "#################################" << endl;
    totpassenger--;
    LoggingSystem(2);
}

void ViewPassengers() {
    node *leader = head;
    int num;
    
    if(head == NULL) {
        cout << "#################################" << endl;
        cout << "ERROR: There are no passengers assigned." << endl;
        cout << "#################################" << endl;
        return;
    }
    
    cout << "How would you like the list to be sorted: "<<endl;
    cout << "1) Alphabetical   2) Flight Number   3)Priority?  ";
    if(!(cin >> num)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "#################################" << endl;
            cout << endl << "Please enter a correct operation number." << endl;
            cout << "#################################" << endl;
            return;
    }
    cout << "#################################" << endl;
    if(num == 1){
        Alphabetically_sorted();
    }
    if(num == 2){
        FlightNumber_sorted();
    }

    if(num == 3){
        Priority_sorted();
    }
    LoggingSystem(3);
}


void SearchPassenger() {
    int inputs;
    cout << "#################################" << endl;
    cout << "How would you like to search: "<< endl;
    cout << "1) Name    2)Flight Number?   "<< endl;
    if(!(cin >> inputs)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a correct operation." << endl;
        return;
    }
    cout << "#################################" << endl;
    if(inputs == 1){
        SearchbyName();
    }
    else if(inputs == 2){
        SearchbyFlightNumber();
    }
    else{
        cout << "#################################" << endl;
        cout << "Please enter a correct operation." << endl;
        cout << "#################################" << endl;
        return;
    }
    LoggingSystem(4);
}


void QueueStatistics() {
node *leader = head;
float counting = 0 ,eta_waiting = 0;

if(leader == NULL){
    cout << "#################################" << endl;
    cout << "There is no one in the queue." << endl;
    cout << "#################################" << endl;
    return;
}
while(leader != NULL){
    counting ++;
    eta_waiting = eta_waiting + counting;
    leader = leader -> next;
}
cout << "#################################" << endl;
cout << "People in queue: " << counting << endl;
cout << "Waiting time Estimated: " << eta_waiting/counting << "min/s" << endl;
cout << "#################################" << endl;
}

void LoggingSystem(int op){

    if(op == 1) {
        oplog.push_back("Passenger Added");
        return;
    }
    else if(op == 2) {
        oplog.push_back("Passenger Removed");
        return;
    }
    else if(op == 3) {
        oplog.push_back("Viewed Passengers");
        return;
    }
    else if(op == 4) {
        oplog.push_back("Searched for Passengers");
        return;
    }
    else if(op == 5){
        oplog.push_back("Modified a Passenger");
        return;
    }
    else if(op == 0) {
        cout << endl << "System Log: " << endl;
        for(int i = 0; i < oplog.size(); i++){
        cout << i+1 << ": " << oplog[i] << endl;
        }
    }
    else {
        cout << "#################################" << endl;
        cout << "ERROR: Nothing to show in the log." << endl;
        cout << "#################################" << endl;
        return;
    }
}

void ModifySystem(){
    string name, Prio, newname, newprio;
    node *leader = head;
    node *follower = NULL;
    int fnum,newfnum,operation, ooop;
    
    if(head == NULL) {
        cout << "#################################" << endl;
        cout << endl << "ERROR: There is no one infront of the queue." << endl;
        cout << "#################################" << endl;
        return;
    }

    cout <<"Please Enter the passenger name you want to modify: ";
    cin.ignore();
    getline(cin,name);
    cout << "#################################" << endl;
    cout << "flight number?: ";
    if(!(cin >> fnum)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Please enter the correct flight number" << endl;
            return;
        }
    cout << "#################################" << endl;
    cout << "the Passenger registered Class:  ";
    cout << "1) Business   ";
    cout << "2) Special Needs   ";
    cout << "3) Regular   ";
    cin >> Prio;
    cout << "#################################" << endl;
    if(Prio == "1"){
        Prio = "Business";
    }
    else if(Prio == "2"){
        Prio = "Special Needs";
    }
    else if(Prio == "3"){
        Prio = "Regular";
    }
    else{
        cout << "#################################" << endl;
        cout << endl << "Please enter a valid option." << endl << endl;
        cout << "#################################" << endl;
        return;
    }
    if(head -> Name == name && head -> FlightNumber == fnum && head -> Priority == Prio) {
        cout << "#################################" << endl;
        cout << "Passenger Found." << endl;
        cout << "#################################" << endl;
        cout <<"What would you like to change?" << endl;
        cout <<"1) Name   2) Flight Number   3) Priority?"<< endl;

        if(!(cin >> operation)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Please enter the correct operation." << endl;
            return;
        }
        cout << "#################################" << endl;
        if(operation == 1){
            cout << "Enter the new name: ";
            cin.ignore();
            getline(cin,newname);
            if(!regex_match(newname, pattern)) {
            cout << "#################################" << endl;
            cout << "ERROR: Enter a name please." << endl;
            cout << "#################################" << endl;
            return;
            }
            leader -> Name = newname;
            LoggingSystem(5);
            cout << endl << "#################################" << endl;
            return;
        }
        if(operation == 2){
            cout << "Enter the new flight number: ";
            cin >> newfnum;
            if(!(cin >> newfnum)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Please enter the correct Flight Number." << endl;
            return;
            }
            leader -> FlightNumber = newfnum;
            LoggingSystem(5);
            cout << endl << "#################################" << endl;
            return;
            }
            
        
        if(operation == 3){
            cout << "Enter the new Priority: " << endl;
            cout << "1) Business   ";
            cout << "2) Special Needs   ";
            cout << "3) Regular   ";
            cin >> newprio;
            if(newprio == "1"){
            newprio = "Business";
            }
            else if(newprio == "2"){
                newprio = "Special Needs";
            }
            else if(newprio == "3"){
                newprio= "Regular";
            }
            else{
                cout << "#################################" << endl;
                cout << endl << "Please enter a valid option." << endl << endl;
                cout << "#################################" << endl;
                return;
            }
            leader -> Priority = newprio;
            LoggingSystem(5);
            cout << "#################################" << endl;
            return;
        }
        else{
            cout << "#################################" << endl;
            cout << "Please enter a valid operation.";
            cout << "#################################" << endl;
            return;
        }
    }
    while(leader != NULL && (leader -> Name != name || leader -> FlightNumber != fnum || leader -> Priority != Prio)) {
        follower = leader;
        leader = leader -> next;
    }

    if(leader == NULL) {
        cout << "#################################" << endl;
        cout << "ERROR: Passenger not found." << endl;
        cout << "#################################" << endl;
        return;
    }
    cout << "#################################" << endl;
    cout << "Passenger Found." << endl;
    cout << "#################################" << endl;
    cout <<"What would you like to change?" << endl;
    cout <<"1) Name   2) Flight Number   3) Priority?"<< endl;

    if(!(cin >> operation)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Please enter the correct operation." << endl;
        return;
    }
    cout << "#################################" << endl;
    if(operation == 1){
        cout << "Enter the new name: ";
        cin.ignore();
        getline(cin,newname);
        leader -> Name = newname;
        LoggingSystem(5);
        cout << "#################################" << endl;
        return;
    }
    if(operation == 2){
        cout << "Enter the new flight number: ";
        if(!(cin >> newfnum)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Please enter the correct Flight Number." << endl;
        return;
        }
        leader -> FlightNumber = newfnum;
        LoggingSystem(5);
        cout << "#################################" << endl;
        return;
        }
            
        
    if(operation == 3){
        cout << "Enter the new Priority: " << endl;
        cout << "1) Business   ";
        cout << "2) Special Needs   ";
        cout << "3) Regular   ";
        cin >> newprio;
        if(newprio == "1"){
        newprio = "Business";
        }
        else if(newprio == "2"){
            newprio = "Special Needs";
        }
        else if(newprio == "3"){
            newprio= "Regular";
        }
        else{
            cout << endl << "Please enter a valid option." << endl << endl;
            return;
        }
        leader -> Priority = newprio;
        cout << "#################################" << endl;
        LoggingSystem(5);
        return;
    }
    else{
        cout << "#################################" << endl;
        cout << "Please enter a valid operation.";
        cout << "#################################" << endl;
    }

    
} 

void Alphabetically_sorted() {
    if (head == NULL) {
        cout << "#################################" << endl;
        cout << "There is no one in the queue";
        cout << "#################################" << endl;
        return; 
    }

    bool swapped = true;
    while (swapped) {
        swapped = false;
        node *follower = head;

        while (follower -> next != NULL) {
            node *leader = follower -> next;

            if (follower->Name > leader->Name) {
                swap(follower -> Name, leader -> Name);
                swap(follower -> FlightNumber, leader -> FlightNumber);
                swap(follower -> Priority, leader -> Priority);
                swap(follower -> queuenumber, leader -> queuenumber);

                swapped = true;
            }

            follower = leader;
        }
    }
    node *curr = head;
    while (curr != NULL) {
        cout << "Passenger Name: " << curr -> Name << "   Flight Number: " << curr -> FlightNumber << "   Registered Class: " << curr -> Priority  << "   Place in Queue: "<< curr -> queuenumber<< endl << endl;
        curr = curr -> next;
    }
    cout << "#################################" << endl;
}

void FlightNumber_sorted(){
    if (head == NULL) {
        cout << "#################################" << endl;
        cout << "No one in the queue";
        cout << "#################################" << endl;
        return; 
    }

    bool swapped = true;
    while (swapped) {
        swapped = false;
        node *follower = head;

        while (follower -> next != NULL) {
            node *leader = follower -> next;

            if (follower -> FlightNumber  > leader -> FlightNumber) {
                swap(follower -> Name, leader -> Name);
                swap(follower -> FlightNumber, leader -> FlightNumber);
                swap(follower -> Priority, leader -> Priority);
                swap(follower -> queuenumber, leader -> queuenumber);

                swapped = true;
            }

            follower = leader;
        }
    }
    node *curr = head;
    while (curr != NULL) {
        cout << "Passenger Name: " << curr -> Name << "   Flight Number: " << curr -> FlightNumber << "   Registered Class: " << curr -> Priority  << "   Place in Queue: "<< curr -> queuenumber<< endl << endl;
        curr = curr -> next;
    }
    cout << "#################################" << endl;
}

void Priority_sorted(){
    node *leader = head;
    int num;
    cout << "Business Class Passengers:" << endl;
    while (leader != NULL) {
        if (leader -> Priority == "Business") {
            cout << "Passenger Name: " << leader -> Name << "   Flight Number: " << leader -> FlightNumber << "   Place in Queue: " << leader -> queuenumber << endl;
        }
        leader = leader->next;
    }

    leader = head;

    cout << "Special Needs Class Passengers:" << endl;
    while (leader != NULL) {
        if (leader -> Priority == "Special Needs") {
            cout << "Passenger Name: " << leader -> Name << "   Flight Number: " << leader -> FlightNumber << "   Place in Queue: " << leader -> queuenumber << endl;
        }
        leader = leader->next;
    }

    leader = head;

    cout << "Regular Class Passengers:" << endl;
    while (leader != NULL) {
        if (leader->Priority == "Regular") {
            cout << "Passenger Name: " << leader -> Name << "   Flight Number: " << leader -> FlightNumber << "   Place in Queue: " << leader -> queuenumber << endl;
        }
        leader = leader->next;
    }
}

void SearchbyName(){
    node *leader = head;
    int n = 0, m = totpassenger;
    string names;
    
    cout << "Please enter the name you want to search for: " << endl;
    cin >> names;
    cout << "#################################" << endl;

    if(head == NULL){
        cout << "#################################" << endl;
        cout << "ERROR: There is no passengers assigned." << endl;
        cout << "#################################" << endl;
        return;
    }

    while(n < m && leader != NULL){
        if(leader -> Name == names){
            cout << "Passenger Name: " << leader -> Name << "   Flight Number: " << leader -> FlightNumber << "   Registered Class: " << leader -> Priority << endl;
            cout << "#################################" << endl;
            return;
        }
        leader = leader -> next;
            n++;
        }
    cout << "#################################" << endl;
    cout << "ERROR: the name you are searching for is not found." << endl;
    cout << "#################################" << endl;
}

void SearchbyFlightNumber(){
    node *leader = head;
    int fnum;
    bool found = false;

    cout << "Flight Number? ";
    if(!(cin >> fnum)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a correct operation." << endl;
        return;
    }
    cout << "#################################" << endl;

    if(head == NULL) {
        cout << "#################################" << endl;
        cout << "ERROR: There are no passengers assigned." << endl;
        cout << "#################################" << endl;
        return;
    }

    while(leader != NULL) {
        if(leader -> FlightNumber == fnum) {
            cout << "Passenger Name: " << leader -> Name << "   Flight Number: " << leader -> FlightNumber << "   Registered Class: " << leader -> Priority  << "   Place in queue: " << leader -> queuenumber<< endl << endl;
            found = true;
            cout << "#################################" << endl;
        }
        leader = leader -> next;    
    }
    if(!found) {
        cout << "#################################" << endl;
        cout << "ERROR: the name you are searching for is not found." << endl;
        cout << "#################################" << endl;
    }
}
