#include "fileconnector.hpp"

int main(){
  const string pricePath = "../prices.txt";
  const string host = "localhost";
  const string port = "3000";
  FileConnector<Bond> priceFileConnector(pricePath, host, port);
  priceFileConnector.Subscribe();
}