#include <iostream>
#include <string>
#include <map>
#include <string>
#include "network.h"
using namespace std;
class Client{
  private: network Network;
  private: std::map<std::string,std::string> client;
  public:int getInput();
  public:void start();
  public:int login(std::string message);
  public:int signUp(std::string message);
  public:void showMenu(std::string message);
  public:void addCar();
  public:void showMyCars();
};

int Client::getInput(){
  char choice;
  std::cin >> choice;
  return choice;
}

void Client::start(){
  cout << "Please make your selection\n";
  cout << "1 - Login\n";
  cout << "2 - Register\n";
  cout << "3 - Quit\n";
  cout << "Selection: ";
}

int Client::login(std::string message){
  system("clear");
  client["method"] = "1";
  std::cout << "\e[1m" << "------> Login <------" << "\e[0m" <<'\n';
  if(message!=  ""){
    std::cout << message << '\n';
  }
  std::cout << "ENTER USERNAME: ";
  std::cin >> client["username"];
  std::cout << "ENTER Password: ";
  std::cin >> client["password"];
  if(Network.send(client)=="1"){
      showMenu("");
  }else{
    login("Invalid username or password");
  }

  return 0;
}

int Client::signUp(std::string message){
  system("clear");
  std::cout << "\e[1m" << "------> Register New User <------" << "\e[0m" <<'\n';
  if(message!=  ""){
    std::cout << message << '\n';
  }
  std::cout << "ENTER USERNAME: ";
  std::cin >> client["username"];
  std::cout << "ENTER Password: ";
  std::cin >> client["password"];
  std::cout << "Confirm Password: ";
  std::cin >> client["confirmPassword"];
  client["method"] = "2";
  if(client["password"] != client["confirmPassword"]){
    system("clear");
    signUp("*New & repeat password doesn't match");
  }else{
    Network.send(client);
    login("New Registration Successful!!");
  }
  return 0;
}

void Client::showMenu(std::string message){
  int choice = 0;
  do{
    system("clear");
    std::cout << "\e[1m" << "------> Please make your selection <------" << "\e[0m" << '\n';
    if(message!=  ""){
      std::cout << message << '\n';
    }
    cout << "1 - Add Car\n";
    cout << "2 - Show My Cars\n";
    cout << "3 - Rent A Car\n";
    cout << "4 - Quit\n";
    cout << "Selection: ";
    choice = getInput();
      switch (choice) {
        case '1':
              addCar();
          break;
        case '2':
              showMyCars();
          break;
        case '3':
              std::cout << "\e[1m" << "------> Book new car <------" << "\e[0m" << '\n';
          break;
        case '4':
          break;
        default:
          break;
      }
  }while(choice != '4');

}

void Client::addCar(){
  std::cout << "\e[1m" << "------> Add new car to pool <------" << "\e[0m" << '\n';
  client["method"] = "3";
  std::cout << "ENTER CAR NAME: ";
  std::cin >> client["carName"];
  std::cout << "CAR MANUFACTURER: ";
  std::cin >> client["carManufacturer"];
  std::cout << "SEATING CAPACITY: ";
  std::cin >> client["carSeatingCapacity"];
  std::cout << "BOOT SPACE: ";
  std::cin >> client["carBootSpace"];
  std::cout << "COLOR: ";
  std::cin >> client["carColor"];
  std::cout << "FUEL TYPE: ";
  std::cin >> client["carFuel"];
  std::cout << "EXTRA INFO: ";
  std::cin >> client["carExtra"];
  std::cout << "Location: ";
  std::cin >> client["carLocation"];
  if(Network.send(client)=="1"){
    showMenu("New car successfully added!!");
  }
}

void Client::showMyCars(){

  client["method"] = "4";
  std::map<std::string, std::map<std::string, std::string>> myCars;

  std::string myCarsString = Network.send(client);
  std::stringstream ss;
  ss << myCarsString;
  boost::archive::text_iarchive iarch(ss);
  iarch >> myCars;
  char choice;
  do{
    system("clear");
    std::cout << "\e[1m" << "------> My cars <------" << "\e[0m" << '\n';
    for (std::map<std::string,std::map<string, string>>::iterator it=myCars.begin(); it!=myCars.end(); ++it){
      std::cout << it->second["carName"] << '\n';
    }
    std::cout << "9 - QUIT" << '\n' << "Selection: ";

    choice = getInput();
      switch (choice) {
        case '1':
              addCar();
          break;
        case '2':
              showMyCars();
          break;
        case '3':
              std::cout << "\e[1m" << "------> Book new car <------" << "\e[0m" << '\n';
          break;
        case '4':
          break;
        default:
          break;
      }
  }while(choice != '9');
}
