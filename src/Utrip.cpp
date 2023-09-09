#include "Utrip.hpp"

using namespace std;

Utrip::Utrip(Hotels _hotels)
{
    hotels = _hotels;
    currentlyLoginedUser = NULL;
}

void Utrip::registerUser(const string& email, const string& userName, const string& password)
{
    hash<string> hash_string; 
    if (!checkUserNameAndEmailDuplication(email, userName))
    {
        User* newUser = new User(email, userName, to_string(hash_string(password)));
        users.push_back(newUser);
        currentlyLoginedUser = newUser;
        activeInactiveDefaultPriceFilter(true);
    }
    else
        throw BadRequest();
}

bool Utrip::checkUserNameAndEmailDuplication(const string& email, const string& userName)
{
    for (int i = 0; i < users.size(); i++)
        if (users[i]->checkEmailSimilarity(email) || users[i]->checkUserNameSimilarity(userName))
            return true;
    return false;
}

bool Utrip::checkCurrentlyLoginedUser()
{
    return currentlyLoginedUser != NULL;
}

void Utrip::loginUser(const std::string& email, const std::string& password)
{
    activeInactiveDefaultPriceFilter(true);
    hash<string> hash_string; 
    for (int i = 0; i < users.size(); i++)
        if (users[i]->checkEmailSimilarity(email) && users[i]->checkPasswordSimilarity(to_string(hash_string(password))))
        {
            currentlyLoginedUser = users[i];
            DefaultPriceFilter* defaultPriceFilter = new DefaultPriceFilter(currentlyLoginedUser->getReserves());
            userAddedFilters.push_back(defaultPriceFilter);
            return;
        }
    throw BadRequest();
}

void Utrip::logoutUser()
{
    currentlyLoginedUser = NULL;
    userAddedFilters.clear();
}

void Utrip::increaseMoney(const double& amount)
{
    if (amount > 0)
        currentlyLoginedUser->increaseMoney(amount);
    else
        throw BadRequest();
}

WalletRecord Utrip::getUserWalletRecord(const int& count)
{
    if (count > 0)
        return currentlyLoginedUser->getWalletRecord(count);
    else
        throw BadRequest();
}

Hotels Utrip::getHotels()
{
    Hotels hotelsToGet = hotels;
    for (int i = 0; i < userAddedFilters.size(); i++)
    {
        if (checkIfDefaultPriceFilterActive())
            userAddedFilters[i]->refreshReserves(currentlyLoginedUser->getReserves());
        hotelsToGet = userAddedFilters[i]->applyFilter(hotelsToGet);
    }
    sortHotels(hotelsToGet);
    return hotelsToGet;
}

void Utrip::sortHotelsByUniqueId(Hotels& hotels)
{
    for (int i = 0; i < hotels.size(); i++)
        for (int j = i + 1; j < hotels.size(); j++)
            if (hotels[j]->getHotelInfo()->uniqueId < hotels[i]->getHotelInfo()->uniqueId)
            {
                Hotel* swapingHotel = hotels[i];
                hotels[i] = hotels[j];
                hotels[j] = swapingHotel;
            }
}

Hotel* Utrip::getSpecificHotel(const Id& hotelId)
{
    for (int i = 0; i < hotels.size(); i++)
        if (hotels[i]->getHotelInfo()->uniqueId == hotelId)
            return hotels[i];
    throw NotFound();
}

void Utrip::addSpecificStayingFilter(const std::string& roomType, const int& roomQuantity, const int& checkIn, const int& checkOut)
{
    for (int i = 0; i < userAddedFilters.size(); i++)
        if (userAddedFilters[i]->getFilterType() == SPECIFIC_STAYING_FILTER)
            userAddedFilters.erase(userAddedFilters.begin() + i);
    SpecificStayFilter* specificStayFilter = new SpecificStayFilter(roomType, roomQuantity, checkIn, checkOut);
    userAddedFilters.push_back(specificStayFilter);
}

void Utrip::addCityFilter(const std::string& city)
{
    for (int i = 0; i < userAddedFilters.size(); i++)
        if (userAddedFilters[i]->getFilterType() == CITY_FILTER)
            userAddedFilters.erase(userAddedFilters.begin() + i);
    CityFilter* cityFilter = new CityFilter(city);
    userAddedFilters.push_back(cityFilter);
}

void Utrip::addStarSpanFilter(const int& minStar, const int& maxStar)
{
    if (minStar < MINIMUM_STAR || maxStar > MAXIMUM_STAR || minStar > maxStar)
        throw BadRequest();
    for (int i = 0; i < userAddedFilters.size(); i++)
        if (userAddedFilters[i]->getFilterType() == STAR_SPAN_FILTER)
            userAddedFilters.erase(userAddedFilters.begin() + i);
    StarSpanFilter* starSpanFilter = new StarSpanFilter(minStar, maxStar);
    userAddedFilters.push_back(starSpanFilter);
}   

void Utrip::addAveragePriceFilter(const double& minPrice, const double& maxPrice)
{
    if (minPrice < 0 || maxPrice < 0 || minPrice > maxPrice)
        throw BadRequest();
    for (int i = 0; i < userAddedFilters.size(); i++)
        if (userAddedFilters[i]->getFilterType() == PRICE_SPAN_FILTER || userAddedFilters[i]->getFilterType() == DEFAULT_PRICE_FILTER)
            userAddedFilters.erase(userAddedFilters.begin() + i);
    PriceSpanFilter* priceSpanFilter = new PriceSpanFilter(minPrice, maxPrice);
    userAddedFilters.push_back(priceSpanFilter);
}

void Utrip::deleteFilters()
{
    userAddedFilters.clear();
}

Rooms Utrip::bookHotelRoom(const std::string& hotelId, const std::string& roomType, const int& quantity
                        , const int& cIn,const int& cOut)
{
    Hotel* hotel = NULL;
    hotel = findHotelById(hotelId);
    if (hotel == NULL)
        throw NotFound();
    RoomTypeData roomTypeData = hotel->findRoomsByType(roomType);
    double moneyNeeded = hotel->getMoneyNeeded(roomTypeData, quantity, cIn, cOut);
    if (!currentlyLoginedUser->checkIfHasEnoughMoney(moneyNeeded))
        throw NotEnoughCredit();
    Rooms reservedRooms = hotel->bookRoom(roomType, quantity, cIn, cOut);
    currentlyLoginedUser->addReserve(Reserve(currentlyLoginedUser->getReserveIdBase(), hotel, roomType
                        , quantity, moneyNeeded, cIn, cOut, reservedRooms));
    return reservedRooms;
}

Reserves& Utrip::getUserReserves()
{
    return currentlyLoginedUser->getReserves();
}

void Utrip::deleteReserve(const int& reserveId)
{
    currentlyLoginedUser->deleteReserve(reserveId);
}

void Utrip::addComment(const Id& hotelId, const std::string& commentBody)
{
    Comment commentToAdd;
    commentToAdd.user = currentlyLoginedUser;
    commentToAdd.comment = commentBody;
    Hotel* hotel = findHotelById(hotelId);
    if (hotel == NULL)
        throw NotFound();
    hotel->addComment(commentToAdd);
}

Hotel* Utrip::findHotelById(const Id& hotelId)
{
    for (int i = 0; i < hotels.size(); i++)
        if (hotels[i]->getHotelInfo()->uniqueId == hotelId)
            return hotels[i];
    return NULL;
}

void Utrip::addRating(Rating rating)
{
    rating.userName = currentlyLoginedUser->getUserName();
    Hotel* hotel = findHotelById(rating.hotelId);
    if (hotel == NULL)
        throw NotFound();
    currentlyLoginedUser->addRating(rating);
    hotel->addRating(rating);
}

Comments Utrip::getHotelComments(const Id& hotelId)
{
    Hotel* hotel = findHotelById(hotelId);
    if (hotel == NULL)
        throw NotFound();
    return hotel->getComments();
}

Rating* Utrip::getHotelRatings(const Id& hotelId)
{
    Hotel* hotel = findHotelById(hotelId);
    if (hotel == NULL)
        throw NotFound();
    return hotel->getRatings();
}

void Utrip::activeInactiveDefaultPriceFilter(const bool& active)
{
    if (active)
    {
        DefaultPriceFilter* defaultPriceFilter = new DefaultPriceFilter(getUserReserves());
        userAddedFilters.push_back(defaultPriceFilter);
    }
    else 
        for (int i = 0; i < userAddedFilters.size(); i++)
            if (userAddedFilters[i]->getFilterType() == DEFAULT_PRICE_FILTER)
                userAddedFilters.erase(userAddedFilters.begin() + i);
}

bool Utrip::checkIfDefaultPriceFilterActive()
{
    if (currentlyLoginedUser->getReserves().size() < MINIMUM_RESERVES_FOR_DEFAULT_PRICE_FILTER)
        return false;
    for (int i = 0; i < userAddedFilters.size(); i++)
        if (userAddedFilters[i]->getFilterType() == DEFAULT_PRICE_FILTER)
            return true;
    return false;
}

void Utrip::setSortSetting(const SortSetting& sortSetting)
{
    hotelsSortSetting = sortSetting;
}

void Utrip::sortHotels(Hotels& hotels)
{
    sortHotelsByUniqueId(hotels);
    if (hotelsSortSetting.property == ID && hotelsSortSetting.order == DESCENDING)
        sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->uniqueId > h2->getHotelInfo()->uniqueId;});
    if (hotelsSortSetting.property == NAME)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->propertyName < h2->getHotelInfo()->propertyName && hotelsSortSetting.order == ASCENDING;});
    if (hotelsSortSetting.property == STAR_RATING)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->hotelFacility.hotelStarRating < h2->getHotelInfo()->hotelFacility.hotelStarRating && hotelsSortSetting.order == ASCENDING;});
    if (hotelsSortSetting.property == CITY)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->location.city < h2->getHotelInfo()->location.city && hotelsSortSetting.order == ASCENDING;});
    sortHotelsByRoomPrices(hotels);
    if (hotelsSortSetting.property == RATING_PERSONAL)
        sortHotelsByRatingPersonal(hotels);
}

void Utrip::setUserManualWeights(const Weights& weights)
{
    if (weights.cleanliness > MAXIMUM_RATE || weights.facilities > MAXIMUM_RATE || weights.location > MAXIMUM_RATE
        || weights.staff > MAXIMUM_RATE || weights.valueForMoney > MAXIMUM_RATE)
        throw BadRequest();
    currentlyLoginedUser->editUserManualWeights(weights);
}

Weights Utrip::getUserRatingWeights()
{
    Weights weights = currentlyLoginedUser->getWeights();
    if (!weights.ifManualWeightsActive)
        throw BadRequest();
    return weights;
}

Weights Utrip::getManualWeights()
{
    Weights weights = currentlyLoginedUser->getManualWeights();
    return weights;
}

void Utrip::sortHotelsByRatingPersonal(Hotels& hotels)
{
    Weights weights = currentlyLoginedUser->getWeights();
    string userName = currentlyLoginedUser->getUserName();
    stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2)
            {return h1->calculateRatingPersonal(userName, weights) < h2->calculateRatingPersonal(userName, weights) && hotelsSortSetting.order == ASCENDING;});
}

void Utrip::sortHotelsByRoomPrices(Hotels& hotels)
{
    if (hotelsSortSetting.property == STANDARD_ROOM_PRICE)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->hotelRoomsData.standard.roomCost < h2->getHotelInfo()->hotelRoomsData.standard.roomCost && hotelsSortSetting.order == ASCENDING;});
    if (hotelsSortSetting.property == DELUXE_ROOM_PRICE)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->hotelRoomsData.deluxe.roomCost < h2->getHotelInfo()->hotelRoomsData.deluxe.roomCost && hotelsSortSetting.order == ASCENDING;});
    if (hotelsSortSetting.property == LUXURY_ROOM_PRICE)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->hotelRoomsData.luxury.roomCost < h2->getHotelInfo()->hotelRoomsData.luxury.roomCost && hotelsSortSetting.order == ASCENDING;});
    if (hotelsSortSetting.property == PREMIUM_ROOM_PRICE)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelInfo()->hotelRoomsData.premium.roomCost < h2->getHotelInfo()->hotelRoomsData.premium.roomCost && hotelsSortSetting.order == ASCENDING;});
    if (hotelsSortSetting.property == AVERAGE_ROOM_PRICE)
        stable_sort(hotels.begin(), hotels.end(), [&](Hotel* h1, Hotel* h2){return h1->getHotelAveragePrice() < h2->getHotelAveragePrice() && hotelsSortSetting.order == ASCENDING;});
}
