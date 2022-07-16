#include "Parser.h"

void Parser::ConvertStrToCDRRecordClass(CDR_Record* cdrr, string str)
{
	string* tmp = new string[9];
	size_t found = 0;

	for (int i = 0; i < (signed int)str.length(); i++)
	{
		while (str[i] == '|') {
			i++;
			found++;
		}
		tmp[found].push_back(str[i]);
	}

	cdrr->MSISDN = atoi(tmp[0].c_str());
	strcpy_s(cdrr->OperatorBrandName, 64, tmp[1].c_str());
	cdrr->OperatorMMCorMNC = atoi(tmp[2].c_str());
	strcpy_s(cdrr->tCall, 9, tmp[3].c_str());
	cdrr->Duration = atoi(tmp[4].c_str());
	if (tmp[5].compare("GPRS")) {
		cdrr->MBDownload = atoi(tmp[5].c_str());
		cdrr->MBUpload = atoi(tmp[6].c_str());
	}
	else {
		cdrr->MBDownload = 0;
		cdrr->MBUpload = 0;
	}
	cdrr->ThirdPartyMSISDN = atoi(tmp[7].c_str());
	cdrr->ThirdPartyOperatorMMCorMNC = atoi(tmp[8].c_str());

	delete[] tmp;
}
