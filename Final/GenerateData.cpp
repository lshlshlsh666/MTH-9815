#include "utils.hpp"

#include <iostream>
#include <filesystem>

int main() {
	std::cout << "Generating data..." << std::endl;
	GeneratePriceTxt();
	GenerateTradeTxt();
	GenerateMarketDataTxt();
	GenerateInquiryTxt();
	std::cout << "Data generated." << std::endl;
}