#include "fileconnector.hpp"

int main(){
  const string tradePath = "../trades.txt";
  const string host = "localhost";
  const string port = "3002";
  FileConnector<Bond> tradeFileConnector(tradePath, host, port);
  tradeFileConnector.Subscribe();
}