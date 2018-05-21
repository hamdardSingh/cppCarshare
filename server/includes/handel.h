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
  public:void connect();
  public:string login(std::string username,std::string password);
  public:string signUp(std::string username,std::string password,std::string confirmPassword);
};

void Server::connect(){
  typedef boost::asio::ip::udp asioudp;
  boost::asio::io_service io_service;
  asioudp::socket socket(io_service, asioudp::endpoint(asioudp::v4(), 13));
  while (true){
    std::array<char, 256> recv_buf;
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
