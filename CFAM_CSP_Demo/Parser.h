#pragma once
#include "CDR_Record.h"
#include <stdlib.h>
#include <string>

using namespace std;
using std::string;

static class Parser
{
public:
	void ConvertStrToCDRRecordClass(CDR_Record* cdrr, string str);
}Parser;

