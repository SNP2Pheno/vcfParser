#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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
		double qual;											// MANDATORY
		string filter;											// MANDATORY
		std::unordered_map<string, std::vector<string>> info;	// MANDATORY
		std::unordered_set<string> infoFlags;					// MANDATORY
		std::vector<string> formatKeys;							// ONLY IF GENOTYPE DATA IS PRESENT
		std::vector<SampleCall> samples;						// ONLY IF GENOTYPE DATA IS PRESENT => No duplicate sample IDs

		std::pair<string, string> decodeAlleles(size_t const& idx = 0) const {
			// default: unknown alleles
			const string rsId = id;
			auto result = std::make_pair(rsId, string("NN"));

			if (samples.empty()) {
				return result;
			}

			if (idx >= samples.size()) {
				return result;
			}

			const SampleCall &sample = samples[idx];

			auto it = sample.fields.find("GT");
			if (it == sample.fields.end() || it->second.empty()) {
				return result;
			}

			const string &gt = it->second[0];

			if (gt == "." || gt == "./." || gt == ".|.") {
				return result;
			}

			// Helper lambda to map allele index to base
			auto decodeAlleleChar = [this](const string &code) -> char {
				if (code == ".") return 'N';
				int idx = std::stoi(code);
				if (idx == 0) {
					return ref.empty() ? 'N' : ref[0];
				}
				std::size_t altIdx = static_cast<std::size_t>(idx - 1);
				if (altIdx < alts.size() && !alts[altIdx].empty()) {
					return alts[altIdx][0];
				}
				return 'N';
			};

			// Split GT on '/' or '|'
			char sep = (gt.find('|') != string::npos) ? '|' : '/';
			string a1Str, a2Str;
			auto pos = gt.find(sep);
			if (pos == string::npos) {
				a1Str = gt;
				a2Str = ".";
			} else {
				a1Str = gt.substr(0, pos);
				a2Str = gt.substr(pos + 1);
			}

			char a1 = decodeAlleleChar(a1Str);
			char a2 = decodeAlleleChar(a2Str);

			result.second = string{a1, a2};
			return result;
		}
	};
}