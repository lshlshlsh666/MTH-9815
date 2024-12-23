# MTH 9815 Final -- Trading System

To run the trading system, run the following command in the terminal:

```bash 
bash ./run.sh
```

US Treasury Info comes from the following website: https://www.savingsbond.gov/auctions/announcements-data-results/.

'prices.txt', 'trades.txt', 'marketdata.txt', 'inquries.txt' are too large to be uploaded to github. However, by running the `run.sh` script, the program will automatically generate these files -- it will take around 1-2 minutes to run.

The output of the program is stored in the `output` folder.

Note: The code structure (use socket to communicate between threads) is inspired by https://github.com/bradleyboyuyang/Trading-System. But most of the detailed code (especially `utils.hpp`) is written by myself.