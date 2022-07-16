#include "InterOperatorSettlement.h"

void InterOperatorSettlement::initOperatorMMCorMNC(int operatorMMCorMMC)
{
	if (this->_operator_MMC_or_MNC != operatorMMCorMMC)
	{
		try {
			*this = NULL;
		}
		catch (std::invalid_argument& e) {
			cerr << e.what() << endl;
			exit(-1);
		}
	}
	this->_operator_MMC_or_MNC = operatorMMCorMMC;
}

void InterOperatorSettlement::CalcAggregatedData(const CDR_Record& cdr_rec)
{
	tCall tcall = { tCall::NOTHING };
	if (strcmp(cdr_rec.tCall, "MOC") == 0)
		tcall = tCall::MOC;
	if (strcmp(cdr_rec.tCall, "MTC") == 0)
		tcall = tCall::MTC;
	if (strcmp(cdr_rec.tCall, "SMS-MO") == 0)
		tcall = tCall::SMS_MO;
	if (strcmp(cdr_rec.tCall, "SMS-MT") == 0)
		tcall = tCall::SMS_MT;
	if (strcmp(cdr_rec.tCall, "GPRS") == 0)
		tcall = tCall::GPRS;

	switch (tcall) {
	case tCall::MOC:
		this->Outgoing_voice_call_durations += cdr_rec.Duration;
		break;
	case tCall::MTC:
		this->Incoming_voice_call_durations += cdr_rec.Duration;
		break;
	case tCall::SMS_MO:
		this->Outgoing_SMS_messages++;
		break;
	case tCall::SMS_MT:
		this->Incoming_SMS_messages++;
		break;
	case tCall::GPRS:
		this->MB_Downloaded += cdr_rec.MBDownload;
		this->MB_Uploaded += cdr_rec.MBUpload;
		break;
	default: break;
	}
}

InterOperatorSettlement& InterOperatorSettlement::operator=(const InterOperatorSettlement& ios)
{
	if (this == &ios)
		return *this;
	this->Incoming_SMS_messages = ios.Incoming_SMS_messages;
	this->Incoming_voice_call_durations = ios.Incoming_voice_call_durations;
	this->_operator_MMC_or_MNC = ios._operator_MMC_or_MNC;
	this->MB_Downloaded = ios.MB_Downloaded;
	this->MB_Uploaded = ios.MB_Uploaded;
	this->Outgoing_SMS_messages = ios.Outgoing_SMS_messages;
	this->Outgoing_voice_call_durations = ios.Outgoing_voice_call_durations;
	return *this;
}

InterOperatorSettlement& InterOperatorSettlement::operator=(const int& nullObj)
{
	if (nullObj == 0)
	{
		this->Incoming_SMS_messages = NULL;
		this->Incoming_voice_call_durations = NULL;
		this->_operator_MMC_or_MNC = NULL;
		this->MB_Downloaded = NULL;
		this->MB_Uploaded = NULL;
		this->Outgoing_SMS_messages = NULL;
		this->Outgoing_voice_call_durations = NULL;
	}
	else {
		throw std::invalid_argument("RUNTIME ERROR! cannot initialize with integer other then NULL \n");
	}
	return *this;
}


ostream& operator<<(ostream& os, const InterOperatorSettlement& ios)
{
	os << "Incoming_SMS_messages: " << ios.Incoming_SMS_messages << endl;
	os << "Incoming_voice_call_durations: " << ios.Incoming_voice_call_durations << endl;
	os << "MB_Downloaded: " << ios.MB_Downloaded << endl;
	os << "MB_Uploaded: " << ios.MB_Uploaded << endl;
	os << "Outgoing_SMS_messages: " << ios.Outgoing_SMS_messages << endl;
	os << "Outgoing_voice_call_durations: " << ios.Outgoing_voice_call_durations << endl;
	return os;
}
