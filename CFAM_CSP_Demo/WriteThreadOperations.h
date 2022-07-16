#pragma once
#include "Globals.h"
#define wThreadMem 1;

#ifdef wThreadMem
recursive_mutex databaseMutex;
recursive_mutex OdatabaseMutex;
recursive_mutex CdatabaseMutex;
mutex printSemaphore;
bool printedAlready = false;
vector<CostumerBilling> c_bill_vector;
vector<CostumerBilling>::iterator c_it;
vector<InterOperatorSettlement> o_bill_vector;
vector<InterOperatorSettlement>::iterator o_it;
bool found = false;
#endif

void printAllHashData() {
	CostumerDatabase.printHashTable();
	OperatorDatabase.printHashTable();
}

void safe_printAllHashData() {
	CostumerDatabase.safe_printHashTable();
	OperatorDatabase.safe_printHashTable();
}

void none_atomic_safe_printOp_PrintHashData() {
	lock_guard<mutex> printDatabaseSemaphoreLock(printSemaphore);
	if (!printedAlready) {
		cout << endl;
		safe_printAllHashData();
		printedAlready = true;
	}
}

void atomic_safe_printHashTable() {
	lock_guard<recursive_mutex> databaseLock(databaseMutex);
	if (!printedAlready) {
		cout << endl;
		printAllHashData();
		printedAlready = true;
	}
}

void writeCostBill(CostumerBilling& c_bill, CDRMsg& msg) {
	int index = 0;
	int idx = 0;
	found = false;
	for (c_it = c_bill_vector.begin(); c_it != c_bill_vector.end(); c_it++, idx++)
	{
		if (msg.rec.MSISDN == (*c_it)._costumer_MSISDN)
		{
			(*c_it).CalcAggregatedData(msg.rec);
			index = idx;
			found = true;
		}
	}
	if (!found)
	{
		c_bill.initCostumerMSISDN(msg.rec.MSISDN);
		c_bill.CalcAggregatedData(msg.rec);
		c_bill_vector.push_back(c_bill);
		CostumerDatabase.put(c_bill._costumer_MSISDN, c_bill);
		found = false;
	}
	else
	{
		CostumerDatabase.put(c_bill_vector[index]._costumer_MSISDN, c_bill_vector[index]);
	}
}

void writeOperBill(InterOperatorSettlement& o_bill, CDRMsg& msg) {
	int index = 0;
	int idx = 0;
	found = false;
	for (o_it = o_bill_vector.begin(); o_it != o_bill_vector.end(); o_it++, idx++)
	{
		if (msg.rec.OperatorMMCorMNC == (*o_it)._operator_MMC_or_MNC)
		{
			(*o_it).CalcAggregatedData(msg.rec);
			index = idx;
			found = true;
		}
	}
	if (!found)
	{
		o_bill.initOperatorMMCorMNC(msg.rec.OperatorMMCorMNC);
		o_bill.CalcAggregatedData(msg.rec);
		o_bill_vector.push_back(o_bill);
		OperatorDatabase.put(o_bill._operator_MMC_or_MNC, o_bill);
		found = false;
	}
	else
	{
		OperatorDatabase.put(o_bill_vector[index]._operator_MMC_or_MNC, o_bill_vector[index]);
	}
}
