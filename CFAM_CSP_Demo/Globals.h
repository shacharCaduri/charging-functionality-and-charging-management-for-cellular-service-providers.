#pragma once

#include "My Header Files/hashmap/HashMap.h"
#include "My Header Files/hashmap/MyKeyHashes.h"
#include "thread_safe_queue.h"
#include "CostumerBilling.h"
#include "InterOperatorSettlement.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#ifndef F_NAME

#define F_NAME "My Files/CDR/file.cdr"

#endif // !F_NAME

#define READ_THREAD_NUM -1

static unsigned int msg_id;
static thread_safe_queue mQueue;
static std::atomic_bool timeToLeave = false;
static CDR_Record** recs = nullptr;
static int numberOfRecords;
recursive_mutex coutMutex;

// - 10,000,000 because each MSISDN is a 7 digit number [0-9] so the maximum number of diffrent MSISDN numbers is 10 to the power of 7 which is 10 million
// 
// - MyDoNothingKey just reutrn the key itself means it does not handle collisions that because MSISDN / Operator MMC/MNC is unique and there is no more then 1 MSISDN / Operator MMC/MNC to save
//   in the database. in consclustion it means just update values on the hash tables does not have linked lists each key
// - MyMSISDNKey - key%(10,000,000) - (10,000,000 = HashTable Size)
static HashMap<int, CostumerBilling, 10000000, MyMSISDNKey> CostumerDatabase;
static HashMap<int, InterOperatorSettlement, 10000000, MyMSISDNKey> OperatorDatabase;

void AtomicPrintThreadOperationAndId(const int& id) {
	lock_guard<recursive_mutex> coutLock(coutMutex);
	if (id == READ_THREAD_NUM)
		cout << "Read Thread" << endl;
	else
		cout << "WriteThread: " << id << endl;
}

template<typename V>
void AtomicPrintThreadText(const string& str, const V& arg) {
	lock_guard<recursive_mutex> coutLock(coutMutex);
	cout << str << arg << endl;
}