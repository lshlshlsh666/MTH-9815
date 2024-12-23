/**
 * utils.hpp
 * A collection of utility functions
 *
 * @author Shuhao Liu
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <thread>

#include "products.hpp"

using namespace std;

std::vector<std::string> BondIdVector = {"91282CLY5", "91282CMB4", "91282CMA6", "91282CLZ2", "91282CLW9", "912810UF3", "912810UE6"};

// join a string vector with a delimiter
string join(const vector<string>& v, const string& delimiter) {
    string res;
    for (const auto& s : v) {
        res += s + delimiter;
    }
    return res.substr(0, res.size() - delimiter.size());
}

string getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // change the system time to local time
    std::tm now_tm = *std::localtime(&now_c);

    // use stringstream to format the time
    stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // get the milliseconds separately
    auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    ss << '.' << std::setfill('0') << std::setw(3) << milli.count();

    return ss.str();
}

// change time point format to string 
string getTime(std::chrono::system_clock::time_point now) {
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);
    stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    ss << '.' << std::setfill('0') << std::setw(3) << milli.count();
    return ss.str();
}

template <typename T>
using ProductConstructor = std::function<T()>;

// Define a map from CUSIPs to product constructors
template <typename T>
std::map<string, ProductConstructor<T>> productConstructors = {
    {"91282CLY5", []() { return Bond("91282CLY5", CUSIP, "T2Y", 0.04250, from_string("2026/11/30")); }},
    {"91282CMB4", []() { return Bond("91282CMB4", CUSIP, "T3Y", 0.04000, from_string("2027/12/15")); }},
    {"91282CMA6", []() { return Bond("91282CMA6", CUSIP, "T5Y", 0.04125, from_string("2029/11/30")); }},
    {"91282CLZ2", []() { return Bond("91282CLZ2", CUSIP, "T7Y", 0.04125, from_string("2031/11/30")); }},
    {"91282CLW9", []() { return Bond("91282CLW9", CUSIP, "T10Y", 0.04250, from_string("2034/11/15")); }},
    {"912810UF3", []() { return Bond("912810UF3", CUSIP, "T20Y", 0.04625, from_string("2044/11/15")); }},
    {"912810UE6", []() { return Bond("912810UE6", CUSIP, "T30Y", 0.04500, from_string("2054/11/15")); }},
};

template <typename T>
T getProductObject(const string& cusip) {
    auto it = productConstructors<T>.find(cusip);
    if (it == productConstructors<T>.end()) {
        throw std::invalid_argument("Unknown CUSIP: " + cusip);
    }
    return it->second();
}


// function to calculate PV01
double calculate_pv01(double face_value, double coupon_rate, double yield_rate, int years_to_maturity, int frequency) {
    double coupon = face_value * coupon_rate / frequency;
    double pv01 = 0.0;
    for (int t = 1; t <= years_to_maturity * frequency; ++t) {
        double discount_factor = 1.0 / pow(1.0 + yield_rate / frequency, t);
        pv01 += coupon * discount_factor;
    }
    pv01 += face_value / pow(1.0 + yield_rate / frequency, years_to_maturity * frequency);
    double pv01_initial = pv01;
    yield_rate += 0.0001;
    pv01 = 0.0;
    for (int t = 1; t <= years_to_maturity * frequency; ++t) {
        double discount_factor = 1.0 / pow(1.0 + yield_rate / frequency, t);
        pv01 += coupon * discount_factor;
    }
    pv01 += face_value / pow(1.0 + yield_rate / frequency, years_to_maturity * frequency);
    double pv01_change = pv01_initial - pv01;
    return pv01_change;
}


std::map<string, double> pv01 = {
    {"91282CLY5", calculate_pv01(1000, 0.01750, 0.04250, 2, 2)},
    {"91282CMB4", calculate_pv01(1000, 0.01875, 0.04000, 3, 2)},
    {"91282CMA6", calculate_pv01(1000, 0.02000, 0.04125, 5, 2)},
    {"91282CLZ2", calculate_pv01(1000, 0.02125, 0.04125, 7, 2)},
    {"91282CLW9", calculate_pv01(1000, 0.02250, 0.04250, 10, 2)},
    {"912810UF3", calculate_pv01(1000, 0.02500, 0.04625, 20, 2)},
    {"912810UE6", calculate_pv01(1000, 0.02750, 0.04500, 30, 2)},
};

// Get unit PV01 value from CUSIP
double getPV01(const string& cusip) {
    auto it = pv01.find(cusip);
    if (it == pv01.end()) {
        throw std::invalid_argument("Unknown CUSIP: " + cusip);
    }
    return it->second;
}

// change US treasury prices from fractional notation to decimal notation
double convertPrice(const string& priceStr) {
    // if the price is in decimal notation, return it directly
    if (priceStr.find_first_of('-') == string::npos) {
        return stod(priceStr);
    }

    // if the price is in fractional notation, convert it to decimal notation
    // first, split the string into two parts
    size_t pos = priceStr.find_first_of('-');
    string str1 = priceStr.substr(0, pos);
    string str2 = priceStr.substr(pos+1, 2);
    string str3 = priceStr.substr(pos+3, 1);
    if (str3 == "+") {
        str3 = "4";
    }

    double res = stod(str1) + stod(str2)*1.0 / 32.0 + stod(str3)*1.0 / 256.0;
    return res;
}

// change prices from decimal notation to fractional notation
string convertPrice(double price) {
    int intPart = floor(price);
    double fraction = price - intPart;
    int xy = floor(fraction * 32);
    int z = static_cast<int>((fraction*256)) % 8;
    // be careful about corner cases
    return to_string(intPart) + "-" + (xy < 10 ? "0" : "") + std::to_string(xy) + (z == 4 ? "+" : std::to_string(z));

}

// Bond price class
class BondPrice {
private:
    int integerPart;
    int decimalPart_32th;
    int decimalPart_256th;
public:
    BondPrice() : integerPart(0), decimalPart_32th(0), decimalPart_256th(0) {}
    BondPrice(double price) {
        integerPart = (int)price;
        decimalPart_32th = (int)((price - integerPart) * 32);
        decimalPart_256th = (int)((price - integerPart - decimalPart_32th / 32) * 256);
    }
    BondPrice(int decimalPart_256th) :
        integerPart(0), decimalPart_32th(0), decimalPart_256th(decimalPart_256th) {}
    BondPrice(int _integerPart, int _decimalPart_32th, int _decimalPart_256th) :
        integerPart(_integerPart), decimalPart_32th(_decimalPart_32th), decimalPart_256th(_decimalPart_256th) {}
    BondPrice(std::string price) {
        std::string integerPartStr = price.substr(0, price.find('-'));
        std::string decimalPartStr = price.substr(price.find('-') + 1);
        integerPart = std::stoi(integerPartStr);
        decimalPart_32th = std::stoi(decimalPartStr.substr(0, 2));
        decimalPart_256th = std::stoi(decimalPartStr.substr(2));
    }
    std::string ToString() {
        std::stringstream ss;
        if (decimalPart_256th != 4) {
            ss << integerPart << "-" << std::setw(2) << std::setfill('0') << decimalPart_32th << decimalPart_256th;
        } else {
            ss << integerPart << "-" << std::setw(2) << std::setfill('0') << decimalPart_32th << "+";
        }
        return ss.str();
    }
    double ToDouble() {
        return integerPart + decimalPart_32th / 32.0 + decimalPart_256th / 256.0;
    }

    BondPrice operator+(int other_decimalPart_256th) {
        int sum_integerPart = integerPart;
        int sum_decimalPart_32th = decimalPart_32th;
        int sum_decimalPart_256th = decimalPart_256th + other_decimalPart_256th;
        
        sum_decimalPart_32th += sum_decimalPart_256th / 8;
        sum_decimalPart_256th %= 8;
        sum_integerPart += sum_decimalPart_32th / 32;
        sum_decimalPart_32th %= 32;

        return BondPrice(sum_integerPart, sum_decimalPart_32th, sum_decimalPart_256th);
    }

    BondPrice operator-(int other_decimalPart_256th) {
        int diff_integerPart = integerPart;
        int diff_decimalPart_32th = decimalPart_32th;
        int diff_decimalPart_256th = decimalPart_256th - other_decimalPart_256th;

        if (diff_decimalPart_256th < 0) {
            diff_decimalPart_32th -= 1;
            diff_decimalPart_256th += 8;
        }
        diff_decimalPart_32th += diff_decimalPart_256th / 8;
        diff_decimalPart_256th %= 8;

        if (diff_decimalPart_32th < 0) {
            diff_integerPart -= 1;
            diff_decimalPart_32th += 32;
        }
        diff_integerPart += diff_decimalPart_32th / 32;
        diff_decimalPart_32th %= 32;

        return BondPrice(diff_integerPart, diff_decimalPart_32th, diff_decimalPart_256th);
    }

    BondPrice operator+=(int other_decimalPart_256th) {
        decimalPart_256th += other_decimalPart_256th;

        decimalPart_32th += decimalPart_256th / 8;
        decimalPart_256th %= 8;
        integerPart += decimalPart_32th / 32;
        decimalPart_32th %= 32;
        return *this;
    }

    BondPrice operator-=(int other_decimalPart_256th) {
        decimalPart_256th -= other_decimalPart_256th;

        if (decimalPart_256th < 0) {
            decimalPart_32th -= 1;
            decimalPart_256th += 8;
        }
        decimalPart_32th += decimalPart_256th / 8;
        decimalPart_256th %= 8;

        if (decimalPart_32th < 0) {
            integerPart -= 1;
            decimalPart_32th += 32;
        }
        integerPart += decimalPart_32th / 32;
        decimalPart_32th %= 32;
        return *this;
    }

    bool operator<(const BondPrice& other) const {
        if (integerPart < other.integerPart) {
            return true;
        } else if (integerPart == other.integerPart) {
            if (decimalPart_32th < other.decimalPart_32th) {
                return true;
            } else if (decimalPart_32th == other.decimalPart_32th) {
                return decimalPart_256th < other.decimalPart_256th;
            }
        }
        return false;
    }

    bool operator>(const BondPrice& other) const {
        return other < *this;
    }

    bool operator==(const BondPrice& other) const {
        return integerPart == other.integerPart && decimalPart_32th == other.decimalPart_32th && decimalPart_256th == other.decimalPart_256th;
    }


    friend std::ostream& operator<<(std::ostream& os, BondPrice& price) {
        os << price.ToString();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, BondPrice& price) {
        std::string priceStr;
        is >> priceStr;
        price = BondPrice(priceStr);
        return is;
    }
};


// Generate a price.txt file with oscillating prices and spreads
void GeneratePriceTxt() {
    std::string filename = "../prices.txt";
    if (std::ifstream(filename)) {
        return;
    }
    std::ofstream priceFile(filename);
    if (!priceFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Initialize price and spread ranges
    BondPrice mid_price(99, 0, 0);  // Mid price
    bool priceIncreasing = false; // Direction of price movement

    // rdg for spread
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5);

    for (int i = 0; i < 1000000; ++i) {
        for (std::string productId : BondIdVector) {
            // Adjust the spread unit
            if (mid_price == BondPrice(101, 0, 0) || mid_price == BondPrice(99, 0, 0)) {
                priceIncreasing = !priceIncreasing;
            }

            // Format and write the line
            int spread_unit = dist(gen) ? 2 : 4;  // Spread unit, 1 means 1/128, 2 means 1/64
            priceFile << productId << "," << mid_price << "," << spread_unit << std::endl;
            if (priceIncreasing) {
                mid_price += 1;
            } else {
                mid_price -= 1;
            }
        }
    }

    priceFile.close();
}

string GenerateRandomId(unsigned int length = 10) {
    // generate 10-digit random trade id
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    std::string tradeId = "";
    for (int i = 0; i < length; ++i) {
        tradeId += std::to_string(dist(gen));
    }
    return tradeId;
}

// Generate a trade.txt file
void GenerateTradeTxt() {
    std::string filename = "../trades.txt";
    if (std::ifstream(filename)) {
        return;
    }
    std::ofstream tradeFile(filename);
    if (!tradeFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // rdg for spread
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5);

    vector<string> bookVector = {"TRSY1", "TRSY2", "TRSY3"};
    int book_cnt = 0;
    long quantity = 1000000;
    for (int i = 0; i < 10; ++i) {
        for (std::string productId : BondIdVector) {
            string tradeId = GenerateRandomId();
            string side = dist(gen) ? "BUY" : "SELL";
            BondPrice price = side == "BUY" ? BondPrice(99, 0, 0) : BondPrice(100, 0, 0);
            string book = bookVector[book_cnt % 3];
            tradeFile << productId << "," << tradeId << "," << price << "," << book << "," << quantity << "," << side << std::endl;
            book_cnt++;
            quantity += 1000000;
            if (quantity == 6000000) {
                quantity = 10000000;
            }
        }
    }

    tradeFile.close();
}

// Generate a marketdata.txt file
void GenerateMarketDataTxt() {
    std::string filename = "../marketdata.txt";
    if (std::ifstream(filename)) {
        return;
    }
    std::ofstream marketDataFile(filename);
    if (!marketDataFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Initialize price and spread ranges
    BondPrice bid_price(99, 0, 0);  // Mid price
    int spread_unit = 1; // Spread unit, 1 means 1/128, 2 means 2/128...
    bool priceIncreasing = false; // Direction of price movement
    bool spreadIncreasing = false; // Direction of spread movement

    for (int i = 0; i < 1000000; ++i) {
        for (std::string productId : BondIdVector) {
            // Adjust the spread unit
            if (bid_price == BondPrice(101, 0, 0) || bid_price == BondPrice(99, 0, 0)) {
                priceIncreasing = !priceIncreasing;
            }
            if (spread_unit == 4 || spread_unit == 1) {
                spreadIncreasing = !spreadIncreasing;
            }

            // Format and write the line
            marketDataFile << productId << ",";
            BondPrice bid = bid_price, ask = bid_price + spread_unit;
            long size = 1000000;
            marketDataFile << bid << "," << size << "," << ask << "," << size;
            for (int j = 0; j < 4; ++j) {
                bid -= 1;
                ask += 1;
                size += 1000000;
                marketDataFile << "," << bid << "," << size << "," << ask << "," << size;
            }
            marketDataFile << std::endl;

            if (priceIncreasing) {
                bid_price += 1;
            } else {
                bid_price -= 1;
            }
            if (spreadIncreasing) {
                spread_unit += 1;
            } else {
                spread_unit -= 1;
            }
        }
    }

    marketDataFile.close();
}

// Generate a inquiry.txt file
void GenerateInquiryTxt() {
    std::string filename = "../inquiries.txt";
    if (std::ifstream(filename)) {
        return;
    }
    std::ofstream inquiryFile(filename);
    if (!inquiryFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // rdg for spread
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5);
    std::uniform_int_distribution<int> dist2(0, 512);

    long quantity = 1000000;
    for (int i = 0; i < 10; ++i) {
        for (std::string productId : BondIdVector) {
            string inquiryId = GenerateRandomId();
            string side = dist(gen) ? "BUY" : "SELL";
            int price_rd = dist2(gen);
            BondPrice price(99, 0, 0);
            price += price_rd;
            string state = "RECEIVED";
            inquiryFile << inquiryId << "," << productId << "," << side << "," << quantity << "," << price << "," << state << std::endl;
            quantity += 1000000;
            if (quantity == 6000000) {
                quantity = 10000000;
            }
        }
    }

    inquiryFile.close();
}

// function to check whether a thread has completed and join it if yes
// introduce the try-catch block as required
void join(std::thread& t) {
    if (t.joinable()) {
        t.join();
    }
    else {
        try {
            t.join();
        }
        catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
}

#endif
