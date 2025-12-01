#pragma once

#include <string>
#include "VCFRecord.h"

namespace vcf {
	void parseRecord(const std::string& plainLine, VCFRecord&);
}