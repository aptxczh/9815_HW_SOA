///////////////////////////////////////////////////////////////////////////////////////////
///                                 Avinash Oza & Zhihao Chen
///////////////////////////////////////////////////////////////////////////////////////////
/**
 * test program for our ProductServices
 */

#include <iostream>
#include <vector>
#include "products.hpp"
#include "productservice.hpp"

using namespace std;
template<typename T>
void print(const vector<T>& v)
{//help function to print out result of problem 3
	for (auto i : v)
		cout << i << endl;
	cout << endl;
}

int main()
{ ////////////////////////
  /// Test Problem 2
  ////////////////////////

  // Create the 3 months EuroDollarfuture issued by China;
  date maturityDate(2017, Mar, 16);
  string ed1 = "912828ONE";
  EDFuture f1(ed1, "China","EDH7", maturityDate);
  // Create the 6 months EuroDollarfuture
  date maturityDate2(2017, Jun, 16);
  string ed2 = "912828TW0";
  Future f2(ed2, EuroDollarFuture, Cash, "EDM7", maturityDate2);


  // Create the 10Y treasury note
  date maturityDateBond(2026, Nov, 16);
  string cusip = "912828M56";
  Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDateBond);

  // Create the 10Y treasury note future;
  date maturityDate3(2017, Sep, 16);
  string bd = "912829ONE";
  BDFuture f3(bd, treasuryBond, "TYU7", maturityDate3);

  // Create a FutureProductService
  FutureProductService *futureProductService = new FutureProductService();

  // Add the 10Y note to the BondProductService and retrieve it from the service
  futureProductService->Add(f1);
  futureProductService->Add(f2);
  futureProductService->Add(f3);
  Future& future1 = futureProductService->GetData(ed1);
  Future& future2 = futureProductService->GetData(ed2);
  Future& future3 = futureProductService->GetData(bd);
  cout << "Future: " << future1.GetProductId() << " ==> "; future1.print();
  cout << "Future: " << future2.GetProductId() << " ==> "; future2.print();
  cout << "Future: " << future3.GetProductId() << " ==> "; future3.print();

  ////////////////////////
  /// Test Problem 3
  ////////////////////////
  // Create the Spot 10Y Outright Swap
  cout << endl << "**************************Test Problem 3******************************************\n";
  date effectiveDate(2016, Nov, 16);
  date terminationDate(2026, Nov, 16);
  string outright10Y = "Spot-Outright-10Y";
  IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

  // Create the IMM 2Y Outright Swap
  date effectiveDate2(2016, Dec, 20);
  date terminationDate2(2018, Dec, 20);
  string imm2Y = "IMM-Outright-2Y";
  IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);
  // Create the IMM 3M Outright Swap
  date effectiveDate3(2016, Dec, 20);
  date terminationDate3(2017, Dec, 20);
  string imm1Y = "IMM-Outright-1Y";
  IRSwap imm1YSwap(imm1Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate3, terminationDate3, USD, 1, IMM, OUTRIGHT);
  // Create a IRSwapProductService
  IRSwapProductService *swapProductService = new IRSwapProductService();

  // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(outright10YSwap);

  // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm2YSwap);
  // Add the IMM 3m Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm1YSwap);
  cout << "Term Test: Greater Than 2 years\n";
  print(swapProductService->GetSwapsGreaterThan(2));
  cout << "Term Test: Less Than 2 years\n";
  print(swapProductService->GetSwapsLessThan(2));
  cout << "Get Swap Test: \n";
  print(swapProductService->GetSwaps(IMM));
}
