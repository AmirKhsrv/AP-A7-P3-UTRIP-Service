#include "Exception.hpp"

using namespace std;

NotFound::NotFound()
{

}

BadRequest::BadRequest()
{
    
}

PermissionDenied::PermissionDenied()
{
    
}

NotEnoughRoom::NotEnoughRoom()
{

}

InsufficientRatings::InsufficientRatings()
{

}

NotEnoughCredit::NotEnoughCredit()
{

}

const char* NotFound::what() const noexcept 
{
    return "Not Found";
}

const char* BadRequest::what() const noexcept 
{
    return "Bad Request";
}

const char* PermissionDenied::what() const noexcept 
{
    return "Permission Denied";
}

const char* NotEnoughRoom::what() const noexcept 
{
    return "Not Enough Room";
}

const char* NotEnoughCredit::what() const noexcept 
{
    return "Not Enough Credit";
}

const char* InsufficientRatings::what() const noexcept 
{
    return "Insufficient Ratings";
}
