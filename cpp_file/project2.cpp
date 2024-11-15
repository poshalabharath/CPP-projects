#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Taxi{
    public:
         static int taxicount;
         int id;
         bool booked;
         char currentSpot;
         int freeTime;
         int totalEarnings;
         vector<string> trips;

         Taxi(){
            booked = false;
            currentSpot = 'A';
            freeTime = 6;
            totalEarnings = 0;
            taxicount++;
            id = taxicount;
         }

         void setDetails(bool booked, char currentSpot, int freeTime, int totalEarning, string tripDetails){
            this->booked = booked;
            this->currentSpot = currentSpot;
            this->freeTime;
            this->totalEarnings = totalEarnings;
            this->trips.push_back(tripDetails);
         }
         void printDetails(){
            cout<< "Taxi - "<< id <<"Total Earnings - "<< totalEarnings << endl;
            cout<< "TaxiID  BookingID  CustomerID  From To PickupTime DropTime Amount" << endl;
            for(const string& trip:trips){
                cout << trip << endl;
            }
            cout<<"----------------------------------------------------" << endl;

         }
         void printTaxiDetails(){
            cout<< "taxi - " << id << " TotalEarnings - " << totalEarnings << "Current Spot - " << currentSpot << "Free Time- " << freeTime << endl;
         }
};

int Taxi::taxicount =0;

void bookTaxi(int customerID, char pickupPoint, char dropPoint, int PickupTime, vector<Taxi>& taxis){
    vector<Taxi*> freeTaxis;

    for(Taxi& t: taxis){
        if(!t.booked && t.freeTime <= PickupTime){
            freeTaxis.push_back(&t);
        }
    }
    if(freeTaxis.empty()){
        cout<< "No Taxis are available at the that time" << endl;
        return;
    }

    sort(freeTaxis.begin(), freeTaxis.end(), [](const Taxi* a, const Taxi* b){
        return a->totalEarnings < b->totalEarnings;
    });

    Taxi* bookedTaxi = freeTaxis.front();
    int distance = abs(dropPoint - pickupPoint)*15;
    int earning = (distance-5)*10 +100;
    int dropTime = PickupTime + distance/15 +1;

    string tripDetail = to_string(bookedTaxi->id)+"          "+ to_string(customerID) + "         " + pickupPoint + "       " + dropPoint + "        " + to_string(PickupTime) + "        " + to_string(dropTime) + "        "+ to_string(earning);

    bookedTaxi -> setDetails(true, dropPoint, dropTime, bookedTaxi->totalEarnings+earning, tripDetail );
    bookedTaxi->freeTime = dropTime;

    cout<< "Taxi" << bookedTaxi->id << "booked" <<endl;
    cout<< "Booking Details:" <<endl;
    cout<< " Taxi customerID: " << customerID << endl;
    cout<< "PickupPoint:" << pickupPoint << endl;
    cout<< "DropPoint:" << dropPoint << endl;
    cout<< "PickupTime:" << PickupTime << endl;
    cout<< "DropTime:" << dropTime << endl;
    cout<< "Amount:" << earning << endl;


    }
  vector<Taxi> createTaxis(int n){
    vector<Taxi> taxis;
    for(int i=0; i< n; i++){
        Taxi t;
        taxis.push_back(t);
    }
    return taxis;

  }
  int main(){
    vector<Taxi> taxis = createTaxis(4);
    int customerID = 1;
    while(true){
        cout<< "1-> Book Taxi" << endl;
        cout<< "2-> Print Taxi Details" << endl;
        int choice;
        cout << "-------->" << endl;
        cin>> choice;
        switch(choice){
            case 1:
                char pickupPoint, dropPoint;
                int pickupTime;
         
                 cout<< "Enter pickup Point: " << endl;
                 cin>> pickupPoint;
                 cout<< "Enter Drop point:" << endl;
                 cin>> dropPoint;
                 cout<< "Enter pickup Time:" << endl;
                 cin>> pickupTime;

                 bookTaxi(customerID, pickupPoint, dropPoint, pickupTime, taxis);
                 customerID++;
                 break;
            case 2:
               for(Taxi& t: taxis){
                t.printTaxiDetails();
               }
               for(Taxi& t: taxis){
                t.printDetails();
               }
           break;
         default:
            return 0;
             
    }
  }
   return 0;
}