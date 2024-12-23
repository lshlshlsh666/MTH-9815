#include "fileconnector.hpp"

int main(){
  const string inquiryPath = "../inquiries.txt";
  const string host = "localhost";
  const string port = "3003";
  FileConnector<Bond> inquiryFileConnector(inquiryPath, host, port);
  inquiryFileConnector.Subscribe();
}