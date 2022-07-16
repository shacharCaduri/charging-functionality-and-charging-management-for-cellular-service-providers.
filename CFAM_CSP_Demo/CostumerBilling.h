#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "CDR_Record.h"
#include "enum_tCall.h"

class CostumerBilling
{

public:
	CostumerBilling() :
		OutgoingVCDOutside(NULL),
		OutgoingVCDWithin(NULL),
		IncomingVCDOutside(NULL),
		IncomingVCDWithin(NULL),
		SMS_Recieve_OMB(NULL),
		SMS_Recieve_WMB(NULL),
		SMS_Sent_OMB(NULL),
		SMS_Sent_WMB(NULL),
		MB_Download(NULL),
		MB_Upload(NULL),
		_costumer_MSISDN(NULL)
	{
	}

	int _costumer_MSISDN;

	int OutgoingVCDWithin;
	int IncomingVCDWithin;
	int OutgoingVCDOutside;
	int IncomingVCDOutside;
	int SMS_Sent_WMB;
	int SMS_Recieve_WMB;
	int SMS_Sent_OMB;
	int SMS_Recieve_OMB;
	size_t MB_Download;
	size_t MB_Upload;

	void CalcAggregatedData(const CDR_Record& cdr_rec);

	void initCostumerMSISDN(int msisdn);

	friend ostream& operator<<(ostream& os, const CostumerBilling& cb);
	CostumerBilling& operator=(const CostumerBilling& cb);
	CostumerBilling& operator=(const int& nullObj);
};

