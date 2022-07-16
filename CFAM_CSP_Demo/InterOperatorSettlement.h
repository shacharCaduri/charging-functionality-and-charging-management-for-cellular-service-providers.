#pragma once
#include "CDR_Record.h"
#include "enum_tCall.h"

class InterOperatorSettlement
{
public:
	InterOperatorSettlement() :
		Incoming_voice_call_durations(NULL),
		Outgoing_voice_call_durations(NULL),
		Incoming_SMS_messages(NULL),
		Outgoing_SMS_messages(NULL),
		MB_Downloaded(NULL),
		MB_Uploaded(NULL),
		_operator_MMC_or_MNC(NULL)
	{
	}

	int Incoming_voice_call_durations;
	int Outgoing_voice_call_durations;
	int Incoming_SMS_messages;
	int Outgoing_SMS_messages;
	size_t MB_Downloaded;
	size_t MB_Uploaded;

	int _operator_MMC_or_MNC;

	void initOperatorMMCorMNC(int operatorMMCorMMC);
	void CalcAggregatedData(const CDR_Record& cdr_rec);

	friend ostream& operator<<(ostream& os, const InterOperatorSettlement& ios);

	InterOperatorSettlement& operator=(const InterOperatorSettlement& ios);
	InterOperatorSettlement& operator=(const int& nullObj);
};

