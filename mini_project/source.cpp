#include <iostream>
#include <fstream>
#include <iomanip>
#include "header.h"
#include "Utils.h"
using namespace std;

// GENERATE TICKET
void Ticket::generateTicket(string nameObj, Bus busObj)
{
    name= nameObj;
    pnrNo= generatePNR().c_str();
    date= getCurrentDate().c_str();
    bus = busObj;
}

// DISPLAY TICKET DETAILS
void Ticket::displayTicket()
{
    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t Name:-> " << getName();
    cout << "\n\t\t\t\t\t\t\t\t\t\t PNR No:-> " << getPnrNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus No:-> " << bus.getBusNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Seat No.:-> " << bus.getBookedSeats();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Date:-> " << getDate();
    cout << "\n\t\t\t\t\t\t\t\t\t\t From:-> " << bus.getSource();
    cout << "\n\t\t\t\t\t\t\t\t\t\t To:-> " << bus.getDestination();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Source Time:-> " << bus.getSourceTime();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Destination Time:-> " << bus.getDestinationTime();
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << bus.getBusFare();
    cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

// BOOK TICKET
void Ticket::bookTicket()
{
    system("cls");
    string from;
    string to;
    int chk = 0;

    Bus busObj;
    fstream busFileStream, ticketFileStream, tempFileStream;

    printHeading("BOOK TICKET");
    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
        cin.ignore();
        cin >> from;
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
        cin >> to;

        system("cls");
        printHeading("AVAILABLE BUSES");
        busFileStream.read((char*)&busObj, sizeof(busObj));
        while (!busFileStream.eof())
        {
            if (busObj.getSource().compare(from) == 0  && busObj.getDestination().compare(to) == 0)
            {
                busObj.showBusDetails();
                chk = 1;
            }
            busFileStream.read((char*)&busObj, sizeof(busObj));
        }

        busFileStream.close();

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Buses Found...!!\n";
        }
        else
        {
            string busNumber;
            int booked = 0;

            cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
            cin >> busNumber;

            busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
            tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

            busFileStream.read((char*)&busObj, sizeof(busObj));
            while (!busFileStream.eof())
            {
                if ((busObj.getSource().compare(from) == 0 && busObj.getDestination().compare(to) == 0) &&  busObj.getBusNo().compare(busNumber) == 0)
                {
                    if (busObj.getBookedSeats() >= 32)
                    {
                        cout << "\n\t\t\t\t\t\t\t\t\t\tSeat not available...!!\n";
                        break;
                    }
                    else
                    {
                        system("cls");
                        printHeading("BOOK TICKET");
                        string passengerName;
                        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Customer Name :-> ";
                        cin >> passengerName;
                        busObj.setBookedSeats();
                        generateTicket(passengerName, busObj);
                        ticketFileStream.open("tickets.dat", ios::out | ios::app | ios::binary);
                        ticketFileStream.write((char*)this, sizeof(*this));
                        ticketFileStream.close();
                        tempFileStream.write((char*)&busObj, sizeof(busObj));
                        booked = 1;
                        system("cls");
                        printHeading("BOOKING DETAILS");
                        displayTicket();
                        cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully...!!\n";
                    }
                }
                else
                {
                    tempFileStream.write((char*)&busObj, sizeof(busObj));
                }
                busFileStream.read((char*)&busObj, sizeof(busObj));
            }
            if (booked == 1)
            {
                busFileStream.close();
                tempFileStream.close();
                remove("buses.dat");
                rename("temp.dat", "buses.dat");
            }
        }
        busFileStream.close();
    }
}

// CANCEL TICKET
void Ticket::cancelTicket()
{
    system("cls");

    string pnrNumber;
    int chk = 0;

    fstream busFileStream, ticketFileStream, tempFileStream, busTempFileStream;

    printHeading("CANCEL TICKET");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin >> pnrNumber;

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getPnrNo().compare(pnrNumber) == 0)
            {
                tempFileStream.write((char*)this, sizeof(*this));
            }
            else
            {
                Bus busObj;
                busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
                busTempFileStream.open("bustemp.dat", ios::out | ios::app | ios::binary);
                busFileStream.read((char*)&busObj, sizeof(busObj));
                while (!busFileStream.eof())
                {
                    if (busObj.getBusNo().compare(bus.getBusNo()) == 0)
                    {
                        busObj.setCancelTicket();
                        busTempFileStream.write((char*)&busObj, sizeof(busObj));
                    }
                    else
                    {
                        busTempFileStream.write((char*)&busObj, sizeof(busObj));
                    }
                    busFileStream.read((char*)&busObj, sizeof(busObj));
                }
                busFileStream.close();
                busTempFileStream.close();
                remove("buses.dat");
                rename("bustemp.dat", "buses.dat");
                chk = 1;
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            ticketFileStream.close();
            tempFileStream.close();
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }
        else
        {
            ticketFileStream.close();
            tempFileStream.close();
            remove("tickets.dat");
            rename("temp.dat", "tickets.dat");
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Cancelled...!!\n";
        }
    }
}

// EDIT TICKET
void Ticket::editTicket()
{
    system("cls");

    string pnrNumber;
    int chk = 0;
    fstream ticketFileStream, tempFileStream;
    printHeading("EDIT TICKET");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin >> pnrNumber;
    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getPnrNo().compare(pnrNumber) == 0)
            {
                system("cls");
                printHeading("EDIT TICKET");

                displayTicket();
                string passengerName;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name :-> ";
                cin >> passengerName;
                setName(passengerName);
                tempFileStream.write((char*)this, sizeof(*this));
                chk = 1;
            }
            else
            {
                tempFileStream.write((char*)this, sizeof(*this));
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }

        if (chk == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }

        ticketFileStream.close();
        tempFileStream.close();
        remove("tickets.dat");
        rename("temp.dat", "tickets.dat");
    }
}

// SHOW TICKET BY PNR
void Ticket::showTicketsByPNR()
{
    system("cls");
    string pnrNumber;
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY PNR");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin >> pnrNumber;
    system("cls");
    printHeading("BOOKINGS");
    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getPnrNo().compare(pnrNumber) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY NAME
void Ticket::showTicketsByName()
{
    system("cls");

    string passengerName;
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name:-> ";
    cin.ignore();
    cin >> passengerName;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getName().compare(passengerName) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY BUS
void Ticket::showTicketsByBus()
{
    system("cls");
    string busNumber;
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin >> busNumber;
    system("cls");
    printHeading("BOOKINGS");
    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (bus.getBusNo().compare(busNumber) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY SOURCE
void Ticket::showTicketsBySource()
{
    system("cls");
    string sourceObj;
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY SOURCE");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    cin.ignore();
    cin >> sourceObj;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (bus.getSource().compare(sourceObj) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY DESTINATION
void Ticket::showTicketsByDestination()
{
    system("cls");

    string destinationObj;
    int chk = 0;
    fstream ticketFileStream;
    printHeading("SHOW BOOKINGS BY DESTINATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin.ignore();
    cin >> destinationObj;
    system("cls");
    printHeading("BOOKINGS");
    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (bus.getDestination().compare(destinationObj) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW ALL BOOKINGS
void Ticket::showAllTickets()
{
    system("cls");

    fstream ticketFileStream;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char*)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            displayTicket();
            ticketFileStream.read((char*)this, sizeof(*this));
        }
        ticketFileStream.close();
    }
}

// ADD BUS
void Bus::addBus()
{
    fstream busFileStream;

    system("cls");

    printHeading("ADD BUS");

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin >> busNo;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    cin >> source;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin >> destination;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
    cin >> sourceTime;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination Time:-> ";
    cin >> destinationTime;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
    cin >> busFare;

    busFileStream.open("buses.dat", ios::out | ios::app | ios::binary);
    busFileStream.write((char*)this, sizeof(*this));
    busFileStream.close();

    cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

// SHOW BUS DETAILS
void Bus::showBusDetails()
{
    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t Bus No:-> " << getBusNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Source:-> " << getSource();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Destination:-> " << getDestination();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Time:-> " << getSourceTime() << " - " << getDestinationTime();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Total Seats:-> " << getMaxSeats();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Seats Remaining:-> " << (getMaxSeats() - getBookedSeats());
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << getBusFare();
    cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

// VIEW ALL BUS INFO
void Bus::showAllBus()
{
    system("cls");

    fstream busFileStream;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!busFileStream)
        cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        printHeading("BUSES");

        busFileStream.read((char*)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            showBusDetails();
            busFileStream.read((char*)this, sizeof(*this));
        }
        busFileStream.close();
    }
}

// VIEW BUS INFO
void Bus::viewBusDetails()
{
    system("cls");
    string busNumber;
    int chk = 0;
    fstream busFileStream;

    printHeading("VIEW BUS INFO");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin >> busNumber;

    system("cls");
    printHeading("BUS INFO");

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        busFileStream.read((char*)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo().compare(busNumber) == 0)
            {
                showBusDetails();
                chk = 1;
            }
            busFileStream.read((char*)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }
        busFileStream.close();
    }
}

// EDIT BUS
void Bus::editBus()
{
    system("cls");

    string busNumber;
    int chk = 0;

    fstream busFileStream, tempFileStream;

    printHeading("EDIT BUS");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin >> busNumber;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

        busFileStream.read((char*)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo().compare(busNumber) == 0)
            {
                system("cls");
                printHeading("EDIT BUS");

                showBusDetails();
                string sourceValue; 
                string destinationValue;
                string sourceTimeValue;
                string destinationTimeValue;
                double fareValue;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
                cin >> sourceValue;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
                cin >> destinationValue;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
                cin >> sourceTimeValue;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination Time:-> ";
                cin >> destinationTimeValue;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
                cin.ignore();
                cin >> fareValue;
                setSource(sourceValue);
                setDestination(destinationValue);
                setSourceTime(sourceTimeValue);
                setDestinationTime(destinationTimeValue);
                setBusFare(fareValue);
                tempFileStream.write((char*)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                tempFileStream.write((char*)this, sizeof(*this));
            }
            busFileStream.read((char*)this, sizeof(*this));
        }

        if (chk == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}

// DELETE BUS
void Bus::deleteBus()
{
    system("cls");

    string busNumber;
    int chk = 0;
    fstream busFileStream, tempFileStream;

    printHeading("DELETE BUS");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    cin.ignore();
    cin >> busNumber;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);
        busFileStream.read((char*)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo().compare(busNumber) != 0)
            {
                tempFileStream.write((char*)this, sizeof(*this));
            }
            else
            {
                chk = 1;
            }
            busFileStream.read((char*)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Deleted...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}


