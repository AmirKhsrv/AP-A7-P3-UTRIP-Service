#ifndef HOTEL_HPP
#define HOTEL_HPP "HOTEL_HPP"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Room.hpp"
#include "InitialData.hpp"

class Hotel
{
public:
    Hotel(const HotelInfo& hInfo);
    void setHotelAverageRating(const Rating& rating);
    HotelInfo* getHotelInfo();
    double getHotelAveragePrice();
    Rooms bookRoom(const std::string& roomType, const int& quantity, const int& cIn,const int& cOut);
    RoomTypeData& findRoomsByType(const std::string& type);
    double getMoneyNeeded(const RoomTypeData& roomTypeData, const int& quantity, const int& cIn, const int& cOut);
    void addComment(const Comment& comment);
    void addRating(const Rating& rating);
    Comments getComments();
    Rating* getRatings();
    bool checkHotelRoomAvailablity(const RoomTypeData& roomTypeData, const int& checkIn
                                    , const int& checkOut, const int& quantity);
    double calculateRatingPersonal(const std::string userName, const Weights& weights);

private:
    void createHotelRooms();
    double calculateWeightedAverage(const Weights& weights);

    HotelInfo hotelInfo;
    Comments commentsAboutHotel;
    Rating hotelAverageRating;
    Ratings ratings;
};

#endif