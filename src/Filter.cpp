#include "Filter.hpp"
#include "Reserve.hpp"

using namespace std;

Filter::Filter()
{

}

CityFilter::CityFilter(const std::string& _city)
{
    city = _city;
}

Hotels CityFilter::applyFilter(const Hotels& allHotels)
{
    Hotels filteredHotels;
    for (int i = 0; i < allHotels.size(); i++)
        if (allHotels[i]->getHotelInfo()->location.city == city)
            filteredHotels.push_back(allHotels[i]);
    return filteredHotels;
}

int CityFilter::getFilterType()
{
    return CITY_FILTER;
}

StarSpanFilter::StarSpanFilter(const int& minS, const int& maxS)
{
    minStar = minS;
    maxStar = maxS;
}

Hotels StarSpanFilter::applyFilter(const Hotels& allHotels)
{
    Hotels filteredHotels;
    for (int i = 0; i < allHotels.size(); i++)
        if (allHotels[i]->getHotelInfo()->hotelFacility.hotelStarRating >= minStar
            && allHotels[i]->getHotelInfo()->hotelFacility.hotelStarRating <= maxStar)
            filteredHotels.push_back(allHotels[i]);
    return filteredHotels;
}

int StarSpanFilter::getFilterType()
{
    return STAR_SPAN_FILTER;
}

PriceSpanFilter::PriceSpanFilter(const double& minP, const double& maxP)
{
    minPrice = minP;
    maxPrice = maxP;
}

Hotels PriceSpanFilter::applyFilter(const Hotels& allHotels)
{
    Hotels filteredHotels;
    for (int i = 0; i < allHotels.size(); i++)
        if (allHotels[i]->getHotelAveragePrice() >= minPrice
            && allHotels[i]->getHotelAveragePrice() <= maxPrice)
            filteredHotels.push_back(allHotels[i]);
    return filteredHotels;
}

int PriceSpanFilter::getFilterType()
{
    return PRICE_SPAN_FILTER;
}

SpecificStayFilter::SpecificStayFilter(const std::string& _type, const int& _quantity, const int& cIn, const int& cOut)
{
    type = _type;
    quantity = _quantity;
    checkIn = cIn;
    checkOut = cOut;
}

Hotels SpecificStayFilter::applyFilter(const Hotels& allHotels)
{
    Hotels filteredHotels;
    for (int i = 0; i < allHotels.size(); i++)
    {
        if (type == STANDARD)
            if (allHotels[i]->checkHotelRoomAvailablity(allHotels[i]->getHotelInfo()->hotelRoomsData.standard, checkIn, checkOut, quantity))
                filteredHotels.push_back(allHotels[i]);
        if (type == DELUXE)
            if (allHotels[i]->checkHotelRoomAvailablity(allHotels[i]->getHotelInfo()->hotelRoomsData.deluxe, checkIn, checkOut, quantity))
                filteredHotels.push_back(allHotels[i]);
        if (type == LUXURY)
            if (allHotels[i]->checkHotelRoomAvailablity(allHotels[i]->getHotelInfo()->hotelRoomsData.luxury, checkIn, checkOut, quantity))
                filteredHotels.push_back(allHotels[i]);
        if (type == PREMIUM)
            if (allHotels[i]->checkHotelRoomAvailablity(allHotels[i]->getHotelInfo()->hotelRoomsData.premium, checkIn, checkOut, quantity))
                filteredHotels.push_back(allHotels[i]);
    }
    return filteredHotels;
}

int SpecificStayFilter::getFilterType()
{
    return SPECIFIC_STAYING_FILTER;
}

void SpecificStayFilter::refreshReserves(const Reserves& newReserves)
{

}

void PriceSpanFilter::refreshReserves(const Reserves& newReserves)
{

}

void StarSpanFilter::refreshReserves(const Reserves& newReserves)
{

}

void CityFilter::refreshReserves(const Reserves& newReserves)
{

}

DefaultPriceFilter::DefaultPriceFilter(const Reserves& newReserves)
{
    reserves = newReserves;
    refreshReserves(newReserves);       
}

Hotels DefaultPriceFilter::applyFilter(const Hotels& allHotels)
{
    if (reserves.size() < MINIMUM_RESERVES_FOR_DEFAULT_PRICE_FILTER)
        return allHotels;
    Hotels filteredHotels;
    for (int i = 0; i < allHotels.size(); i++)
        if (checkHotelPassFilter(allHotels[i]))
            filteredHotels.push_back(allHotels[i]);
    return filteredHotels;
}

int DefaultPriceFilter::getFilterType()
{
    return DEFAULT_PRICE_FILTER;
}

void DefaultPriceFilter::refreshReserves(const Reserves& newReserves)
{
    reserves = newReserves;
    findAllReservedRooms();
    if (allReservedRooms.size() == 0)
        return;
    calculateRoomsAveragePrice();
    calculatestandardDeviation();
}

double DefaultPriceFilter::calculateRoomsAveragePrice()
{
    roomsAveragePrice = (double)accumulate(allReservedRooms.begin(), allReservedRooms.end(), 0, [](int init, Room* room)
        {return init + room->getRoomPrice();}) / (double)allReservedRooms.size();
}

double DefaultPriceFilter::calculatestandardDeviation()
{
    roomsPriceStandardDeviation = sqrt(accumulate(allReservedRooms.begin(), allReservedRooms.end(), 0, [&](double init, Room* room)
        {return init + pow(roomsAveragePrice - room->getRoomPrice(), 2);}) / (allReservedRooms.size() - 1));
}

bool DefaultPriceFilter::checkHotelPassFilter(Hotel* hotel)
{
    return fabs(hotel->getHotelAveragePrice() - roomsAveragePrice) <= 2 * roomsPriceStandardDeviation;
}

void DefaultPriceFilter::findAllReservedRooms()
{
    for (int i = 0; i < reserves.size(); i++)
    {
        Rooms aReserveRooms = reserves[i].getReservedRooms();
        allReservedRooms.insert(allReservedRooms.end(), aReserveRooms.begin(), aReserveRooms.end());
    }
}
