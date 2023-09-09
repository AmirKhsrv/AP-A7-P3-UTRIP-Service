#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <iostream>
#include "Utrip.hpp"

class Signup : public RequestHandler
{
public:
  Signup(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class SignupResult : public RequestHandler
{
public:
  SignupResult(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class Login : public RequestHandler
{
public:
  Login(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class LoginResult : public RequestHandler
{
public:
  LoginResult(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class UserMenu : public RequestHandler
{
public:
  UserMenu(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class MainMenu : public RequestHandler
{
public:
  Response *callback(Request *);
};

class CreditInfo : public RequestHandler
{
public:
  CreditInfo(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class IncreaseCredit : public RequestHandler
{
public:
  IncreaseCredit(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class HotelInfoPage : public RequestHandler
{
public:
  HotelInfoPage(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

class FilterResult : public RequestHandler
{
public:
  FilterResult(Utrip*);
  Response *callback(Request *);
private:
  Utrip* utrip;
};

#endif