#include "handlers.hpp"
#include "../server/server.hpp"
#include <iostream>
#include "Utrip.hpp"

using namespace std;

int main(int argc, char **argv) {
  ReadData readData(argv[1], argv[2]);
  Utrip utrip(readData.readHotelsData());
  try {
    Server server(8080);
    
    server.get("/signup", new Signup(&utrip));
    server.get("/signupresult", new SignupResult(&utrip));
    server.get("/mainmenu", new MainMenu());
    server.get("/login", new Login(&utrip));
    server.get("/loginresult", new LoginResult(&utrip));
    server.get("/usermenu", new UserMenu(&utrip));
    server.get("/creditinfo", new CreditInfo(&utrip));
    server.get("/increasecredit", new IncreaseCredit(&utrip));
    server.get("/hotelinfopage", new HotelInfoPage(&utrip));
    server.get("/filterresult", new FilterResult(&utrip));

    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}

#include <iostream>



// using namespace std;

// int main(int argc, char* argv[])
// {
//     ReadData readData(argv[1], argv[2]);
//     Utrip utrip(readData.readHotelsData());
//     Interface interface(&utrip);
//     while (cin)
//     {
//         try
//         {
//             interface.runProgram();
//         }
//         catch(const exception& e)
//         {
//             cout << e.what() << endl;
//         }
//     }
//     return 0;
// }