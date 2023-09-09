#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#include <iostream>
#include <string>
#include <random>
#include <math.h>
#include <vector>

#include "Hotel.hpp"
#include "Reserve.hpp"
#include "InitialData.hpp"

class User
{
public:
    User(const std::string& _email, const std::string& _userName, const std::string& _password);
    bool checkEmailSimilarity(const std::string& _email);
    bool checkUserNameSimilarity(const std::string& _userName);
    bool checkPasswordSimilarity(const std::string& _password);
    void increaseMoney(const double& amount);
    WalletRecord getWalletRecord(const int& count);
    bool checkIfHasEnoughMoney(const double& amount);
    void addReserve(Reserve reserve);
    int getReserveIdBase();
    Reserves& getReserves();
    void deleteReserve(const int& reserveId);
    std::string getUserName();
    void addRating(const Rating rating);
    void editUserManualWeights(const Weights& _manualWeights);
    Weights getWeights();
    Weights getManualWeights();
    
private:
    void estimatePersonalWeight();
    void setPersonalWeightsRandomly();
    std::vector<double> calculateErrorFuncDifferential();
    double calculateErrorFuncPartial(const Rating& rating, const std::string& partialOn);
    double calculateErrorFunc(const Rating& rating, const Weights& _weights);
    void clampWeights();
    void clampWeight(double& weight);

    std::string email;
    std::string userName;
    std::string password;
    double money;
    WalletRecord walletRecord;
    Reserves reserves;
    int reserveIdBase;
    Ratings userRatings;
    Weights weights;
};

#endif