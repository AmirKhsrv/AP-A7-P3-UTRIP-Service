#include "Hotel.hpp"

using namespace std;

Hotel::Hotel(const HotelInfo& hInfo)
{
    hotelInfo = hInfo;
    createHotelRooms();
}

void Hotel::createHotelRooms()
{
    for (int i = 0; i < hotelInfo.hotelRoomsData.standard.numberOfRooms; i++)
        hotelInfo.hotelRoomsData.standard.rooms.push_back(new StandardRoom(STANDARD_ROOMS_ID_BASE + to_string(i + 1)
                            , hotelInfo.hotelRoomsData.standard.roomCost));
    for (int i = 0; i < hotelInfo.hotelRoomsData.deluxe.numberOfRooms; i++)
        hotelInfo.hotelRoomsData.deluxe.rooms.push_back(new DeluxeRoom(DELUXE_ROOMS_ID_BASE + to_string(i + 1)
                            , hotelInfo.hotelRoomsData.deluxe.roomCost));
    for (int i = 0; i < hotelInfo.hotelRoomsData.luxury.numberOfRooms; i++)
        hotelInfo.hotelRoomsData.luxury.rooms.push_back(new LuxuryRoom(LUXURY_ROOMS_ID_BASE + to_string(i + 1)
                            , hotelInfo.hotelRoomsData.luxury.roomCost));
    for (int i = 0; i < hotelInfo.hotelRoomsData.premium.numberOfRooms; i++)
        hotelInfo.hotelRoomsData.premium.rooms.push_back(new PremiumRoom(PREMIUM_ROOMS_ID_BASE + to_string(i + 1)
                            , hotelInfo.hotelRoomsData.premium.roomCost));
}

HotelInfo* Hotel::getHotelInfo()
{
    return &hotelInfo;
}

double Hotel::getHotelAveragePrice()
{
    double priceSum = 0;
    int roomNumbers = 0;
    if (hotelInfo.hotelRoomsData.standard.roomCost != 0)
    {
        priceSum += hotelInfo.hotelRoomsData.standard.roomCost;
        roomNumbers++;
    }
    if (hotelInfo.hotelRoomsData.deluxe.roomCost != 0)
    {
        priceSum += hotelInfo.hotelRoomsData.deluxe.roomCost;
        roomNumbers++;
    }
    if (hotelInfo.hotelRoomsData.luxury.roomCost != 0)
    {
        priceSum += hotelInfo.hotelRoomsData.luxury.roomCost;
        roomNumbers++;
    }
    if (hotelInfo.hotelRoomsData.premium.roomCost != 0)
    {
        priceSum += hotelInfo.hotelRoomsData.premium.roomCost;
        roomNumbers++;
    }
    if (roomNumbers == 0)
        return 0.00;
    return priceSum / roomNumbers;
}

Rooms Hotel::bookRoom(const std::string& roomType, const int& quantity, const int& cIn,const int& cOut)
{
    Rooms rooms;
    RoomTypeData roomTypeData = findRoomsByType(roomType);
    int bookedRoomsCounter = 0;
    for (int i = 0; i < roomTypeData.rooms.size(); i++)
        if (!roomTypeData.rooms[i]->ifRoomBooked(cIn, cOut))
        {
            if (bookedRoomsCounter >= quantity)
                break;
            roomTypeData.rooms[i]->bookRoom(cIn, cOut);
            rooms.push_back(roomTypeData.rooms[i]);
            bookedRoomsCounter++;
        }
    return rooms;
}

RoomTypeData& Hotel::findRoomsByType(const std::string& type)
{
    if (type == STANDARD)
        return hotelInfo.hotelRoomsData.standard;
    if (type == DELUXE)
        return hotelInfo.hotelRoomsData.deluxe;
    if (type == LUXURY)
        return hotelInfo.hotelRoomsData.luxury;
    if (type == PREMIUM)
        return hotelInfo.hotelRoomsData.premium;
}

double Hotel::getMoneyNeeded(const RoomTypeData& roomTypeData, const int& quantity, const int& cIn, const int& cOut)
{
    int roomCounter = 0;
    for (int i = 0; i < roomTypeData.rooms.size(); i++)
        if (!roomTypeData.rooms[i]->ifRoomBooked(cIn, cOut))
            roomCounter++;
    if (roomCounter < quantity)
        throw NotEnoughRoom();
    return quantity * roomTypeData.roomCost * (cOut - cIn + 1);
}

void Hotel::addComment(const Comment& comment)
{   
    commentsAboutHotel.push_back(comment);
}

void Hotel::addRating(const Rating& rating)
{
    for (int i = 0; i < ratings.size(); i++)
        if (ratings[i].userName == rating.userName)
            ratings.erase(ratings.begin() + i);
    ratings.push_back(rating);
}

Comments Hotel::getComments()
{
    return commentsAboutHotel;
}

Rating* Hotel::getRatings()
{
    return &hotelAverageRating;
}

bool Hotel::checkHotelRoomAvailablity(const RoomTypeData& roomTypeData, const int& checkIn
                                        , const int& checkOut, const int& quantity)
{
    int roomCounter = 0;
    for (int i = 0; i < roomTypeData.rooms.size(); i++)
        if (!roomTypeData.rooms[i]->ifRoomBooked(checkIn, checkOut))
            roomCounter++;
    if (roomCounter >= quantity)
        return true;
    return false;
}

void Hotel::setHotelAverageRating(const Rating& rating)
{
    hotelAverageRating = rating;
}

double Hotel::calculateRatingPersonal(const std::string userName, const Weights& weights)
{
    for (int i = 0; i < ratings.size(); i++)
        if (ratings[i].userName == userName)
            return ratings[i].overallRating;
    return calculateWeightedAverage(weights);
}

double Hotel::calculateWeightedAverage(const Weights& weights)
{
    double weightSum = 0, sum = 0;
    sum += weights.cleanliness * hotelAverageRating.cleanlinessRating;
    sum += weights.facilities * hotelAverageRating.facilitiesRating;
    sum += weights.location * hotelAverageRating.LocationRating;
    sum += weights.staff * hotelAverageRating.staffRating;
    sum += weights.valueForMoney * hotelAverageRating.valueForMoneyRating;
    weightSum = weights.facilities + weights.cleanliness + weights.location
                + weights.staff + weights.valueForMoney;
    return sum / weightSum;
}
