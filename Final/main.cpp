/**
 * main.hpp
 * Main function to start six trading system servers
 * 
 * External data flows in the system through:
 * 	1. price data -> pricing service -> algo streaming service -> streaming service -> historical data service
	   (another data flow: pricing service -> GUI service -> GUI data output)
 * 	2. orderbook data -> market data service -> algo execution service -> execution service -> historical data service
 * 	   (another data flow: execution service -> trade booking service -> position service -> risk service -> historical data service)
 * 	3. trade data -> trade booking service -> position service -> risk service -> historical data service
 * 	4. inquiry data -> inquiry service -> historical data service
 * 	
 * @author Shuhao Liu
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <thread>

#include "soa.hpp"
#include "products.hpp"
#include "marketdataservice.hpp"
#include "pricingservice.hpp"
#include "riskservice.hpp"
#include "executionservice.hpp"
#include "positionservice.hpp"
#include "inquiryservice.hpp"
#include "historicaldataservice.hpp"
#include "streamingservice.hpp"
#include "algostreamingservice.hpp"
#include "tradebookingservice.hpp"
#include "algoexecutionservice.hpp"
#include "guiservice.hpp"
#include "utils.hpp"

using namespace std;

/**
 * server thread function
 * The whole system is designed so that subscribe() method
 * opens a separate process and listens to the data on the socket
 */
template<typename T>
void Server(T& service)
{
	service.GetConnector()->Subscribe();
}

int main(int, char**){
	string resPath = "../output";
	if (filesystem::exists(resPath)) {
		filesystem::remove_all(resPath);
	}
	filesystem::create_directory(resPath);

	PricingService<Bond> pricingService("localhost", "3000");
	MarketDataService<Bond> marketDataService("localhost", "3001");
	TradeBookingService<Bond> tradeBookingService("localhost", "3002");
	InquiryService<Bond> inquiryService("localhost", "3003");
	StreamingService<Bond> streamingService("localhost", "3004");
	ExecutionService<Bond> executionService("localhost", "3005");

	AlgoStreamingService<Bond> algoStreamingService;
	AlgoExecutionService<Bond> algoExecutionService;
	PositionService<Bond> positionService;
	RiskService<Bond> riskService;
	GUIService<Bond> guiService;

	HistoricalDataService<Position<Bond>> historicalPositionService(POSITION);
	HistoricalDataService<PV01<Bond>> historicalRiskService(RISK);
	HistoricalDataService<ExecutionOrder<Bond>> historicalExecutionService(EXECUTION);
	HistoricalDataService<PriceStream<Bond>> historicalStreamingService(STREAMING);
	HistoricalDataService<Inquiry<Bond>> historicalInquiryService(INQUIRY);

	// 2.2 create listeners
    std::cout << "Linking service listeners..." << std::endl;
	pricingService.AddListener(algoStreamingService.GetAlgoStreamingListener());
	pricingService.AddListener(guiService.GetGUIServiceListener());
	algoStreamingService.AddListener(streamingService.GetStreamingServiceListener());
	marketDataService.AddListener(algoExecutionService.GetAlgoExecutionServiceListener());
	algoExecutionService.AddListener(executionService.GetExecutionServiceListener());
	executionService.AddListener(tradeBookingService.GetTradeBookingServiceListener());
	tradeBookingService.AddListener(positionService.GetPositionListener());
	positionService.AddListener(riskService.GetRiskServiceListener());

	positionService.AddListener(historicalPositionService.GetHistoricalDataServiceListener());
	executionService.AddListener(historicalExecutionService.GetHistoricalDataServiceListener());
	streamingService.AddListener(historicalStreamingService.GetHistoricalDataServiceListener());
	riskService.AddListener(historicalRiskService.GetHistoricalDataServiceListener());
	inquiryService.AddListener(historicalInquiryService.GetHistoricalDataServiceListener());
    std::cout << "Service listeners linked." << std::endl;

	// 3. start six system servers in different threads
	cout << fixed << setprecision(6);
	vector<thread> threads;

	// four input servers: pricing, market data, trade booking, inquiry
	threads.push_back(thread(Server<PricingService<Bond>>, ref(pricingService))); 
	threads.push_back(thread(Server<MarketDataService<Bond>>, ref(marketDataService))); 
	threads.push_back(thread(Server<TradeBookingService<Bond>>, ref(tradeBookingService))); 
	threads.push_back(thread(Server<InquiryService<Bond>>, ref(inquiryService))); 

	// two output servers: streaming, execution
	threads.push_back(thread(Server<StreamingService<Bond>>, ref(streamingService)));
	threads.push_back(thread(Server<ExecutionService<Bond>>, ref(executionService))); 

	for (auto& thread : threads) {
		join(thread);
	}

}
