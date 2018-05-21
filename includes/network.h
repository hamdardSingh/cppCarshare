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
class network{
  public: std::string host = "127.0.0.1";
  public: std::string send(std::map<std::string,std::string> networkData);
};

string network::send(std::map<string,string> networkData){
  typedef boost::asio::ip::udp asioudp;
  boost::asio::io_service io_service;
  asioudp::endpoint receiver_endpoint = asioudp::endpoint(boost::asio::ip::address_v4::from_string(host),13);
  asioudp::socket socket(io_service);
  socket.open(asioudp::v4());
  std::stringstream ss;
  boost::archive::text_oarchive oarch(ss);
  oarch << networkData;
  socket.send_to(boost::asio::buffer(ss.str()), receiver_endpoint);
  std::array<char, 128> recv_buf;
  asioudp::endpoint sender_endpoint;
  size_t const len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
  std::string const received_message(recv_buf.data(), len);
  return received_message;
}
