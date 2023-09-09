#ifndef FILTER_HPP
#define FILTER_HPP "FILTER_HPP"

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 

#include "Hotel.hpp"
#include "InitialData.hpp"


class Filter
{
public:
    Filter();
    virtual Hotels applyFilter(const Hotels& allHotels) = 0;
    virtual int getFilterType() = 0;
    virtual void refreshReserves(const Reserves& newReserves) = 0;

private:
    
};

class CityFilter : public Filter
{
public:
    CityFilter(const std::string& _city);
    Hotels applyFilter(const Hotels& allHotels);
    int getFilterType();
    void refreshReserves(const Reserves& newReserves);

private:
    std::string city;
};

class StarSpanFilter : public Filter
{
public:
    StarSpanFilter(const int& minS, const int& maxS);
    Hotels applyFilter(const Hotels& allHotels);
    int getFilterType();
    void refreshReserves(const Reserves& newReserves);

private:
    int minStar;
    int maxStar;
};

class PriceSpanFilter : public Filter
{
public:
    PriceSpanFilter(const double& minP, const double& maxP);
    Hotels applyFilter(const Hotels& allHotels);
    int getFilterType();
    void refreshReserves(const Reserves& newReserves);

private:
    double minPrice;
    double maxPrice;
};

class SpecificStayFilter : public Filter
{
public:
    SpecificStayFilter(const std::string& _type, const int& _quantity, const int& cIn, const int& cOut);
    Hotels applyFilter(const Hotels& allHotels);
    int getFilterType();
    void refreshReserves(const Reserves& newReserves);

private:
    std::string type;
    int quantity;
    int checkIn;
    int checkOut;
};

class DefaultPriceFilter : public Filter
{
public:
    DefaultPriceFilter(const Reserves& newReserves);
    Hotels applyFilter(const Hotels& allHotels);
    int getFilterType();
    void refreshReserves(const Reserves& newReserves);
    
private:
    double calculateRoomsAveragePrice();
    double calculatestandardDeviation();
    bool checkHotelPassFilter(Hotel* hotel);
    void findAllReservedRooms();

    double roomsAveragePrice;
    double roomsPriceStandardDeviation;
    Reserves reserves;
    Rooms allReservedRooms;
};

#endif