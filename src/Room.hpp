#ifndef ROOM_HPP
#define ROOM_HPP "ROOM_HPP"

#include <iostream>
#include <string>
#include <iomanip>

#include "Exception.hpp"
#include "InitialData.hpp"

class Room
{
public:
    Room(const Id& id, const int& price);
    virtual void bookRoom(const int& checkIn, const int& checkOut) = 0;
    virtual bool ifRoomBooked(const int& cIn, const int& cOut) = 0;
    virtual Id getRoomId() = 0;
    virtual void cancelRoomBook(const int& cIn, const int& cOut) = 0;
    virtual int getRoomPrice() = 0;

protected:
    Id roomId;
    int roomPrice;
    DaysReservationData daysReservationData;
};

class StandardRoom : public Room
{
public:
    StandardRoom(const Id& id, const int& price);
    void bookRoom(const int& checkIn, const int& checkOut);
    bool ifRoomBooked(const int& cIn, const int& cOut);
    Id getRoomId();
    void cancelRoomBook(const int& cIn, const int& cOut); 
    int getRoomPrice();

private:    
};

class DeluxeRoom : public Room
{
public:
    DeluxeRoom(const Id& id, const int& price);
    void bookRoom(const int& checkIn, const int& checkOut);
    bool ifRoomBooked(const int& cIn, const int& cOut);
    Id getRoomId();
    void cancelRoomBook(const int& cIn, const int& cOut); 
    int getRoomPrice();

private:
};

class LuxuryRoom : public Room
{
public:
    LuxuryRoom(const Id& id, const int& price);
    void bookRoom(const int& checkIn, const int& checkOut);
    bool ifRoomBooked(const int& cIn, const int& cOut);
    Id getRoomId();
    void cancelRoomBook(const int& cIn, const int& cOut); 
    int getRoomPrice();

private:
};

class PremiumRoom : public Room
{
public:
    PremiumRoom(const Id& id, const int& price);
    void bookRoom(const int& checkIn, const int& checkOut);
    bool ifRoomBooked(const int& cIn, const int& cOut);
    Id getRoomId();
    void cancelRoomBook(const int& cIn, const int& cOut); 
    int getRoomPrice();

private:
};

#endif