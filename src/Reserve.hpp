#ifndef RESERVE_HPP
#define RESERVE_HPP "RESERVE_HPP"

#include <iostream>
#include <string>

#include "Hotel.hpp"
#include "InitialData.hpp"

class Reserve
{
public:
    Reserve(const int& _id, Hotel* _hotel, const std::string& type, const int& quan, const double& _cost
            , const int& cIn, const int& cOut, Rooms reservedR);
    int getId();
    Hotel* getHotel();
    std::string getRoomType();
    int getCost();
    int getCheckIn();
    int getCheckOut();
    int getQuantity();
    void cancelReserve();
    Rooms getReservedRooms();
    
private:
    int id;
    Hotel* hotel;
    std::string roomType;
    int quantity;
    double cost;
    int checkIn; 
    int checkOut;
    Rooms reservedRooms;
};

#endif