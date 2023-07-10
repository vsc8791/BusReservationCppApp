#include <iostream>
using namespace std;

class Bus
{
private:
    int maxSeats, bookedSeats;
    double busFare;
    string busNo; 
    string source; 
    string destination; 
    string sourceTime;
    string destinationTime;

public:
    Bus(){
        busNo = "";
        maxSeats = 32;
        bookedSeats = 0;
        busFare = 0.0;
        source = "";
        destination = "";
        sourceTime = "";
        destinationTime = "";
    }

    // METHODS
    void addBus();
    void showAllBus();
    void showBusDetails();
    void viewBusDetails();
    void deleteBus();
    void editBus();

    // GETTERS
    string getBusNo(){
        return busNo;
    }

    string getSource(){
        return source;
    }

    string getDestination() {
        return destination;
    }

    string getSourceTime(){
        return sourceTime;
    }

    string getDestinationTime(){
        return destinationTime;
    }

    int getBookedSeats(){
        return bookedSeats;
    }

    int getMaxSeats() {
        return maxSeats;
    }

    double getBusFare(){
        return busFare;
    }

    // SETTERS
    void setBookedSeats(){
        bookedSeats++;
    }

    void setCancelTicket(){
        bookedSeats--;
    }

    void setSource(string sourceObj){
        if (!sourceObj.empty())
            source = sourceObj;
    }

    void setDestination(string destinationObj){
        if (!destinationObj.empty())
           destination= destinationObj;
    }

    void setSourceTime(string sourceTimeObj) {
        if (!sourceTimeObj.empty())
            sourceTime= sourceTimeObj;
    }

    void setDestinationTime(string destinationTimeObj) {
        if (!destinationTimeObj.empty())
           destinationTime= destinationTimeObj;
    }

    void setBusFare(double fare) {
        if (fare)
            busFare = fare;
    }
};

// CLASS TICKET  ===============================================
class Ticket
{
private:
    string name;
    string pnrNo;
    string date;
    Bus bus;

public:
    void generateTicket(string, Bus);
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void editTicket();
    void showTicketsByPNR();
    void showTicketsByName();
    void showTicketsByBus();
    void showTicketsBySource();
    void showTicketsByDestination();
    void showAllTickets();

    // GETTERS
    string getName()
    {
        return name;
    }

    string getPnrNo()
    {
        return pnrNo;
    }

    string getDate()
    {
        return date;
    }

    // SETTERS
    void setName(string nameObj)
    {
        if (!nameObj.empty())
            name= nameObj;
    }
};









