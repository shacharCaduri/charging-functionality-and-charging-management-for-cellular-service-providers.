#pragma once

#include "CDR_Record.h"
#include <iostream>
using namespace std;

class CDRMsg
{
public:
	CDRMsg(unsigned int _id):id(_id) {
		rec;
	}

	friend ostream& operator<<(ostream& os, const CDRMsg& msg);
	CDRMsg& operator=(CDRMsg& other);
	bool operator!=(const CDRMsg& val);

	unsigned int id;
	CDR_Record rec;

};

