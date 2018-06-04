#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE serverTest
#include <boost/test/included/unit_test.hpp>
#include "../server/includes/handel.h"
Server server;

//test for sign up
BOOST_AUTO_TEST_CASE(signUpTest){
  BOOST_CHECK(server.signUp("username","password","password")=="1");
}
//test for login
BOOST_AUTO_TEST_CASE(loginTest){
  BOOST_CHECK(server.login("username","password")=="1");
}
//test for failed login
BOOST_AUTO_TEST_CASE(loginFailTest){
  BOOST_CHECK(server.login("username","invalidpassword")=="0");
}

//test for add car to pool
BOOST_AUTO_TEST_CASE(addCarTest){
  server.receivedData["usename"] = "username";
  server.receivedData["carName"] = "carName";
  server.receivedData["carManufacturer"] = "carManufacturer";
  server.receivedData["carSeatingCapacity"] = "carSeatingCapacity";
  server.receivedData["carBootSpace"] = "carBootSpace";
  server.receivedData["carFuel"] = "carFuel";
  server.receivedData["carColor"] = "carColor";
  server.receivedData["carLocation"] = "carLocation";
  server.receivedData["carExtra"] = "carExtra";
  server.receivedData["status"] = "1";
  server.receivedData["bookedUser"] = "";
  BOOST_CHECK(server.addCar()=="1");
}

//test for book car
BOOST_AUTO_TEST_CASE(bookCarTest){
  server.receivedData["bookedCarName"] = "carName";
  BOOST_CHECK(server.bookCar()=="1");
}

//test for return car
BOOST_AUTO_TEST_CASE(returnCarTest){
  server.receivedData["bookedCarName"] = "carName";
  BOOST_CHECK(server.returnCar()=="1");
}
