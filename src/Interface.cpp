#include "Interface.hpp"

using namespace std;

Interface::Interface(Utrip* _utrip)
{
    utrip = _utrip;
}

void Interface::runProgram()
{
    while (cin)
    {
        if (utrip->checkCurrentlyLoginedUser())
            runUserMenu();
        else
            runGeneralMenu();
    }
}

void Interface::runGeneralMenu()
{
    string order, orderData;   
    cin >> order;
    if (order == NULL_VALUE)
        return;
    getline(cin, orderData);
    stringstream orderDataStream;
    orderDataStream << orderData;
    if (orderData == NULL_VALUE)
        throw BadRequest(); 
    if (order == POST_ORDER)
        getGeneralPostOrder(orderDataStream);
    else if (order == GET_ORDER)
        getGeneralGetOrder(orderDataStream);
    else if (order == DELETE_ORDER)
        throw PermissionDenied();
    else
        throw BadRequest();
}

void Interface::getGeneralPostOrder(stringstream& orderDataStream)
{    
    string order;
    orderDataStream >> order;
    if (order == SIGNUP_ORDER)
        signupUser(orderDataStream);
    else if (order == LOGIN_ORDER)
        loginUser(orderDataStream);
    else if (checkGeneralPostOrderPermission(order))
        throw PermissionDenied();
    else
        throw NotFound();
}

void Interface::getGeneralGetOrder(std::stringstream& orderDataStream)
{
    string order;
    orderDataStream >> order;
    if (order == WALLET_ORDER)
        throw PermissionDenied();
    else if (order == HOTLES_ORDER || order == COMMENTS_ORDER || order == RATINGS_ORDER)
        throw PermissionDenied();
    else
        throw NotFound();
}

void Interface::runUserMenu()
{
    while (utrip->checkCurrentlyLoginedUser())
    {
        string order;
        cin >> order;
        if (order == NULL_VALUE)
            return;
        string orderData;
        getline(cin, orderData);
        stringstream orderDataStream;
        orderDataStream << orderData;
        if (orderData == NULL_VALUE)
            throw BadRequest(); 
        if (order == GET_ORDER)
            getUserGetOrder(orderDataStream);
        else if (order == POST_ORDER)
            getUserPostOrder(orderDataStream);
        else if (order == DELETE_ORDER)
            getUserDeleteOrder(orderDataStream);
        else
            throw BadRequest();
    }
}

void Interface::getUserGetOrder(std::stringstream& orderDataStream)
{
    string order;
    orderDataStream >> order;
    if (order == WALLET_ORDER)
        getUserWalletRecord(orderDataStream);
    else if (order == HOTLES_ORDER)
        getHotelsList(orderDataStream);
    else if (order == FILTERS_ORDER)
        addFilter(orderDataStream);
    else if (order == RESERVES_ORDER)
        getUserReserves();
    else if (order == COMMENTS_ORDER)
        getHotelComments(orderDataStream);
    else if (order == RATINGS_ORDER)
        getHotelAverageRating(orderDataStream);
    else if (order == MANUAL_WEIGHTS_ORDER)
        getManualWeights();
    else if (order == ESTIMATED_WEIGHTS_ORDER)
        getEstimatedWeights();
    else
        throw NotFound();
}

void Interface::getUserPostOrder(std::stringstream& orderDataStream)
{
    string order;
    orderDataStream >> order;
    if (order == LOGOUT_ORDER)
        logoutUser();
    else if (order == WALLET_ORDER)
        increaseUserMoney(orderDataStream);
    else if (order == FILTERS_ORDER)
        addFilter(orderDataStream);
    else if (order == RESERVES_ORDER)
        bookHotelRoom(orderDataStream);
    else if (order == COMMENTS_ORDER)
        addComment(orderDataStream);
    else if (order == RATINGS_ORDER)
        addRating(orderDataStream);
    else if (order == DEFAULT_PRICE_FILTER_ORDER)
        addDefaultPriceFilter(orderDataStream);
    else if (order == SORT_ORDER)
        addSortSetting(orderDataStream);
    else if (order == MANUAL_WEIGHTS_ORDER)
        setManualWeights(orderDataStream);
    else
        throw NotFound();
}

void Interface::signupUser(stringstream& orderDataStream)
{
    string email, userName, password;
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    email = findValueForType(orderData, EMAIL);        
    userName = findValueForType(orderData, USER_NAME);
    password = findValueForType(orderData, PASSWORD);
    utrip->registerUser(email, userName, password);
    orderDone();
}

void Interface::loginUser(stringstream& orderDataStream)
{
    string email, password;
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    email = findValueForType(orderData, EMAIL);
    password = findValueForType(orderData, PASSWORD);
    utrip->loginUser(email, password);
    orderDone();
}

void Interface::logoutUser()
{
    utrip->logoutUser();
    orderDone();
}
    
string Interface::findValueForType(const OrderData& orderData, const string& type)
{
    for (int i = 0; i < orderData.dataTypes.size(); i++)
        if (orderData.dataTypes[i] == type)
            return orderData.dataValues[i];
    throw BadRequest();
    return NULL_VALUE;
}

OrderData Interface::getOrderData(stringstream& orderDataStream)
{
    OrderData orderData;
    string readPart;
    while (orderDataStream >> readPart)
    {
        orderData.dataTypes.push_back(readPart);
        if (!(orderDataStream >> readPart))
            break;
        orderData.dataValues.push_back(readPart);
    }
    if (orderData.dataTypes.size() == 0 || orderData.dataValues.size() == 0)
        throw BadRequest();
    if (orderData.dataTypes.size() != orderData.dataValues.size())
        throw BadRequest();
    return orderData;
}

void Interface::increaseUserMoney(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    double amount;
    string readData;
    orderDataStream >> readData;
    if (readData == AMOUNT)
    {
        orderDataStream >> amount;
        utrip->increaseMoney(amount);
    }
    orderDone();
}

void Interface::orderDone()
{
    cout << "OK" << endl;
}

void Interface::getUserWalletRecord(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    double count;
    WalletRecord walletRecord;
    OrderData orderData = getOrderData(orderDataStream);
    count = stod(findValueForType(orderData, COUNT));
    if (orderData.dataTypes[0] == COUNT)
        walletRecord = utrip->getUserWalletRecord(count);
    for (int i = 0; i < walletRecord.size(); i++)
        cout << (int) round(walletRecord[i]) << endl;
}

void Interface::getHotelsList(std::stringstream& orderDataStream)
{
    string questionMark;
    if (orderDataStream >> questionMark)
    {
        Id hotelId;
        OrderData orderData = getOrderData(orderDataStream);
        hotelId = findValueForType(orderData, ID);
        if (orderData.dataTypes[0] == ID)
            getSpecificHotel(hotelId);
    }
    else
    {
        if (utrip->checkIfDefaultPriceFilterActive())
            cout << "* Results have been filtered by the default price filter." << endl;
        Hotels gotHotels = utrip->getHotels();
        if (gotHotels.size() == 0)
        {
            cout << EMPTY << endl;
            return;
        }
        for (int i = 0; i < gotHotels.size(); i++)
            showHotel(gotHotels[i]);
    }
}

void Interface::showHotel(Hotel* hotel)
{
    cout << hotel->getHotelInfo()->uniqueId << " ";
    cout << hotel->getHotelInfo()->propertyName << " ";
    cout << hotel->getHotelInfo()->hotelFacility.hotelStarRating << " ";
    cout << hotel->getHotelInfo()->location.city << " ";
    int totalNumOfRooms = hotel->getHotelInfo()->hotelRoomsData.standard.numberOfRooms;
    totalNumOfRooms += hotel->getHotelInfo()->hotelRoomsData.deluxe.numberOfRooms;
    totalNumOfRooms += hotel->getHotelInfo()->hotelRoomsData.luxury.numberOfRooms;
    totalNumOfRooms += hotel->getHotelInfo()->hotelRoomsData.premium.numberOfRooms;
    cout << totalNumOfRooms << " ";
    cout << fixed << setprecision(PERCISION_COUNT);
    cout << hotel->getHotelAveragePrice() << setprecision(PERCISION_COUNT) << " " ;
    cout << endl;
}

void Interface::getSpecificHotel(const Id& hotelId)
{
    Hotel* gotHotel = utrip->getSpecificHotel(hotelId);
    cout << gotHotel->getHotelInfo()->uniqueId << endl;
    cout << gotHotel->getHotelInfo()->propertyName << endl;
    cout <<   "star: " << gotHotel->getHotelInfo()->hotelFacility.hotelStarRating << endl;
    cout <<  "overview: " << gotHotel->getHotelInfo()->hotelFacility.hotelOverview << endl;
    int hotelAmenitiesCount = gotHotel->getHotelInfo()->hotelFacility.propertyAmenities.size();
    cout << "amenities: ";
    for (int i = 0; i < hotelAmenitiesCount - 1; i++)
        cout << gotHotel->getHotelInfo()->hotelFacility.propertyAmenities[i] << "|";
    cout << gotHotel->getHotelInfo()->hotelFacility.propertyAmenities[hotelAmenitiesCount - 1] << endl;
    cout <<  "city: " << gotHotel->getHotelInfo()->location.city << endl;
    cout <<  "latitude: " << fixed << setprecision(PERCISION_COUNT) << gotHotel->getHotelInfo()->location.Latitude << endl;
    cout <<  "longitude: " << setprecision(PERCISION_COUNT) << gotHotel->getHotelInfo()->location.Longitude << endl;
    cout << "#rooms: " << gotHotel->getHotelInfo()->hotelRoomsData.standard.numberOfRooms << " ";
    cout << gotHotel->getHotelInfo()->hotelRoomsData.deluxe.numberOfRooms << " ";
    cout << gotHotel->getHotelInfo()->hotelRoomsData.luxury.numberOfRooms << " ";
    cout << gotHotel->getHotelInfo()->hotelRoomsData.premium.numberOfRooms << endl;
    cout << "price: " << gotHotel->getHotelInfo()->hotelRoomsData.standard.roomCost << " ";
    cout << gotHotel->getHotelInfo()->hotelRoomsData.deluxe.roomCost << " ";
    cout << gotHotel->getHotelInfo()->hotelRoomsData.luxury.roomCost << " ";
    cout << gotHotel->getHotelInfo()->hotelRoomsData.premium.roomCost << endl;
}

void Interface::addFilter(stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    if (orderData.dataTypes[0] == CITY)
        addCityFilter(orderData);
    if (orderData.dataTypes[0] == MIN_STAR || orderData.dataTypes[0] == MAX_STAR)
        addStarSpanFilter(orderData);
    if (orderData.dataTypes[0] == MIN_PRICE || orderData.dataTypes[0] == MAX_PRICE)
        addAveragePriceFilter(orderData);
    if (orderData.dataTypes[0] == TYPE || orderData.dataTypes[0] == QUANTITY 
        || orderData.dataTypes[0] == CHECK_IN || orderData.dataTypes[0] == CHECK_OUT)
        addSpecificStayingFilter(orderData);
    orderDone();
}

void Interface::addCityFilter(const OrderData& orderData)
{
    string city;
    city = findValueForType(orderData, CITY);
    if (city == NULL_VALUE)
        throw BadRequest();
    utrip->addCityFilter(city);
}

void Interface::addStarSpanFilter(const OrderData& orderData)
{
    string minStar, maxStar;
    minStar = findValueForType(orderData, MIN_STAR);
    maxStar = findValueForType(orderData, MAX_STAR);
    if (minStar == NULL_VALUE || maxStar == NULL_VALUE)
        throw BadRequest();
    utrip->addStarSpanFilter(stoi(minStar), stoi(maxStar));
}

void Interface::addAveragePriceFilter(const OrderData& orderData)
{
    string minPrice, maxPrice;
    minPrice = findValueForType(orderData, MIN_PRICE);
    maxPrice = findValueForType(orderData, MAX_PRICE);
    if (minPrice == NULL_VALUE || maxPrice == NULL_VALUE)
        throw BadRequest();
    utrip->addAveragePriceFilter(stod(minPrice), stod(maxPrice));
}   

void Interface::addSpecificStayingFilter(const OrderData& orderData)
{
    string type;
    string quantity, checkIn, checkOut;
    type = findValueForType(orderData, TYPE);
    quantity = findValueForType(orderData, QUANTITY);
    checkIn = findValueForType(orderData, CHECK_IN);
    checkOut = findValueForType(orderData, CHECK_OUT);
    if (type == NULL_VALUE || quantity == NULL_VALUE || checkIn == NULL_VALUE || checkOut == NULL_VALUE)
        throw BadRequest();
    utrip->addSpecificStayingFilter(type, stoi(quantity), stoi(checkIn), stoi(checkOut));
}

void Interface::addDefaultPriceFilter(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    string active = findValueForType(orderData, ACTIVE);
    if (active == NULL_VALUE || orderData.dataTypes[0] != ACTIVE)
        throw BadRequest();
    if (active == TRUE_STR)
        utrip->activeInactiveDefaultPriceFilter(true);
    else if (active == FALSE_STR)
        utrip->activeInactiveDefaultPriceFilter(false);
    else
        throw BadRequest();
    orderDone();
}

void Interface::bookHotelRoom(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    string hotelId, type;
    string quantity, checkIn, checkOut;
    hotelId = findValueForType(orderData, HOTEL);
    type = findValueForType(orderData, TYPE);
    quantity = findValueForType(orderData, QUANTITY);
    checkIn = findValueForType(orderData, CHECK_IN);
    checkOut = findValueForType(orderData, CHECK_OUT);
    if (hotelId == NULL_VALUE || type == NULL_VALUE || quantity == NULL_VALUE || checkIn == NULL_VALUE
        || checkOut == NULL_VALUE)
        throw BadRequest();
    Rooms rooms = utrip->bookHotelRoom(hotelId, type, stoi(quantity), stoi(checkIn), stoi(checkOut));
    if (rooms.size() > 0)
    {
        for (int i = 0; i < rooms.size(); i++)
            cout << rooms[i]->getRoomId() << " ";
        cout << endl;
    }
}

void Interface::getUserReserves()
{
    Reserves reserves = utrip->getUserReserves();
    for (int i = reserves.size() - 1; i >= 0; i--)
    {
        cout << "id: " << reserves[i].getId() << " ";
        cout << "hotel: " << reserves[i].getHotel()->getHotelInfo()->uniqueId << " ";
        cout << "room: " << reserves[i].getRoomType() << " ";
        cout << "quantity: " << reserves[i].getQuantity() << " ";
        cout << "cost: " << reserves[i].getCost() << " ";
        cout << "check_in " << reserves[i].getCheckIn() << " ";
        cout << "check_out " << reserves[i].getCheckOut() << endl;   
    }
}

void Interface::deleteReserves(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    string id;
    OrderData orderData = getOrderData(orderDataStream);
    id = findValueForType(orderData, ID);
    if (id == NULL_VALUE)
        throw BadRequest();
    utrip->deleteReserve(stoi(id)); 
    orderDone();
}

void Interface::getUserDeleteOrder(std::stringstream& orderDataStream)
{
    string deleteAbout;
    orderDataStream >> deleteAbout;
    if (deleteAbout == FILTERS_ORDER)
    {
        utrip->deleteFilters();
        orderDone();
    }
    else if (deleteAbout == RESERVES_ORDER)
        deleteReserves(orderDataStream);
}

void Interface::addComment(std::stringstream& orderDataStream)
{
    string commentBody;
    Id hotelId;
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    hotelId = findValueForType(orderData, HOTEL);
    commentBody = findValueForType(orderData, COMMENT);
    if (hotelId == NULL_VALUE || commentBody == NULL_VALUE)
        throw BadRequest();
    utrip->addComment(hotelId, commentBody);
    orderDone();
}

void Interface::addRating(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    Rating rating;
    string hotelId, location, cleanliness, staff, facilities, valueForMoney, overallRating;
    OrderData orderData = getOrderData(orderDataStream);
    hotelId = findValueForType(orderData, HOTEL);
    location = findValueForType(orderData, LOCATION);
    cleanliness = findValueForType(orderData, CLEANLINESS);
    staff = findValueForType(orderData, STAFF);
    facilities = findValueForType(orderData, FACILITIES);
    valueForMoney = findValueForType(orderData, VALUE_FOR_MONEY);
    overallRating = findValueForType(orderData, OVERALL_RATING);
    if (hotelId == NULL_VALUE || location == NULL_VALUE || cleanliness == NULL_VALUE || staff == NULL_VALUE
        || facilities == NULL_VALUE || valueForMoney == NULL_VALUE || overallRating == NULL_VALUE)
        throw BadRequest();
    rating.hotelId = hotelId;
    rating.LocationRating = stod(location);
    rating.cleanlinessRating = stod(cleanliness);
    rating.staffRating = stod(staff);
    rating.facilitiesRating = stod(facilities);
    rating.valueForMoneyRating = stod(valueForMoney);
    rating.overallRating = stod(overallRating);
    utrip->addRating(rating);
    orderDone();
}

void Interface::getHotelComments(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    Id hotelId;
    OrderData orderData = getOrderData(orderDataStream);
    hotelId = findValueForType(orderData, HOTEL);
    if (hotelId == NULL_VALUE)
        throw BadRequest();
    showComments(utrip->getHotelComments(hotelId));
}

void Interface::getHotelAverageRating(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    Id hotelId;
    OrderData orderData = getOrderData(orderDataStream);
    hotelId = findValueForType(orderData, HOTEL);
    if (hotelId == NULL_VALUE)
        throw BadRequest();
    showRating(utrip->getHotelRatings(hotelId));
}

void Interface::showComments(const Comments& comments)
{
    if (comments.size() > 0)
    {
        for (int i = 0; i < comments.size() - 1; i++)
            cout << comments[i].user->getUserName() << ": " << comments[i].comment << endl;
        cout << comments[comments.size() - 1].user->getUserName() << ": " << comments[comments.size() - 1].comment << endl;
    }
}

void Interface::showRating(const Rating* rating)
{
    if (rating != NULL)
    {
        cout << fixed << LOCATION << setprecision(PERCISION_COUNT) << ": " << rating->LocationRating << endl;  
        cout << CLEANLINESS << ": " << setprecision(PERCISION_COUNT) << rating->cleanlinessRating << endl;  
        cout << STAFF << ": " << setprecision(PERCISION_COUNT) << rating->staffRating << endl;  
        cout << FACILITIES << ": " << setprecision(PERCISION_COUNT) << rating->facilitiesRating << endl;  
        cout << "value_for_money" << setprecision(PERCISION_COUNT) << ": " << rating->valueForMoneyRating << endl;  
        cout << "overall_rating" << setprecision(PERCISION_COUNT) << ": " << rating->overallRating << endl;  
    }
    else
        cout << NO_RATING << endl;
}
    
bool Interface::checkGeneralPostOrderPermission(const std::string& order)
{
    return order == LOGOUT_ORDER || order == WALLET_ORDER || order == HOTLES_ORDER
            || order == LOGOUT_ORDER || order == RESERVES_ORDER || order == FILTERS_ORDER
            || order == COMMENTS_ORDER || order == RATINGS_ORDER || order == DEFAULT_PRICE_FILTER_ORDER
            || order == SORT_ORDER || order == MANUAL_WEIGHTS_ORDER || order == ESTIMATED_WEIGHTS_ORDER;
}

void Interface::addSortSetting(std::stringstream& orderDataStream)
{
    SortSetting sortSetting;
    char questionMark;
    orderDataStream >> questionMark;
    OrderData orderData = getOrderData(orderDataStream);
    sortSetting.property = findValueForType(orderData, PROPERTY);        
    sortSetting.order = findValueForType(orderData, ORDER);
    utrip->setSortSetting(sortSetting);
    orderDone();
}

void Interface::setManualWeights(std::stringstream& orderDataStream)
{
    char questionMark;
    orderDataStream >> questionMark;
    Weights manualWeights;
    OrderData orderData = getOrderData(orderDataStream);
    string valueForMoney, facilities, cleanliness, staff, location;
    if (findValueForType(orderData, ACTIVE) == FALSE_STR)
    {
        manualWeights.ifManualWeightsActive = false;
        return;
    }
    manualWeights.ifManualWeightsActive = true;
    cleanliness = findValueForType(orderData, CLEANLINESS);
    staff = findValueForType(orderData, STAFF);
    facilities = findValueForType(orderData, FACILITIES);
    valueForMoney = findValueForType(orderData, VALUE_FOR_MONEY);
    location = findValueForType(orderData, LOCATION);
    if (location == NULL_VALUE || cleanliness == NULL_VALUE || staff == NULL_VALUE
        || facilities == NULL_VALUE || valueForMoney == NULL_VALUE)
        throw BadRequest();
    manualWeights.cleanliness = stod(cleanliness);
    manualWeights.staff = stod(staff);
    manualWeights.facilities = stod(facilities);
    manualWeights.valueForMoney = stod(valueForMoney);
    manualWeights.location = stod(location);
    utrip->setUserManualWeights(manualWeights);
    orderDone();
}

void Interface::getManualWeights()
{
    Weights manualWheights = utrip->getManualWeights();
    if (manualWheights.ifManualWeightsActive == false)
    {
        cout << ACTIVE << " " << FALSE_STR << endl;
        return;
    }
    cout << ACTIVE << " " << TRUE_STR << " ";
    cout << fixed << LOCATION << setprecision(PERCISION_COUNT) << " " << manualWheights.location << " ";
    cout << CLEANLINESS << " " << manualWheights.cleanliness << " ";
    cout << STAFF << " " << manualWheights.staff << " ";
    cout << FACILITIES << " " << manualWheights.facilities << " ";
    cout << VALUE_FOR_MONEY << " " << manualWheights.valueForMoney << " " << endl;
}

void Interface::getEstimatedWeights()
{
    Weights estimatedWheights = utrip->getUserRatingWeights();
    cout << ACTIVE << " " << TRUE_STR << " ";
    cout << fixed << LOCATION << setprecision(PERCISION_COUNT) << " " << estimatedWheights.location << " ";
    cout << CLEANLINESS << " " << estimatedWheights.cleanliness << " ";
    cout << STAFF << " " << estimatedWheights.staff << " ";
    cout << FACILITIES << " " << estimatedWheights.facilities << " ";
    cout << VALUE_FOR_MONEY << " " << estimatedWheights.valueForMoney << " " << endl;
}
