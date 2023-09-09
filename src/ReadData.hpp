#ifndef READ_DATA_HPP
#define READ_DATA_HPP "READ_DATA_HPP"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Utrip.hpp"
#include "InitialData.hpp"

class ReadData
{
public:
    ReadData(const Address& hDFile, const Address& hRDFile);
    Hotels readHotelsData();

private:
    Hotel* createNewHotel(const std::string& hotelData);
    AmenitiesData getHotelAmenities(const std::string& amenitiesDataStr);
    Location getHotelLocation(std::stringstream& hotelDataStream);
    HotelRoomsData getHotelRoomsData(std::stringstream& hotelDataStream);
    int readintegerFromStream(std::stringstream& hotelDataStream);
    void readAndSetHotelsRatings(Hotels& hotels);
    Hotel* findHotelById(Hotels& hotels, const Id& id);
    void setHotelRatings(Hotels& hotels, const std::string& hotelRatingsData);

    Address hotleDataFile;
    Address hotelsRatingsDataFile;
};

#endif