#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

#include "thread pools classes/ThreadPool.h"
#include "Globals.h"
#include "WriteThreadOperations.h"
#include "InterOperatorSettlement.h"
#include "CostumerBilling.h"
#include "CDRMsg.h"
#include "CDR_Record.h"

using namespace std;

void StartPool(int nThreads)
{
	//thread pool
	ThreadPool pool(nThreads);
	std::vector< std::future<void> > results;
	for (int i = 0; i < nThreads; i++)
	{
		results.emplace_back(
			pool.enqueue([i] {
				while (!(mQueue.empty()) || !timeToLeave) {
					CDRMsg msg = (mQueue.pop());
					if (msg != NULL) {
						AtomicPrintThreadOperationAndId(i);
						/*lock_guard<recursive_mutex> databaseLock(databaseMutex);*/
						CostumerBilling c_bill;
						InterOperatorSettlement o_bill;
						{
							lock_guard<recursive_mutex> databaseLock(CdatabaseMutex);
							writeCostBill(c_bill, msg);
						}
						{
							lock_guard<recursive_mutex> databaseLock(OdatabaseMutex);
							writeOperBill(o_bill, msg);
						}
					}
					//Sleep(1000);
				} // while loop close braces
				return none_atomic_safe_printOp_PrintHashData();
				}) // end enqueue func
		);// end emplace_back func
	} // for loop end

	for (auto&& result : results)
		result.get();
	std::cout << std::endl;
}