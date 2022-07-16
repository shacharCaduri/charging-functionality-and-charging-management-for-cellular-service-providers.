#pragma once
#include "CDRMsg.h"

ostream& operator<<(ostream& os, const CDRMsg& msg)
{
	os << "msg id: " << msg.id << endl;
	os << "record:" << endl <<"-------"<< endl << msg.rec << endl;
	return os;
}

CDRMsg& CDRMsg::operator=(CDRMsg& other)
{
	if (this == &other)
		return *this;
	//if(this != nullptr)
	//	delete[] this->rec;
	this->rec = other.rec;
	this->id = other.id;

	return *this;
}

bool CDRMsg::operator!=(const CDRMsg& val)
{
	if (
		this->id != val.id ||
		this->rec != val.rec
		)
		return true;
	return false;
}
