#pragma once

#include <string>

namespace vcf {
	void parseRecord(const std::string& plainLine, VCFRecord&);
}