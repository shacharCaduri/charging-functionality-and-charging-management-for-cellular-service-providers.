#include "CostumerBilling.h"

void CostumerBilling::CalcAggregatedData(const CDR_Record& cdr_rec)
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
		if (cdr_rec.OperatorMMCorMNC == cdr_rec.ThirdPartyOperatorMMCorMNC) {
			this->OutgoingVCDWithin += cdr_rec.Duration;
		}
		else {
			this->OutgoingVCDOutside += cdr_rec.Duration;
		}
		break;
	case tCall::MTC:
		if (cdr_rec.OperatorMMCorMNC == cdr_rec.ThirdPartyOperatorMMCorMNC) {
			this->IncomingVCDWithin += cdr_rec.Duration;
		}
		else {
			this->IncomingVCDOutside += cdr_rec.Duration;
		}
		break;
	case tCall::SMS_MO:
		if (cdr_rec.OperatorMMCorMNC == cdr_rec.ThirdPartyOperatorMMCorMNC) {
			this->SMS_Sent_WMB++;
		}
		else {
			this->SMS_Sent_OMB++;
		}
		break;
	case tCall::SMS_MT:
		if (cdr_rec.OperatorMMCorMNC == cdr_rec.ThirdPartyOperatorMMCorMNC) {
			this->SMS_Recieve_WMB++;
		}
		else {
			this->SMS_Recieve_OMB++;
		}
		break;
	case tCall::GPRS:
		this->MB_Download += cdr_rec.MBDownload;
		this->MB_Upload += cdr_rec.MBUpload;
		break;
	default: break;
	}
}

void CostumerBilling::initCostumerMSISDN(int msisdn)
{
	if (this->_costumer_MSISDN != msisdn)
	{
		try {
			*this = NULL;
		}
		catch (std::invalid_argument& e) {
			cerr << e.what() << endl;
			exit(-1);
		}
	}
	this->_costumer_MSISDN = msisdn;
}

CostumerBilling& CostumerBilling::operator=(const CostumerBilling& cb)
{
	if (this == &cb)
		return *this;

	this->IncomingVCDOutside = cb.IncomingVCDOutside;
	this->IncomingVCDWithin = cb.IncomingVCDWithin;
	this->MB_Download = cb.MB_Download;
	this->MB_Upload = cb.MB_Upload;
	this->OutgoingVCDOutside = cb.OutgoingVCDOutside;
	this->OutgoingVCDWithin = cb.OutgoingVCDWithin;
	this->SMS_Recieve_OMB = cb.SMS_Recieve_OMB;
	this->SMS_Recieve_WMB = cb.SMS_Recieve_WMB;
	this->SMS_Sent_OMB = cb.SMS_Sent_OMB;
	this->SMS_Sent_WMB = cb.SMS_Sent_WMB;
	this->_costumer_MSISDN = cb._costumer_MSISDN;
	return *this;
}

CostumerBilling& CostumerBilling::operator=(const int& nullObj)
{
	if (nullObj == 0) {
		this->IncomingVCDOutside = 0;
		this->IncomingVCDWithin = 0;
		this->MB_Download = 0;
		this->MB_Upload = 0;
		this->OutgoingVCDOutside = 0;
		this->OutgoingVCDWithin = 0;
		this->SMS_Recieve_OMB = 0;
		this->SMS_Recieve_WMB = 0;
		this->SMS_Sent_OMB = 0;
		this->SMS_Sent_WMB = 0;
		this->_costumer_MSISDN = 0;
	}
	else {
		throw std::invalid_argument("RUNTIME ERROR! cannot initialize with const integer other then NULL \n");
	}
	return *this;
}

ostream& operator<<(ostream& os, const CostumerBilling& cb)
{
	os << "IncomingVCDOutside: " << cb.IncomingVCDOutside << endl;
	os << "IncomingVCDWithin: " << cb.IncomingVCDWithin << endl;
	os << "MB_Download: " << cb.MB_Download << endl;
	os << "MB_Upload: " << cb.MB_Upload << endl;
	os << "OutgoingVCDOutside: " << cb.OutgoingVCDOutside << endl;
	os << "OutgoingVCDWithin: " << cb.OutgoingVCDWithin << endl;
	os << "SMS_Recieve_OMB: " << cb.SMS_Recieve_OMB << endl;
	os << "SMS_Recieve_WMB: "<<cb.SMS_Recieve_WMB << endl;
	os << "SMS_Sent_OMB: " <<cb.SMS_Sent_OMB << endl;
	os << "SMS_Sent_WMB: " << cb.SMS_Sent_WMB << endl;
	os << "_costumer_MSISDN: " << cb._costumer_MSISDN << endl;
	return os;
}

