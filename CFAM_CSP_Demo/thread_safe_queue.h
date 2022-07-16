#pragma once

#include <iostream>
#include <queue>
#include <mutex>

#include "Globals.h"
#include "CDRMsg.h"

using namespace std;

class thread_safe_queue : public queue<CDRMsg>
{
private:
	std::recursive_mutex mtx;
	std::condition_variable cv;
public:

	bool empty() {
		std::lock_guard<std::recursive_mutex> lock(mtx); // holds the lock until scope is left
		if (queue<CDRMsg>::c.empty() == true) {
			return true;
		}
		return false;
	}

	void push(const CDRMsg& _msg) {
		std::lock_guard<std::recursive_mutex> lock(mtx); // holds the lock until scope is left
		queue<CDRMsg>::c.push_back(_msg);
		cv.notify_one();
	}

	CDRMsg pop() {
		std::lock_guard<std::recursive_mutex> lock(mtx); // holds the lock until scope is left
		queue<CDRMsg>::value_type msg((unsigned int)0);
		bool val = this->empty();
		if (!val)
		{
			msg = queue<CDRMsg>::c.front();
			CDR_Record rec = (msg.rec);
			queue<CDRMsg>::c.pop_front();
			(msg.rec) = rec;
			return msg;
		}
		return NULL;
	}
};

