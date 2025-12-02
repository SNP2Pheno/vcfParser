#pragma once

#include "VCFRecord.h"

namespace vcf {
	void parseRecord(const std::string& plainLine,std::vector<std::string> recordHeader, VCFRecord& r);
}