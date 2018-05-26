#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace std;
class Server{
  struct users{
    std::string username;
    std::string password;
  };

  private: std::map<std::string,std::string> receivedData;
  private: std::map<std::string, users> userDb;
  private: std::map<std::string, std::map<std::string, std::string>> carsDb;
  public:void connect();
  public:string login(std::string username,std::string password);
  public:string signUp(std::string username,std::string password,std::string confirmPassword);
  public:string addCar();
  public:string showMyCars(std::string username);
};

void Server::connect(){
  typedef boost::asio::ip::udp asioudp;
  boost::asio::io_service io_service;
  asioudp::socket socket(io_service, asioudp::endpoint(asioudp::v4(), 13));
  while (true){
    std::array<char, 1024> recv_buf;
    asioudp::endpoint remote_endpoint;
    boost::system::error_code error;
    std::size_t const received_bytes = socket.receive_from(boost::asio::buffer(recv_buf),remote_endpoint,0,error);
    if (error && error != boost::asio::error::message_size){
      throw boost::system::system_error(error);
    }
    std::string const inputmessage(recv_buf.data(), received_bytes);
    std::stringstream ss;
    ss << inputmessage;
    boost::archive::text_iarchive iarch(ss);
    iarch >> receivedData;
    boost::system::error_code ignored_error;
    int i = std::stoi(receivedData["method"]);

    switch (i) {
      case 1:{ //Login
        std::string response = login(receivedData["username"],receivedData["password"]);
        socket.send_to(boost::asio::buffer(response),remote_endpoint,0,ignored_error);
        break;
      }
      case 2:{ //Register new user
        std::string response = signUp(receivedData["username"],receivedData["password"],receivedData["confirmPassword"]);
        socket.send_to(boost::asio::buffer(response),remote_endpoint,0,ignored_error);
        break;
      }
      case 3:{ //Add New Car
        std::string response = addCar();
        socket.send_to(boost::asio::buffer(response),remote_endpoint,0,ignored_error);
        break;
      }
      case 4:{ //Show cars that user owns
        std::string response = showMyCars(receivedData["username"]);
        socket.send_to(boost::asio::buffer(response),remote_endpoint,0,ignored_error);
        break;
      }
      default:
        break;
    }

  }

}
//Method for login User
string Server::login(std::string username,std::string password){
  auto user = userDb.find(username);
  if(user != userDb.end() && user->second.password == password){
      return "1";
  }
  return "0";

}
//Method for create new user
string Server::signUp(std::string username,std::string password,std::string confirmPassword){
    userDb[username] = users{username,password};
    return "1";
}

//Method for add new Car
string Server::addCar(){
    carsDb[receivedData["carName"]] = {
      {"username",receivedData["username"]},
      {"carName",receivedData["carName"]},
      {"carManufacturer",receivedData["carManufacturer"]},
      {"carSeatingCapacity",receivedData["carSeatingCapacity"]},
      {"carBootSpace",receivedData["carBootSpace"]},
      {"carColor",receivedData["carColor"]},
      {"carFuel",receivedData["carFule"]},
      {"carExtra",receivedData["carExtra"]},
      {"carLocation",receivedData["carLocation"]},
      {"status","1"}
    };
    std::cout << carsDb.size() << '\n';
    return "1";
}
//Method for show cars that user owns
string Server::showMyCars(std::string username){
  std::map<string, std::map<string, string>> Lmap;
  for (std::map<std::string,std::map<string, string>>::iterator it=carsDb.begin(); it!=carsDb.end(); ++it){
    if(it->second["username"] == username){
      Lmap[it->first] = it->second;
    }
  }
  std::stringstream ss;
  boost::archive::text_oarchive oarch(ss);
  oarch << Lmap;
  return ss.str();
}
