#include <string>
#include <sstream>
#include "handlers.hpp"
using namespace std;

Signup::Signup(Utrip* ut)
{
  utrip = ut;
}

Response *Signup::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  utrip->logoutUser();
  ostringstream body;
  body 
  << "<!DOCTYPE html>" << endl
  << "<html>" << endl
  << "<body>" << endl

  << "<form action='/mainmenu'>" << endl
  << "<input type='submit' value='Home page' />" << endl
  << "</form>" << endl

  << "<form action='/signupresult' method='get'>" << endl
  << "Username: <input name='username' type='text' name='username' placeholder='username' /> <br/>" << endl
  << "Password: <input name='password' type='text' placeholder='password' /> <br/>" << endl
  << "Repeat Password: <input name='repassword' type='text' placeholder='password' /> <br/>" << endl
  << "Email: <input name='email' type='text' placeholder='email' /> <br/>" << endl
  << "<button type='submit' value='save'>Signup</button>" << endl
  << "</form>"

  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

SignupResult::SignupResult(Utrip* ut)
{
  utrip = ut;
}

Response *SignupResult::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string username = req->getQueryParam("username");
  string password = req->getQueryParam("password");
  string email = req->getQueryParam("email");

  ostringstream body;
  body 
    << "<!DOCTYPE html>" << endl
    << "<html>" << endl
    << "<body>" << endl;
    if (utrip->checkUserNameAndEmailDuplication(email, username))
    {
      body << "<h1>Email or Username already taken. try another one.</h1>" << endl
      << "<form action='/signup'>" << endl
      << "<input type='submit' value='Return' />" << endl
      << "</form>" << endl;
      res->setBody(body.str());
      return res;    
    }
    utrip->registerUser(email, username, password);
    body << "<h1>User successfully added.</h1>" << endl
    << "<form action='/usermenu'>" << endl
    << "<input type='submit' value='Continue to account' />" << endl
    << "</form>" << endl;
  res->setBody(body.str());
  return res;
}

Login::Login(Utrip* ut)
{
  utrip = ut;
}

Response *Login::callback(Request *)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body 
  << "<!DOCTYPE html>" << endl
  << "<html>" << endl
  << "<body>" << endl

  << "<form action='/mainmenu'>" << endl
  << "<input type='submit' value='Home page' />" << endl
  << "</form>" << endl

  << "<form action='/loginresult' method='get'>" << endl
  << "Email: <input name='email' type='text' placeholder='email' /> <br/>" << endl
  << "Password: <input name='password' type='text' placeholder='password' /> <br/>" << endl
  << "<button type='submit' value='save'>Login</button>" << endl
  << "</form>"

  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

LoginResult::LoginResult(Utrip* ut)
{
  utrip = ut;
}

Response *LoginResult::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string email = req->getQueryParam("email");
  string password = req->getQueryParam("password");

  ostringstream body;
  body 
    << "<!DOCTYPE html>" << endl
    << "<html>" << endl
    << "<body>" << endl;
    try 
    {
      utrip->loginUser(email, password);
      body << "<h1>User successfully logined.</h1>" << endl
      << "<form action='/usermenu'>" << endl
      << "<input type='submit' value='Continue to account' />" << endl
      << "</form>" << endl;
      res->setBody(body.str());
      res->setSessionId(email);
      return res;   
    } catch(exception& ex)
    {
      body << "<h1>Wrong email or password. Try again.</h1>" << endl
      << "<form action='/login'>" << endl 
      << "<input type='submit' value='return' />" << endl
      << "</form>" << endl;
      res->setBody(body.str());
      return res;
    }
}

Response *MainMenu::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body 
    << "<!DOCTYPE html>" << endl
    << "<html>" << endl
    << "<body>" << endl
    << "<form action='/signup'>" << endl
    << "<input type='submit' value='Signup' />" << endl
    << "</form>" << endl
    << "<form action='/login'>" << endl
    << "<input type='submit' value='Login' />" << endl
    << "</form>" << endl
    << "</body>" << endl
    << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

UserMenu::UserMenu(Utrip* ut)
{
  utrip = ut;
}

Response *UserMenu::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body 
  << "<!DOCTYPE html>" << endl
  << "<html>" << endl
  << "<body>" << endl

  << "<form action='/login'>" << endl
  << "<input type='submit' value='Logout' />" << endl
  << "</form>" << endl

  << "<form action='/creditinfo'>" << endl
  << "<input type='submit' value='Credit info' />" << endl
  << "</form>" << endl

  << "<form action='/filterresult' method='get'>" << endl
  << "Minimum star: <input name='minstar' type='text' placeholder='minimum star rating' /> <br/>" << endl
  << "Maximum star: <input name='maxstar' type='text' placeholder='maximum star rating' /> <br/>" << endl
  << "<button type='submit' value='save'>Apply</button>" << endl
  << "</form>"

  << "<h1>Hotels</h1>" << endl

  << "<table border=1>" << endl
  << "                <tr>" << endl
  << "                    <th>Property name</th>" << endl
  << "                    <th>Star rating</th>" << endl
  << "                    <th>City</th>" << endl
  << "                    <th>image</th>" << endl
  << "                    <th>&nbsp;</th>" << endl
  << "                </tr>" << endl;
  Hotels hotels = utrip->getHotels();
  for (int i = 0; (unsigned)i < hotels.size(); i++) {
    body
      << "                    <tr>" << endl
      << "                        <td>" << hotels[i]->getHotelInfo()->propertyName << "</td>" << endl
      << "                        <td>" << hotels[i]->getHotelInfo()->hotelFacility.hotelStarRating << "</td>" << endl
      << "                        <td>" << hotels[i]->getHotelInfo()->location.city << "</td>" << endl
      << "                        <td> <img src='" << hotels[i]->getHotelInfo()->imageUrl << "' width='150' height='150'></td>" << endl
      << "                        <td><a href='hotelinfopage?id=" << hotels[i]->getHotelInfo()->uniqueId << "'>Show hotel</a></td>" << endl
      << "                    </tr>" << endl;
    }
  body
  << "            </table>" << endl

  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

CreditInfo::CreditInfo(Utrip* ut)
{
  utrip = ut;
}

Response *CreditInfo::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  ostringstream body;
  body 
  << "<!DOCTYPE html>" << endl
  << "<html>" << endl
  << "<body>" << endl
  
  << "<form action='/usermenu'>" << endl
  << "<input type='submit' value='Return to user menu' />" << endl
  << "</form>" << endl

  << "<b>Current Credit: " << utrip->getUserWalletRecord(1)[0] << "<b>" << endl
  << "<form action='/increasecredit'>" << endl
  << "Amount : <input name='amount' type='text' name='amount' placeholder='money amount' /> <br/>" << endl
  << "<input type='submit' value='Increase' />" << endl
  << "</form>" << endl

  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

IncreaseCredit::IncreaseCredit(Utrip* ut)
{
  utrip = ut;
}

Response *IncreaseCredit::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  double moneyAmount = stod(req->getQueryParam("amount"));
  utrip->increaseMoney(moneyAmount);

  ostringstream body;
  body 
  << "<!DOCTYPE html>" << endl
  << "<html>" << endl
  << "<body>" << endl

  << "<h1>Credit successfully increased.</h1>" << endl

  << "<form action='/creditinfo'>" << endl
  << "<input type='submit' value='Return' />" << endl
  << "</form>" << endl

  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

HotelInfoPage::HotelInfoPage(Utrip* ut)
{
  utrip = ut;
}

Response *HotelInfoPage::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string id = req->getQueryParam("id");
  Hotel* hotel = utrip->getSpecificHotel(id);

  ostringstream body;
  body 
  << "<!DOCTYPE html>" << endl
  << "<html>" << endl
  << "<body>" << endl
  
  << "<h2> " << hotel->getHotelInfo()->propertyName << "</h2>"

  << "<img src='" << hotel->getHotelInfo()->imageUrl << "' width='500' height='500'>" << endl

  << "<p>" << hotel->getHotelInfo()->hotelFacility.hotelOverview << "</p>" << endl

  << "<p>Hotel ameneties : </p>" << endl
  << "<ul>" << endl;
  for (int i = 0; (unsigned)i < hotel->getHotelInfo()->hotelFacility.propertyAmenities.size(); i++)
    body << "<li>" <<hotel->getHotelInfo()->hotelFacility.propertyAmenities[i] << "</li>" << endl;
  body << "</ul>  " << endl

  << "<p>Hotel star rating : " << hotel->getHotelInfo()->hotelFacility.hotelStarRating << "</p>" << endl

  << "<p>City : " << hotel->getHotelInfo()->location.city << "</p>" << endl


  << "<table border=1>" << endl
  << "                <tr>" << endl
  << "                    <th>Room type</th>" << endl
  << "                    <th>Room count</th>" << endl
  << "                    <th>Cost per night</th>" << endl
  << "                </tr>" << endl
  << "                    <tr>" << endl
  << "                        <td>Standard room</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.standard.numberOfRooms << "</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.standard.roomCost << "</td>" << endl
  << "                    </tr>" << endl
  << "                </tr>" << endl
  << "                    <tr>" << endl
  << "                        <td>Deluxe room</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.deluxe.numberOfRooms << "</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.deluxe.roomCost << "</td>" << endl
  << "                    </tr>" << endl
  << "                </tr>" << endl
  << "                    <tr>" << endl
  << "                        <td>Luxury room</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.luxury.numberOfRooms << "</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.luxury.roomCost << "</td>" << endl
  << "                    </tr>" << endl
  << "                </tr>" << endl
  << "                    <tr>" << endl
  << "                        <td>Premium room</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.premium.numberOfRooms << "</td>" << endl
  << "                        <td>" << hotel->getHotelInfo()->hotelRoomsData.premium.roomCost << "</td>" << endl
  << "                    </tr>" << endl 
  << "            </table>" << endl

  << "<form action='/usermenu'>" << endl
  << "<input type='submit' value='Return to user menu' />" << endl
  << "</form>" << endl

  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

FilterResult::FilterResult(Utrip* ut)
{
  utrip = ut;
}

Response *FilterResult::callback(Request * req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  int minStar = stoi(req->getQueryParam("minstar"));
  int maxStar = stoi(req->getQueryParam("maxstar"));
  utrip->addStarSpanFilter(minStar, maxStar);

  ostringstream body;
  body 
    << "<!DOCTYPE html>" << endl
    << "<html>" << endl
    << "<body>" << endl;
    body << "<h1>Filter successfully added.</h1>" << endl
    << "<form action='/usermenu'>" << endl 
    << "<input type='submit' value='return' />" << endl
    << "</form>" << endl

    << "</body>" << endl
    << "</html>" << endl;
    res->setBody(body.str());
    return res;
}