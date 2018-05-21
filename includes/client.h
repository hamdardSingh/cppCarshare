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
  public:void showMenu();
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
      showMenu();
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

void Client::showMenu(){
  int choice = 0;
  do{
    system("clear");
    cout << "Please make your selection\n";
    cout << "1 - Add Car\n";
    cout << "2 - Show My Cars\n";
    cout << "3 - Rent A Car\n";
    cout << "4 - Quit\n";
    cout << "Selection: ";
    choice = getInput();
      switch (choice) {
        case '1':
            std::cout << "----------Enter Car Details-----------" << '\n';
          break;
        case '2':
              std::cout << "-----------My Cars----------" << '\n';
          break;
        case '3':
                std::cout << "-----------Select Car----------" << '\n';
          break;
        case '4':
          break;
        default:
          break;
      }
  }while(choice != '4');

}
