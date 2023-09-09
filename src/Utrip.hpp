#ifndef UTRIP_HPP
#define UTRIP_HPP "UTRIP_HPP"

#include <iostream>
#include <string>
#include <functional>

#include "Filter.hpp"
#include "User.hpp"
#include "Hotel.hpp"
#include "InitialData.hpp"
#include "ReadData.hpp"

class Utrip
{
public:
    Utrip(Hotels _hotels);
    void registerUser(const std::string& email, const std::string& userName, const std::string& password);
    bool checkCurrentlyLoginedUser();
    void loginUser(const std::string& email, const std::string& password);
    void logoutUser();
    void increaseMoney(const double& amount);
    WalletRecord getUserWalletRecord(const int& count);
    Hotels getHotels();
    Hotel* getSpecificHotel(const Id& hotelId);
    void addCityFilter(const std::string& city);
    void addStarSpanFilter(const int& minStar, const int& maxStar);
    void addAveragePriceFilter(const double& minPrice, const double& maxPrice);
    void addSpecificStayingFilter(const std::string& roomType, const int& roomQuantity, const int& checkIn, const int& checkOut);
    void deleteFilters();
    Rooms bookHotelRoom(const std::string& hotelId, const std::string& roomType, const int& quantity, const int& cIn,const int& cOut);
    Reserves& getUserReserves();
    void deleteReserve(const int& reserveId);
    void addComment(const Id& hotelId, const std::string& commentBody);
    void addRating(Rating rating);
    Comments getHotelComments(const Id& hotelId);
    Rating* getHotelRatings(const Id& hotelId);
    void activeInactiveDefaultPriceFilter(const bool& active);
    bool checkIfDefaultPriceFilterActive();
    void setSortSetting(const SortSetting& sortSetting);
    void setUserManualWeights(const Weights& weights);
    Weights getUserRatingWeights();
    Weights getManualWeights();
    bool checkUserNameAndEmailDuplication(const std::string& email, const std::string& userName);

private:
    void sortHotelsByUniqueId(Hotels& hotels);
    Hotel* findHotelById(const Id& hotelId);
    void sortHotels(Hotels& hotels);
    void sortHotelsByRatingPersonal(Hotels& hotels);
    void sortHotelsByRoomPrices(Hotels& hotels);

    Users users;
    Hotels hotels;
    User* currentlyLoginedUser;
    Filters userAddedFilters;
    SortSetting hotelsSortSetting;
};

#endif