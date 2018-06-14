//client entry point
#include "includes/client.h"
int main(){
  Client c;
  char choice = '0';

  do{
    system("clear");
    c.start();
    choice = c.getInput();
    switch (choice) {
      case '1':
        c.login("");
        break;
      case '2':
        c.signUp("");
        break;
      case '3':
        std::cout << "Goodbye!!" << '\n';
        break;
      default:
        break;
    }
  }while (choice != '3' );

  return 0;
}
