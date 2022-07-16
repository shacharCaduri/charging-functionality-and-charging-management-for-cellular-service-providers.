#pragma once

#include "CDR_Record.h"


ostream& operator<<(ostream& os, const CDR_Record& cdrr) {
	os << "MSISDN: " << cdrr.MSISDN << endl;
	os << "OperatorBrandName: " << cdrr.OperatorBrandName << endl;
	os << "OperatorMMCorMNC: " << cdrr.OperatorMMCorMNC << endl;
	os << "tCall: " << cdrr.tCall << endl;
	os << "Duration: " << cdrr.Duration << endl;
	os << "MBDownload: " << cdrr.MBDownload << endl;
	os << "MBUpload: " << cdrr.MBUpload << endl;
	os << "ThirdPartyMSISDN: " << cdrr.ThirdPartyMSISDN << endl;
	os << "ThirdPartyOperatorMMCorMNC: " << cdrr.ThirdPartyOperatorMMCorMNC << endl;
	return os;
}

bool CDR_Record::operator!=(const CDR_Record& val)
{
	if (
		this->MSISDN != val.MSISDN ||
		strcmp(this->OperatorBrandName, val.OperatorBrandName) != 0 ||
		this->OperatorMMCorMNC != val.OperatorMMCorMNC ||
		strcmp(this->tCall, val.tCall) != 0 ||
		this->Duration != val.Duration ||
		this->MBDownload != val.MBDownload ||
		this->MBUpload != val.MBUpload ||
		this->ThirdPartyMSISDN != val.ThirdPartyMSISDN ||
		this->ThirdPartyOperatorMMCorMNC != val.ThirdPartyOperatorMMCorMNC
		)
		return true;
	return false;
}

CDR_Record& CDR_Record::operator=(CDR_Record& other)
{
	if (this == &other)
		return *this;
	this->MSISDN = other.MSISDN;
	strcpy_s(this->OperatorBrandName, 64, other.OperatorBrandName);
	this->OperatorMMCorMNC = other.OperatorMMCorMNC;
	strcpy_s(this->tCall, 9, other.tCall);
	this->Duration = other.Duration;
	this->MBDownload = other.MBDownload;
	this->MBUpload = other.MBUpload;
	this->ThirdPartyMSISDN = other.ThirdPartyMSISDN;
	this->ThirdPartyOperatorMMCorMNC = other.ThirdPartyOperatorMMCorMNC;

	return *this;
}
