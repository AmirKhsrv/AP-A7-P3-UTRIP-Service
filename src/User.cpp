#include "User.hpp"

using namespace std;

User::User(const string& _email, const string& _userName, const string& _password)
{
    email = _email;
    userName = _userName;
    password = _password;
    money = USER_INITIAL_MONEY;
    walletRecord.push_back(money);
    reserveIdBase = 1;
    weights.ifEstimatedWeightsCalculated = false;
    weights.ifManualWeightsActive = false;
}

bool User::checkEmailSimilarity(const std::string& _email)
{
    return email == _email;
}

bool User::checkUserNameSimilarity(const std::string& _userName)
{
    return userName == _userName;
}

bool User::checkPasswordSimilarity(const std::string& _password)
{
    return password == _password;
}

void User::increaseMoney(const double& amount)
{
    money += amount;
    walletRecord.push_back(money);
}

WalletRecord User::getWalletRecord(const int& count)
{
    WalletRecord recordToReturn;
    int i = 1;
    while (i <= count)
    {
        if (i > walletRecord.size())
            break;
        recordToReturn.push_back(walletRecord[walletRecord.size() - i]);
        i++;
    }
    return recordToReturn;
}

bool User::checkIfHasEnoughMoney(const double& amount)
{
    if (money >= amount)
    {
        money -= amount;
        walletRecord.push_back(money);
        return true;
    }
    return false;
}

void User::addReserve(Reserve reserve)
{
    reserves.push_back(reserve);
    reserveIdBase++;
}

int User::getReserveIdBase()
{
    return reserveIdBase;
}

Reserves& User::getReserves()
{
    return reserves;
}

void User::deleteReserve(const int& reserveId)
{
    bool ifReserveFound = false;
    for (int i = 0; i < reserves.size(); i++)
        if (reserves[i].getId() == reserveId)
        {
            reserves[i].cancelReserve();
            money += reserves[i].getCost() / 2;
            walletRecord.push_back(money);
            reserves.erase(reserves.begin() + i);
            ifReserveFound = true;
        }
    if (!ifReserveFound)
        throw NotFound();
}

string User::getUserName()
{
    return userName;
}

void User::addRating(const Rating rating)
{
    userRatings.push_back(rating);
    if (weights.ifEstimatedWeightsCalculated)
        estimatePersonalWeight(); 
}

void User::editUserManualWeights(const Weights& _manualWeights)
{
    weights = _manualWeights;
}

Weights User::getWeights()
{
    if (weights.ifManualWeightsActive || weights.ifEstimatedWeightsCalculated)
        return weights;
    else if (userRatings.size() >= MINIMUM_RATING_NUMBER)
    {
        cerr << "weights :" << endl;
        estimatePersonalWeight(); 
        cerr << "location : " << weights.location << endl;
        cerr << "cleanliness : " << weights.cleanliness << endl;
        cerr << "staff : " << weights.staff << endl;
        cerr << "facilities : " << weights.facilities << endl;
        cerr << "valueForMoney : " << weights.valueForMoney << endl;
        return weights;
    }
    throw InsufficientRatings();
}

void User::estimatePersonalWeight()
{
    setPersonalWeightsRandomly();
    for (int i = 0; i < NUMBER_OF_ESTIMATES; i++)
    {
        vector<double> differentials = calculateErrorFuncDifferential();
        weights.location -= STEP_SIZE * differentials[0];
        weights.cleanliness -= STEP_SIZE * differentials[1];
        weights.staff -= STEP_SIZE * differentials[2];
        weights.facilities -= STEP_SIZE * differentials[3];
        weights.valueForMoney -= STEP_SIZE * differentials[4];
        clampWeights();
    }
}

void User::setPersonalWeightsRandomly()
{
    srand(time(NULL));
    weights.location = rand() % 5 + 1;
    weights.cleanliness = rand() % 5 + 1;
    weights.staff = rand() % 5 + 1;
    weights.facilities = rand() % 5 + 1;
    weights.valueForMoney = rand() % 5 + 1;
}

vector<double> User::calculateErrorFuncDifferential()
{
    vector<double> differentials(5, 0);
    for (int j = 0; j < userRatings.size(); j++)
    {
        differentials[0] += calculateErrorFuncPartial(userRatings[j], LOCATION);
        differentials[1] += calculateErrorFuncPartial(userRatings[j], CLEANLINESS);
        differentials[2] += calculateErrorFuncPartial(userRatings[j], STAFF);
        differentials[3] += calculateErrorFuncPartial(userRatings[j], FACILITIES);
        differentials[4] += calculateErrorFuncPartial(userRatings[j], VALUE_FOR_MONEY);
    }
    return differentials;
}

double User::calculateErrorFuncPartial(const Rating& rating, const string& partialOn)
{
    Weights weightsWithEpsilon = weights;
    if (partialOn == LOCATION)
        weightsWithEpsilon.location += EPSILON;
    if (partialOn == CLEANLINESS)
        weightsWithEpsilon.cleanliness += EPSILON;
    if (partialOn == STAFF)
        weightsWithEpsilon.staff += EPSILON;
    if (partialOn == FACILITIES)
        weightsWithEpsilon.facilities += EPSILON;
    if (partialOn == VALUE_FOR_MONEY)
        weightsWithEpsilon.valueForMoney += EPSILON;
    return (calculateErrorFunc(rating, weightsWithEpsilon) - calculateErrorFunc(rating, weights)) / EPSILON;
}

double User::calculateErrorFunc(const Rating& rating, const Weights& _weights)
{
    double weightSum = 0, sum = 0;
    sum += _weights.cleanliness * rating.cleanlinessRating;
    sum += _weights.facilities * rating.facilitiesRating;
    sum += _weights.location * rating.LocationRating;
    sum += _weights.staff * rating.staffRating;
    sum += _weights.valueForMoney * rating.valueForMoneyRating;
    weightSum = _weights.facilities + _weights.cleanliness + _weights.location
                + _weights.staff + _weights.valueForMoney;
    return pow((sum / weightSum) - rating.overallRating, 2);
}

void User::clampWeights()
{
    clampWeight(weights.location);
    clampWeight(weights.cleanliness);
    clampWeight(weights.staff);
    clampWeight(weights.facilities);
    clampWeight(weights.valueForMoney);
}

void User::clampWeight(double& weight)
{
    if (weight > MAXIMUM_STAR)
        weight = MAXIMUM_STAR;
    if (weight < MINIMUM_STAR)
        weight = MINIMUM_STAR;
}

Weights User::getManualWeights()
{
    return weights;
}
