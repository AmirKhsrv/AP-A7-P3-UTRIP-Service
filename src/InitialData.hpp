#ifndef INITIAL_DATA_HPP
#define INITIAL_DATA_HPP "INITIAL_DATA_HPP"

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

class Room;
class Hotel;
class Filter;
class Reserve;

typedef std::string Id;

const std::string STANDARD_ROOMS_ID_BASE = "s";
const std::string DELUXE_ROOMS_ID_BASE = "d";
const std::string LUXURY_ROOMS_ID_BASE = "l";
const std::string PREMIUM_ROOMS_ID_BASE = "p";
const std::string STANDARD = "standard";
const std::string DELUXE = "deluxe";
const std::string LUXURY = "luxury";
const std::string PREMIUM = "premium";

class User;

typedef std::vector<Id> RoomIds;
typedef std::vector<Room*> Rooms;

struct Location
{
    std::string city;
    double Latitude;
    double Longitude;
};

struct RoomTypeData
{
    int numberOfRooms;
    int roomCost;
    Rooms rooms;
};

typedef struct RoomTypeData RoomTypeData;

struct HotelRoomsData
{
    RoomTypeData standard;
    RoomTypeData deluxe;
    RoomTypeData luxury;
    RoomTypeData premium;
};

typedef std::vector<std::string> AmenitiesData;
typedef struct HotelRoomsData HotelRoomsData;

struct HotelFacility
{
    int hotelStarRating;
    std::string hotelOverview;
    AmenitiesData propertyAmenities;
};

typedef struct HotelFacility HotelFacility;
typedef struct Location Location;

struct HotelInfo
{
    Id uniqueId;
    std::string propertyName;
    Location location;
    HotelFacility hotelFacility;
    std::string imageUrl;
    HotelRoomsData hotelRoomsData;
};

typedef struct HotelInfo HotelInfo;

struct Comment
{
    std::string comment;
    User* user;
};

typedef struct Comment Comment;
typedef std::vector<Comment> Comments;

struct Rating
{
    std::string userName;
    Id hotelId;
    double LocationRating;
    double cleanlinessRating;
    double staffRating;
    double facilitiesRating;
    double valueForMoneyRating;
    double overallRating;
};

typedef struct Rating Rating;
typedef std::vector<Rating> Ratings;

const int CITY_FILTER = 0;
const int STAR_SPAN_FILTER = 1;
const int PRICE_SPAN_FILTER = 2;
const int SPECIFIC_STAYING_FILTER = 3;
const int DEFAULT_PRICE_FILTER = 4;
typedef std::vector<Hotel*> Hotels;


typedef std::vector<Hotel*> Hotels;
typedef std::vector<Filter*> Filters;
typedef std::vector<User*> Users;

const int MAXIMUM_STAR = 5;
const int MINIMUM_STAR = 1;

const int MINIMUM_RESERVES_FOR_DEFAULT_PRICE_FILTER = 10;

typedef std::string Address;

const char HOTEL_DATA_DELIMITER = ',';
const char AMENITIES_DATA_DELIMITER = '|';

const double USER_INITIAL_MONEY = 0;

typedef std::vector<double> WalletRecord;
typedef std::vector<Reserve> Reserves;

const std::string POST_ORDER = "POST";
const std::string GET_ORDER = "GET";
const std::string DELETE_ORDER = "DELETE";
const std::string SIGNUP_ORDER = "signup";
const std::string LOGIN_ORDER = "login";
const std::string LOGOUT_ORDER = "logout";
const std::string WALLET_ORDER = "wallet";
const std::string HOTLES_ORDER = "hotels";
const std::string RESERVES_ORDER = "reserves";
const std::string FILTERS_ORDER = "filters";
const std::string COMMENTS_ORDER = "comments";
const std::string RATINGS_ORDER = "ratings";
const std::string DEFAULT_PRICE_FILTER_ORDER = "default_price_filter";
const std::string MANUAL_WEIGHTS_ORDER = "manual_weights";
const std::string ESTIMATED_WEIGHTS_ORDER = "estimated_weights";
const std::string SORT_ORDER = "sort";
const std::string PROPERTY = "property";
const std::string ASCENDING = "ascending";
const std::string DESCENDING = "descending";
const std::string ORDER = "order";
const std::string ACTIVE = "active";
const std::string TRUE_STR = "true";
const std::string FALSE_STR = "false";
const std::string NULL_VALUE = "";
const std::string EMAIL = "email";
const std::string USER_NAME = "username";
const std::string PASSWORD = "password";
const std::string AMOUNT = "amount";
const std::string COUNT = "count";
const std::string ID = "id";
const std::string CITY = "city";
const std::string MIN_STAR = "min_star";
const std::string MAX_STAR = "max_star";
const std::string MIN_PRICE = "min_price";
const std::string MAX_PRICE = "max_price";
const std::string TYPE = "type";
const std::string QUANTITY = "quantity";
const std::string CHECK_IN = "check_in";
const std::string CHECK_OUT = "check_out";
const std::string HOTEL = "hotel";
const std::string COMMENT = "comment";
const std::string LOCATION = "location";
const std::string CLEANLINESS = "cleanliness";
const std::string STAFF = "staff";
const std::string FACILITIES = "facilities";
const std::string VALUE_FOR_MONEY = "value_for_money";
const std::string OVERALL_RATING = "overall_rating";
const std::string NAME = "name";
const std::string STAR_RATING = "star_rating";
const std::string STANDARD_ROOM_PRICE = "standard_room_price";
const std::string DELUXE_ROOM_PRICE = "deluxe_room_price";
const std::string PREMIUM_ROOM_PRICE = "premium_room_price";
const std::string LUXURY_ROOM_PRICE = "luxury_room_price";
const std::string AVERAGE_ROOM_PRICE = "average_room_price";
const int PERCISION_COUNT = 2;
const int ZERO = 0;
const std::string EMPTY = "Empty";
const std::string NO_RATING = "No Rating";
const std::string RATING_PERSONAL = "rating_personal";

typedef std::vector<std::string> OrderPart;

struct OrderData
{
    OrderPart dataTypes;
    OrderPart dataValues;
};

typedef struct OrderData OrderData;

typedef std::vector<bool> DaysReservationData;

const int MONTH_DAYS_NUMBER = 31;

struct SortSetting
{
    std::string property;
    std::string order;
};

typedef struct SortSetting SortSetting;

struct Weights
{
    bool ifEstimatedWeightsCalculated;
    bool ifManualWeightsActive;
    double location;
    double cleanliness;
    double staff;
    double facilities;
    double valueForMoney;
};

typedef struct Weights Weights;

const double MAXIMUM_RATE = 5;
const int MINIMUM_RATING_NUMBER = 5;
const double EPSILON = 0.0001;
const double STEP_SIZE = 1;
const int NUMBER_OF_ESTIMATES = 1000;

#endif