// CFAM_CSP_Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <string>
#include <assert.h>

#include "Parser.h"
#include "CDR_Reader.h"
#include "readThread.h"
#include "WriteThread.h"
#include "thread_safe_queue.h"
#include "CDRMsg.h"
#include "CDR_Record.h"
#include "CDR_Reader.h"
#include "enum_tCall.h"
#include "CostumerBilling.h"
#include "InterOperatorSettlement.h"
#include "thread pools classes/ThreadPool.h"
#include "StartPool.h"

#include "Globals.h"

using namespace std;
void freeAllGlobalData();

int main()
{
	readThreadObj rth; //defined in ReadThread
	
	std::thread poolThread(StartPool, 5);
	std::thread readerThread(rth, F_NAME); // F_NAME defined in Globals.h

	readerThread.join();
	poolThread.join();

	freeAllGlobalData();
	return 0;
}

void freeAllGlobalData() {
	if (recs != nullptr) {
		for (int i = 0; i < numberOfRecords; i++)
		{
			CostumerDatabase.removeAllKey(recs[i]->MSISDN);
			OperatorDatabase.removeAllKey(recs[i]->OperatorMMCorMNC);
			delete recs[i];
		}
		delete[] recs;

	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
