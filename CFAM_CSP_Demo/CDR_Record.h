#pragma once
#include <string>
#include <iostream>

using namespace std;

class CDR_Record
{

public:
	CDR_Record() {
		MSISDN = 0;
		strcpy_s(OperatorBrandName, 64, "\0");
		OperatorMMCorMNC = 0;
		strcpy_s(tCall,9,"\0");
		Duration = 0;
		MBDownload = 0;
		MBUpload = 0;
		ThirdPartyMSISDN = 0;
		ThirdPartyOperatorMMCorMNC = 0;
	}

	int MSISDN;
	char OperatorBrandName[64];
	int OperatorMMCorMNC;
	char tCall[9];
	int Duration;
	int MBDownload;
	int MBUpload;
	int ThirdPartyMSISDN;
	int ThirdPartyOperatorMMCorMNC;

	bool operator!=(const CDR_Record& val);
	friend ostream& operator<<(ostream& os, const CDR_Record& cdrr); 
	CDR_Record& operator=(CDR_Record& other);
};

