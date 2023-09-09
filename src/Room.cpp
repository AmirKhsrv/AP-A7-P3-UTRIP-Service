#include "Room.hpp"

using namespace std;

Room::Room(const Id& id, const int& price)
{
    roomId = id;
    roomPrice = price;
    for (int i = 0; i < MONTH_DAYS_NUMBER; i++)
        daysReservationData.push_back(false);
}

StandardRoom::StandardRoom(const Id& id, const int& price)
            : Room(id, price)
{

}

DeluxeRoom::DeluxeRoom(const Id& id, const int& price)
          : Room(id, price)
{

}

LuxuryRoom::LuxuryRoom(const Id& id, const int& price)
          : Room(id, price)
{

}

PremiumRoom::PremiumRoom(const Id& id, const int& price)
          : Room(id, price)
{

}

void StandardRoom::bookRoom(const int& checkIn, const int& checkOut)
{
    for (int i = checkIn; i <= checkOut; i++)
        daysReservationData[i] = true;
}

void DeluxeRoom::bookRoom(const int& checkIn, const int& checkOut)
{
    for (int i = checkIn; i <= checkOut; i++)
        daysReservationData[i] = true;
}

void LuxuryRoom::bookRoom(const int& checkIn, const int& checkOut)
{
    for (int i = checkIn; i <= checkOut; i++)
        daysReservationData[i] = true;
}

void PremiumRoom::bookRoom(const int& checkIn, const int& checkOut)
{
   for (int i = checkIn; i <= checkOut; i++)
        daysReservationData[i] = true;
}

bool LuxuryRoom::ifRoomBooked(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        if (daysReservationData[i] == true)
            return true;
    return false;
}

bool DeluxeRoom::ifRoomBooked(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        if (daysReservationData[i] == true)
            return true;
    return false;
}

bool PremiumRoom::ifRoomBooked(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        if (daysReservationData[i] == true)
            return true;
    return false;
}

bool StandardRoom::ifRoomBooked(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        if (daysReservationData[i] == true)
            return true;
    return false;
}

Id StandardRoom::getRoomId()
{
    return roomId;
}

Id DeluxeRoom::getRoomId()
{
    return roomId;
}

Id LuxuryRoom::getRoomId()
{
    return roomId;
}

Id PremiumRoom::getRoomId()
{
    return roomId;
}

void StandardRoom::cancelRoomBook(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        daysReservationData[i] = false;
}

void DeluxeRoom::cancelRoomBook(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        daysReservationData[i] = false;
}

void LuxuryRoom::cancelRoomBook(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        daysReservationData[i] = false;
}

void PremiumRoom::cancelRoomBook(const int& cIn, const int& cOut)
{
    for (int i = cIn; i <= cOut; i++)
        daysReservationData[i] = false;
}

int StandardRoom::getRoomPrice()
{
    return roomPrice;
}

int DeluxeRoom::getRoomPrice()
{
    return roomPrice;
}

int LuxuryRoom::getRoomPrice()
{
    return roomPrice;
}

int PremiumRoom::getRoomPrice()
{
    return roomPrice;
}