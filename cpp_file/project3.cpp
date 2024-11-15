#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
 
 int SLEEPER_SEATS = 6;
 int RAC_SEATS = 1;
 int WAITING_LIST_SEATS = 1;

 struct Passenger{
     string name;
     int age;
     char gender;
     string berthPreference;
     int seatNumber;
 };
  struct Ticket{
    int ticketID;
    Passenger passenger;
  }; 

   class ReservationSystem{
    vector<Ticket> tickets;
    int ticketID;
    queue<int> lowerBerthSeats;
    queue<int> middleBerthSeats;
    queue<int> upperBerthSeats;
    queue<int> RacSeats;
    queue<int> WaitingListSeats;

    public:
        ReservationSystem(): ticketID(1){
          int i=1;
          while(i<=SLEEPER_SEATS){
            lowerBerthSeats.push(i++);
            middleBerthSeats.push(i++);
            upperBerthSeats.push(i++);
          }
          for(int i=1; i<=RAC_SEATS;i++){
            RacSeats.push(i);
          }
          for(int i=1; i<=WAITING_LIST_SEATS;i++){
                WaitingListSeats.push(i);
          }

        }
        void bookTicket();
        void cancelTicket(int ticketID);
        void printAvailability();
        void printBookedTickets();
   };

   void ReservationSystem::cancelTicket(int ticketID){
    if(tickets.size() == 0){
       cout<<"No tickets found"<<endl;
       return;
    }
    vector<Ticket>::iterator it = tickets.begin();
    for(;it!=tickets.end(); it++){
        if(it->ticketID == ticketID){
            break;
        }
    }
    if(it!=tickets.end()){
        string berth = it->passenger.berthPreference;
        int seatNumber = it->passenger.seatNumber;
        tickets.erase(it);
        cout<<"Ticket Cancelled Successfully" << endl;

        vector<Ticket>::iterator nextAvailableRAC = tickets.begin();
        for(;nextAvailableRAC!=tickets.end(); it++){
            if(nextAvailableRAC->passenger.berthPreference == "RAC"){
                int racSeatNumber = nextAvailableRAC->passenger.seatNumber;
                RacSeats.push(racSeatNumber);
                nextAvailableRAC->passenger.berthPreference = berth;
                nextAvailableRAC->passenger.seatNumber = seatNumber;

                vector<Ticket>::iterator nextAvailableWaitingList = tickets.begin();
                for(; nextAvailableWaitingList!=tickets.end();it++){
                    if(nextAvailableWaitingList->passenger.berthPreference == "WL"){
                       int WaitingListsNumber = nextAvailableWaitingList->passenger.seatNumber;
                        WaitingListSeats.push(WaitingListsNumber);
                        nextAvailableWaitingList->passenger.seatNumber = RacSeats.front();
                        RacSeats.pop();
                        nextAvailableWaitingList->passenger.berthPreference = "RAC";
                        break;
                    }
                }
                break;
            }
        }
        if(nextAvailableRAC == tickets.end()){
            berth == "LB" ? lowerBerthSeats.push(seatNumber) : (berth=="MB" ? middleBerthSeats.push(seatNumber) : upperBerthSeats.push(seatNumber));
        }
    }
    else{
        cout<< "Ticket ID not found" <<endl;
    }
   }

   void ReservationSystem::bookTicket(){
    if(tickets.size()== SLEEPER_SEATS + RAC_SEATS + WAITING_LIST_SEATS){
        cout<< " No tickets available" << endl;
        return;
    }
    Passenger passenger;
        cout<<"Enter Passenger details:";
        cout<<"Name:";
        cin.ignore();
        getline(cin, passenger.name);
        cout<<"Age:";
        cin>> passenger.age;
        cout<<"Gender:";
        cin>>passenger.gender;
        cout<<"Berth Preference (LB/MB/UB):";
        cin>> passenger.berthPreference;

        if(passenger.age<5){
            cout<< "no need of ticket reservation for age below 5" << endl;
        }
        else{
        if(passenger.age>60){
            passenger.berthPreference = "LB";
            if(!lowerBerthSeats.empty()){
                passenger.seatNumber = lowerBerthSeats.front();
                lowerBerthSeats.pop();
            }
            else{
                cout << "Lower Berth for senior citizen is not available"<< endl;
            }
            cout<<"your berth changed";
        }
         if(!lowerBerthSeats.empty()|| !middleBerthSeats.empty()|| !upperBerthSeats.empty()){
           if(passenger.berthPreference == "LB" && !lowerBerthSeats.empty()){
            passenger.seatNumber = lowerBerthSeats.front();
            lowerBerthSeats.pop();
           }
           else if(passenger.berthPreference == "MB" && !middleBerthSeats.empty()){
            passenger.seatNumber = middleBerthSeats.front();
            middleBerthSeats.pop();
         }
         else if(passenger.berthPreference == "UB" && !upperBerthSeats.empty()){
            passenger.seatNumber = upperBerthSeats.front();
            upperBerthSeats.pop();
         }
         else if(!lowerBerthSeats.empty()){
            cout << "Berth Preference changed to LB" << endl;
            passenger.berthPreference = "LB";
            passenger.seatNumber = lowerBerthSeats.front();
            lowerBerthSeats.pop(); 
         }
         else if(!middleBerthSeats.empty()){
            cout << "Berth Preference changed to MB" << endl;
            passenger.berthPreference = "MB";
            passenger.seatNumber = middleBerthSeats.front();
            middleBerthSeats.pop();
            
         }
         else if(!upperBerthSeats.empty()){
            cout << "Berth Preference changed to UB" << endl;
            passenger.berthPreference = "UB";
            passenger.seatNumber = upperBerthSeats.front();
            upperBerthSeats.pop();
         }
         Ticket t ={ticketID++, passenger};
         tickets.push_back(t);
         cout<<"Ticket Booked Successfully, your berth is confirmed, Ticket ID:" << ticketID - 1 << endl;

      }
      else if(!RacSeats.empty()){
        passenger.seatNumber = RacSeats.front();
        passenger.berthPreference = "RAC";
        RacSeats.pop();
        Ticket t= {ticketID++, passenger};
        tickets.push_back(t);
        cout<< "Ticket booked is RAC, Ticket ID:" << ticketID -1 << endl;
      }
       else if(!WaitingListSeats.empty()){
        passenger.seatNumber = WaitingListSeats.front();
        passenger.berthPreference = "WL";
        WaitingListSeats.pop();
        Ticket t= {ticketID++, passenger};
        tickets.push_back(t);
        cout<< "Ticket booked is WL, Ticket ID:" << ticketID -1 << endl;
      }
   }
 }
 void ReservationSystem::printBookedTickets(){
    for(Ticket &t : tickets){
        cout<< "Ticket ID:" << t.ticketID <<", Name:" << t.passenger.name << ", Age: "<< t.passenger.age <<", Gender: "<< t.passenger.gender <<",  Berth:" << t.passenger.seatNumber << t.passenger.berthPreference << ", status: ";
        cout<<(t.passenger.berthPreference == "RAC" ? "RAC" :(t.passenger.berthPreference == "WL" ? "WL" : "confirmed")) <<endl;
    }
 }

  void ReservationSystem::printAvailability(){
    cout<< "Availability sleeper Tickets:-" << "Lower Berth:" << lowerBerthSeats.size() <<", Middle Berth:" << middleBerthSeats.size() << ",Upper Berth:" << upperBerthSeats.size() << endl;
    cout<< "Available RAC tickets:" << RacSeats.size() << endl;
    cout<< "Available WL tickets:" << WaitingListSeats.size()<< endl;
    cout<< endl;
  }


  int main(){
    ReservationSystem system;
    bool userWish(true);
    int choice;
    do{
        cout<<"###### Railway Reservation System Menu #####"<< endl;
        cout<<"1. Book Ticket\n";
        cout<<"2. Cancel Tickets\n";
        cout<<"3. Print Booked Tickets\n";
        cout<<"4. Print Available Tickets\n";
        cout<<"5. Exit"<<endl;
        cout<<"Enter  choice: ";
        cin>> choice;
        switch(choice){
            case 1:
                system.bookTicket();
                break;
            case 2:
               int ID;
               cout<<"Enter Ticket ID: ";
               cin>>ID;
               system.cancelTicket(ID);
               break;
            case 3:
                system.printBookedTickets();
                break;
            case 4:
                 system.printAvailability();
                 break;
            case 5:
                 cout<<"Existing app, Thankyou !!";
                 break;
            default:
            break;
        }
    }while(choice != 5);
    return 0;
  }
