#ifndef INTERFACE_HPP
#define INTERFACE_HPP "INTERFACE_HPP"

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>

#include "Utrip.hpp"
#include "InitialData.hpp"

class Interface
{
public:
    Interface(Utrip* _utrip);
    void runProgram();
    
private:
    void runGeneralMenu();
    void runUserMenu();
    void getUserGetOrder(std::stringstream& orderDataStream);
    void getUserPostOrder(std::stringstream& orderDataStream);
    void getUserDeleteOrder(std::stringstream& orderDataStream);
    void getGeneralPostOrder(std::stringstream& orderDataStream);
    void getGeneralGetOrder(std::stringstream& orderDataStream);
    void signupUser(std::stringstream& orderDataStream);
    void loginUser(std::stringstream& orderDataStream);
    void logoutUser();
    void increaseUserMoney(std::stringstream& orderDataStream);
    void getUserWalletRecord(std::stringstream& orderDataStream);
    void getHotelsList(std::stringstream& orderDataStream);
    void showHotel(Hotel* hotel);
    void getSpecificHotel(const Id& hotelId);
    void addFilter(std::stringstream& orderDataStream);
    void addCityFilter(const OrderData& orderData);
    void addStarSpanFilter(const OrderData& orderData);
    void addAveragePriceFilter(const OrderData& orderData);
    void addSpecificStayingFilter(const OrderData& orderData);
    void addDefaultPriceFilter(std::stringstream& orderDataStream);
    std::string findValueForType(const OrderData& orderData, const std::string& type);
    OrderData getOrderData(std::stringstream& orderDataStream);
    void orderDone();
    void bookHotelRoom(std::stringstream& orderDataStream);
    void getUserReserves();
    void deleteReserves(std::stringstream& orderDataStream);
    void addComment(std::stringstream& orderDataStream);
    void addRating(std::stringstream& orderDataStream);
    void getHotelComments(std::stringstream& orderDataStream);
    void getHotelAverageRating(std::stringstream& orderDataStream);
    void showComments(const Comments& comments);
    void showRating(const Rating* rating);
    bool checkGeneralPostOrderPermission(const std::string& order);
    void addSortSetting(std::stringstream& orderDataStream);
    void setManualWeights(std::stringstream& orderDataStream);
    void getManualWeights();
    void getEstimatedWeights();
    
    Utrip* utrip;
};

#endif