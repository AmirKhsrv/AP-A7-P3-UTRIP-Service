#include "Reserve.hpp"

using namespace std;

Reserve::Reserve(const int& _id, Hotel* _hotel, const string& type, const int& quan, const double& _cost
                , const int& cIn, const int& cOut, Rooms reservedR)
{
    id = _id;
    hotel = _hotel;
    roomType = type;
    cost = _cost;
    checkIn = cIn;
    checkOut = cOut;
    quantity = quan;
    reservedRooms = reservedR;
}

int Reserve::getId()
{
    return id; 
}

Hotel* Reserve::getHotel()
{
    return hotel;
}

std::string Reserve::getRoomType()
{
    return roomType;
}

int Reserve::getCost()
{
    return cost;
}

int Reserve::getCheckIn()
{
    return checkIn;
}

int Reserve::getCheckOut()
{
    return checkOut;
}
    
int Reserve::getQuantity()
{
    return quantity;
}

void Reserve::cancelReserve()
{
    for (int i = 0; i < reservedRooms.size(); i++)
        reservedRooms[i]->cancelRoomBook(checkIn, checkOut);
}

Rooms Reserve::getReservedRooms()
{
    return reservedRooms;
}
