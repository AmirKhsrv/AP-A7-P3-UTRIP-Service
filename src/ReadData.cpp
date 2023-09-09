#include "ReadData.hpp"

using namespace std;

ReadData::ReadData(const Address& hDFile, const Address& hRDFile)
{
    hotleDataFile = hDFile;
    hotelsRatingsDataFile = hRDFile;
}

Hotels ReadData::readHotelsData()
{
    Hotels hotels;
    ifstream hotelData;
    hotelData.open(hotleDataFile);
    string readData;
    getline(hotelData, readData);
    while (getline(hotelData, readData))
        hotels.push_back(createNewHotel(readData));
    readAndSetHotelsRatings(hotels);
    return hotels;
}

Hotel* ReadData::createNewHotel(const string& hotelData)
{
    stringstream hotelDataStream;
    hotelDataStream << hotelData;
    HotelInfo hotelInfo;
    string readData;
    getline(hotelDataStream, hotelInfo.uniqueId, HOTEL_DATA_DELIMITER);
    getline(hotelDataStream, hotelInfo.propertyName, HOTEL_DATA_DELIMITER);
    hotelInfo.hotelFacility.hotelStarRating = readintegerFromStream(hotelDataStream);
    getline(hotelDataStream, hotelInfo.hotelFacility.hotelOverview, HOTEL_DATA_DELIMITER);
    getline(hotelDataStream, readData, HOTEL_DATA_DELIMITER);
    hotelInfo.hotelFacility.propertyAmenities = getHotelAmenities(readData);
    hotelInfo.location = getHotelLocation(hotelDataStream);
    getline(hotelDataStream, hotelInfo.imageUrl, HOTEL_DATA_DELIMITER);
    hotelInfo.hotelRoomsData = getHotelRoomsData(hotelDataStream);
    return new Hotel(hotelInfo);
}

AmenitiesData ReadData::getHotelAmenities(const std::string& amenitiesDataStr)
{
    stringstream amenitiesDataStream;
    amenitiesDataStream << amenitiesDataStr;
    AmenitiesData amenitiesData;
    string readData;
    while (getline(amenitiesDataStream, readData, AMENITIES_DATA_DELIMITER))
        amenitiesData.push_back(readData);
    return amenitiesData;
}

Location ReadData::getHotelLocation(std::stringstream& hotelDataStream)
{
    Location hotelLocation;
    string readData;
    hotelDataStream << HOTEL_DATA_DELIMITER;
    getline(hotelDataStream, hotelLocation.city, HOTEL_DATA_DELIMITER);
    getline(hotelDataStream, readData, HOTEL_DATA_DELIMITER);
    hotelLocation.Latitude = stod(readData);
    getline(hotelDataStream, readData, HOTEL_DATA_DELIMITER);
    hotelLocation.Longitude = stod(readData);
    return hotelLocation;
}

HotelRoomsData ReadData::getHotelRoomsData(std::stringstream& hotelDataStream)
{
    HotelRoomsData hotelRoomsData;
    hotelRoomsData.standard.numberOfRooms = readintegerFromStream(hotelDataStream);
    hotelRoomsData.deluxe.numberOfRooms = readintegerFromStream(hotelDataStream);
    hotelRoomsData.luxury.numberOfRooms = readintegerFromStream(hotelDataStream);
    hotelRoomsData.premium.numberOfRooms = readintegerFromStream(hotelDataStream);
    hotelRoomsData.standard.roomCost = readintegerFromStream(hotelDataStream);
    hotelRoomsData.deluxe.roomCost = readintegerFromStream(hotelDataStream);
    hotelRoomsData.luxury.roomCost = readintegerFromStream(hotelDataStream);
    hotelRoomsData.premium.roomCost = readintegerFromStream(hotelDataStream);
    return hotelRoomsData;
}

int ReadData::readintegerFromStream(std::stringstream& hotelDataStream)
{
    string readData;
    getline(hotelDataStream, readData, HOTEL_DATA_DELIMITER);
    return stoi(readData);
}

void ReadData::readAndSetHotelsRatings(Hotels& hotels)
{
    ifstream hotelRatingsData;
    hotelRatingsData.open(hotelsRatingsDataFile);
    string readData;
    getline(hotelRatingsData, readData);
    while (getline(hotelRatingsData, readData))
        setHotelRatings(hotels, readData);
}

void ReadData::setHotelRatings(Hotels& hotels, const string& hotelRatingsData)
{
    Id hotelId;
    stringstream hotelRatingsDataStream;
    hotelRatingsDataStream << hotelRatingsData;
    getline(hotelRatingsDataStream, hotelId, HOTEL_DATA_DELIMITER);
    Rating averageRating;
    string readData;
    getline(hotelRatingsDataStream, readData, HOTEL_DATA_DELIMITER);
    averageRating.LocationRating = stod(readData);
    getline(hotelRatingsDataStream, readData, HOTEL_DATA_DELIMITER);
    averageRating.cleanlinessRating = stod(readData);
    getline(hotelRatingsDataStream, readData, HOTEL_DATA_DELIMITER);
    averageRating.staffRating = stod(readData);
    getline(hotelRatingsDataStream, readData, HOTEL_DATA_DELIMITER);
    averageRating.facilitiesRating = stod(readData);
    getline(hotelRatingsDataStream, readData, HOTEL_DATA_DELIMITER);
    averageRating.valueForMoneyRating = stod(readData);
    getline(hotelRatingsDataStream, readData, HOTEL_DATA_DELIMITER);
    averageRating.overallRating = stod(readData);
    if (findHotelById(hotels, hotelId) == NULL)
        return;
    findHotelById(hotels, hotelId)->setHotelAverageRating(averageRating);
}

Hotel* ReadData::findHotelById(Hotels& hotels, const Id& id)
{
    for (int i = 0; i < hotels.size(); i++)
        if (hotels[i]->getHotelInfo()->uniqueId == id)
            return hotels[i];
    return NULL;
}
