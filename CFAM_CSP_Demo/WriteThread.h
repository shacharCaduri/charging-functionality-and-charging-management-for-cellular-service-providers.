#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include "Globals.h"
#include "thread_safe_queue.h"
#include "InterOperatorSettlement.h"
#include "WriteThreadOperations.h"

using namespace std;

class WriteThread
{
private:
public:
	WriteThread() {
	}

	~WriteThread() {

	}
	void operator()(int num) {
		while (!(mQueue.empty()) || !timeToLeave) {
			AtomicPrintThreadOperationAndId(num);
			CDRMsg msg = (mQueue.pop());
			if (msg != NULL) {
				CostumerBilling c_bill;
				InterOperatorSettlement o_bill;
				writeCostBill(c_bill, msg);
				writeOperBill(o_bill, msg);
			}
		Sleep(1000);
		} // while loop close braces
		lock_guard<recursive_mutex> databaseLock(databaseMutex);
		if (!printedAlready) {
			cout << endl;
			printAllHashData();
			printedAlready = true;
		}
	}

};

