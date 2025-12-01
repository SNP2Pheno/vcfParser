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
		CHRM,
		NONSTANDARD
	};

	struct SampleCall {
		std::unordered_map<string, std::vector<string>> fields;
	};

	struct VCFRecord {
		EChrom chrom;											// MANDATORY
		int position;											// MANDATORY
		string id;												// MANDATORY
		string ref;												// MANDATORY
		std::vector<string> alts;								// MANDATORY
		string qual;											// MANDATORY
		string filter;											// MANDATORY
		std::unordered_map<string, std::vector<string>> info;	// MANDATORY
		std::unordered_set<string> infoFlags;					// MANDATORY
		std::vector<string> formatKeys;							// ONLY IF GENOTYPE DATA IS PRESENT
		std::vector<SampleCall> samples;						// ONLY IF GENOTYPE DATA IS PRESENT => No duplicate sample IDs
	};
}