#include<iostream>
#include<string.h>
using namespace std;

class Customer{
    public:
       char name[100];
       char address[100];
       char phone[12];
       float payment_advance;
       int booking_id;
};

class Room{
    public:
        char type;
        char stype;
        char ac;
        int roomNumber;
        int rent;
        int status;

        class Customer cust;
        class Room addRoom(int);
        void searchRoom(int);
        void deleteRoom(int);
        void displayRoom(Room);
    
};


class Room rooms[100];
int count = 0;

  Room Room::addRoom(int rno){
    class Room room;
    room.roomNumber = rno;
    cout<<"\n Type ac/Non-ac (A/N):";
    cin>>room.ac;
    cout<<"\nType Comfort(N/P):";
    cin>>room.type;
    cout<<"\nSize (S/D):";
    cin>>room.stype;
    cout<<"\nDaily Rent:";
    cin>>room.rent;
    room.status = 0;
    
    cout<<"\n Room Added Successfully";
    return room;
}


  void Room::searchRoom(int rno){
    int i, found = 0;
    for(i=0;i<count;i++){
        if(rooms[i].roomNumber == rno){
            found=1;
            break;
        }
    }
    if(found==1){
        cout<<"Room Details\n";
        if(rooms[i].status==1){
            cout<<"\nRoom is Reserved";
        }
        else{
            cout<<"Room is Available"; 
        }
        displayRoom(rooms[i]);  
    }
    else{
        cout<<"Room not found";
    }
}
  void Room::displayRoom(Room tempRoom){
    cout<<"\n Room Number:\t"<< tempRoom.roomNumber;
    cout<<"\n Ac/non-Ac:\t"<< tempRoom.ac;
    cout<<"\n Comfort:\t"<< tempRoom.type;
    cout<<"\n Size :\t"<< tempRoom.stype;
    cout<<"\n Rent:\t"<<  tempRoom.rent;
}

   class HotelMgnt:protected Room{
    public:
      void checkIn();
      void getAvailRoom();
      void searchCustomer(char *);
      void checkOut(int);
      void guestSummaryReport();
    
};
    void HotelMgnt::guestSummaryReport(){
    if(count==0){
        cout<<"\n No Guest in Hotel !";
    }
    for(int i=0; i<count;i++){
        if(rooms[i].status==1){
            cout<<"\nCustomer Name: "<<rooms[i].cust.name;
            cout<<"\n Room Number:"<<rooms[i].roomNumber;
            cout<<"\n Address:"<<rooms[i].cust.address;
            cout<<"\n Phone Number:"<<rooms[i].cust.phone;
            cout<<"\n-------------------------------------";
        }
    }
}

   void HotelMgnt::checkIn(){
    int i,found=0, rno;
    class Room room;
    cout<<"\n Enter room number:";
    cin>> rno;
    for(i=0;i<count;i++){
        if(rooms[i].roomNumber==rno){
            found=1;
            break;
        }
    }
    if(found==1){
        if(rooms[i].status==1){
            cout<<"\n Room is already booked";
            return;
        }
        cout<<"\n Enter Booking id:";
        cin>>rooms[i].cust.booking_id;
        cout<<"\n Enter Customer Name:";
        cin>>rooms[i].cust.name;

        cout<<"\n Enter Phone Number:";
        cin>>rooms[i].cust.phone;

        cout<<"\n Enter the Advance payment:";
        cin>>rooms[i].cust.payment_advance;

        rooms[i].status = 1;
        cout<<"\n Customer Checkedin successfully";
    }
}

  void HotelMgnt::getAvailRoom(){
    int i,found=0;
    for(i=0;i<count;i++){
        if(rooms[i].status==0){
            displayRoom(rooms[i]);
            cout<<"\n\n Press enter for next room";
            found=1;
        }
    }
    if(found==0){
        cout<<"\nAll rooms are reserved";
    }
}
  void HotelMgnt::searchCustomer(char *pname){
    int i, found=0;
    for(int i=0;i<count;i++){
        if(rooms[i].status==1 && strcmp(rooms[i].cust.name, pname)==0){
            cout<<"\n Customer Name:" <<rooms[i].cust.name;
            cout<<"\n Room Number:"<<rooms[i].roomNumber;

            cout<<"\n\n Press Enter for the next record";
            found=1;
        }
       }
    if(found==0){
        cout<<"\n Person Not found";
    }
}
 
  void HotelMgnt::checkOut(int roomnum){
    int i,found=0, days, rno;

    float billAmount=0;

    for(int i=0; i<count; i++){
        if(rooms[i].roomNumber==roomnum && rooms[i].status==1){
            found=1;
            break;

        }
    }
    if(found==1){
        cout<<"\n Enter No of Days:";
        cin>>days;
        billAmount = days*rooms[i].rent;

        cout<<"\nPayable Amount left:"<<(billAmount - rooms[i].cust.payment_advance);
        cout<<"\nChecked out successfully";

        rooms[i].status =0;
    }
 } 

  void manageRooms(){
    class Room room;
    int opt, rno, i, flag=0;
    char ch;
    do{
        cout<<"\n __manage Rooms__";
        cout<<"\n1.Add room";
        cout<<"\n2.Search Room";
        cout<<"\n3.Back to Main Menu";
        cout<<"\n\n Enter Option:";
        cin>>opt;

        switch(opt){
        case 1:
            cout<<"\nEnter Room Number:";
            cin>> rno;
            i=0;
            for(i=0; i<count; i++){
                if(rooms[i].roomNumber==rno){
                    flag=1;
                }
            }
            if(flag==1){
                cout<<"\n Room Number is present.\n please enter unique rooms";
                flag=0;
            }
            else{
                rooms[count] = room.addRoom(rno);
                count++;
            }
            break;
        case 2:
            cout<<"\nEnter Room Number:";
            cin>>rno;
            room.searchRoom(rno);
            break;
         case 3:
            break;
        default:
            cout<<"\n Please select above options only";
            break;
        }
    }while(opt!=3);
}

  int main(){
    class HotelMgnt hm;
    int i,j, opt, rno;
    char ch;
    char pname[100];

    do{
        cout<<"\n ##### Hotel Management ######";
        cout<<"\n 1.Manage Room";
        cout<<"\n 2. Check-In Room";
        cout<<"\n 3. Available Room";
        cout<<"\n 4. Search Customer";
        cout<<"\n 5. Check out room";
        cout<<"\n 6. Guest summary";
        cout<<"\n 7. Quit";

        cout<<"\n\n Enter Option:";
        cin>>opt;
        switch(opt){
            case 1:
              manageRooms();
              break;
            case 2:
                 if(count==0){
                    cout<<"\nNo rooms are registered, please add room first";
                 }
                 else{
                    hm.checkIn();
                 }
                 break;
            case 3:
                 if(count==0){
                    cout<<"\nNo rooms are registered, please add room first";
                 }
                 else{
                    hm.getAvailRoom();
            }
                 break;
            case 4:
                 if(count==0){
                    cout<<"\nNo rooms are registered, please add room first";
                 }
                 else{
                  cout<<"enter customer name:";
                  cin>> pname;
                  hm.searchCustomer(pname);
              }
              break;
            case 5:
                 if(count==0){
                    cout<<"\nNo rooms are registered, please add room first";
                 }
                 else{
                  cout<<"enter customer name:";
                  cin>> rno;
                  hm.checkOut(rno);
              }
              break;
            case 6:
               hm.guestSummaryReport();
               break;
            case 7:
                cout<<"\n Thankyou for using our APP";
                break;
             default:
                  cout<<"\nSelect valid option";
                  break;
        }
    }while(opt!=7);
    
 }
 
