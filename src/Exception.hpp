#ifndef EXCEPTIONSO_H
#define EXCEPTIONSO_H "EXCEPTIONSO_H"

#include <string>
#include <vector>

class NotFound : public std::exception
{
public:
    NotFound();
    const char* what() const noexcept;

private:
};

class BadRequest : public std::exception
{
public:
    BadRequest();
    const char* what() const noexcept ;

private:
};

class PermissionDenied : public std::exception
{
public:
    PermissionDenied();
    const char* what() const noexcept ;

private:
};

class NotEnoughRoom : public std::exception
{
public:
    NotEnoughRoom();
    const char* what() const noexcept ;

private:
};

class NotEnoughCredit : public std::exception
{
public:
    NotEnoughCredit();
    const char* what() const noexcept ;

private:
};

class InsufficientRatings : public std::exception
{
public:
    InsufficientRatings();
    const char* what() const noexcept ;

private:
};

#endif 