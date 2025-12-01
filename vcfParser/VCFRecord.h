#pragma once

#include <string>
#include <vector>

using std::string;


namespace vcf {

	enum class EChrom {
		CHR1,
		CHR2,
		CHR3,
		CHR4,
		CHR5,
		CHR6,
		CHR7,
		CHR8,
		CHR9,
		CHR10,
		CHR11,
		CHR12,
		CHR13,
		CHR14,
		CHR15,
		CHR16,
		CHR17,
		CHR18,
		CHR19,
		CHR20,
		CHR21,
		CHR22,
		CHRX,
		CHRY,
		CHRM
	};

	struct VCFRecord {
		EChrom chrom;
		int position;
		string id;
		string ref;
		std::vector<string> alts;
		string qual;
		string filter;
		std::vector<string> info;
		std::vector<string> format;
		std::vector<std::vector<string>> samples;
	};
}