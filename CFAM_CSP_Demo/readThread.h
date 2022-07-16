#pragma once

#include <iostream>
#include <mutex>

#include "Globals.h"
#include "CDR_Record.h"
#include "CDR_Reader.h"
#include "CDRMsg.h"
#include "Parser.h"
#include "thread_safe_queue.h"

using namespace std;

class readThreadObj
{
	CDR_Reader* reader;
	CDRMsg* msg; /// last msg
public:
	readThreadObj() {
		this->msg = nullptr;
		this->reader = nullptr;
	}

	~readThreadObj() {
		if (msg != nullptr) {
			delete[] msg;
		}

		if (reader != nullptr) {
			delete reader;
		}
	}

	void operator()(string path) {
		reader = new CDR_Reader(path);
		int lines = reader->getNumOfLines();
		//lines = 10000;
		recs = new CDR_Record * [lines];
		cout << endl;
		for (int i = 0; i < lines; i++)
		{
			recs[i] = new CDR_Record;
			Parser.ConvertStrToCDRRecordClass(recs[i], reader->getLine());
			//cout << *rec[i] << endl;
			msg = new CDRMsg(msg_id++);
			msg->rec = *recs[i];
			AtomicPrintThreadOperationAndId(READ_THREAD_NUM);
			mQueue.push(*msg);
			//Sleep(1000);
		}

		numberOfRecords = lines;
		timeToLeave = true;
	}
};

