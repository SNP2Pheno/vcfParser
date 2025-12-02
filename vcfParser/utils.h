#pragma once

#include <string>
#include "VCFRecord.h"

namespace vcf {

	std::string toLower(std::string s);

	std::string clearOfDoubleQuotation(std::string s);

	std::vector<std::string> splitString(const std::string& str, char delimiter);

	EChrom mapChromosome(std::string chrom);

	std::string cleanLine(std::string l);
}