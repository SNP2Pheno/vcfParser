#include "RecordsParsing.h"
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include "utils.h"
#include <stdexcept>

namespace vcf
{

	using RecordHandler = std::function<void(const std::string&, VCFRecord&)>;
	static const std::unordered_map<std::string, RecordHandler> recordHandlers = {
		{"CHROM",[](const std::string& value, VCFRecord& r) {
			r.chrom = mapChromosome(value);
		}},
		{"POS", [](const std::string& value, VCFRecord& r) {
			r.position = std::stoul(value);
		}},
		{"ID", [](const std::string& value, VCFRecord& r) {
			r.id = value;
		}},
		{"REF", [](const std::string& value, VCFRecord& r) {
			r.ref = value;
		}},
		{"ALT", [](const std::string& value, VCFRecord& r) {
			r.alts = splitString(value, ',');
		}},
		{"QUAL", [](const std::string& value, VCFRecord& r) {
			if (value == ".") {
				r.qual = -1.0;
			}
			else {
				r.qual = std::stod(value);
			}
		}},
		{"FILTER", [](const std::string& value, VCFRecord& r) {
			r.filter = value;
		}},
		{"INFO", [](const std::string& value, VCFRecord& r) {
			std::vector<std::string> infoFields = splitString(value, ';');
			for (const auto& field : infoFields) {
				if (field.find('=') != std::string::npos) {
					std::string key = field.substr(0, field.find('='));
					std::string val = field.substr(field.find('=') + 1);
					r.info[key] = splitString(val, ',');

					r.infoFlags.insert(key);
				}
				else {
					r.info[field] = { "true" };
					r.infoFlags.insert(field);
				}
			}
		}},
		{"FORMAT", [](const std::string& value, VCFRecord& r) {
			r.formatKeys = splitString(value, ':');
		}}
	};


	void parseRecord(const std::string& plainLine, std::vector<std::string> recordHeader, VCFRecord& r) {
	
		std::vector<std::string> fields = splitString(plainLine, '\t');
		if (fields.size() < recordHeader.size()) {
			throw std::runtime_error("Malformed VCF record: insufficient fields.");
		}
		std::vector<std::string> keys = recordHeader;

		for (size_t i = 0; i < fields.size(); i++)
		{
			auto it = recordHandlers.find(keys[i]);
			if (it != recordHandlers.end()) {
				it->second(fields[i], r);
			}
			else {
				// Handle sample calls
				if (i >= 9) { // Sample data starts from the 10th column
					if (r.formatKeys.empty()) {
						throw std::runtime_error("FORMAT field is missing for sample data.");
					}
					SampleCall sampleCall;
					std::vector<std::string> sampleValues = splitString(fields[i], ':');
					for (size_t j = 0; j < r.formatKeys.size(); j++) {
						if (j < sampleValues.size()) {
							sampleCall.fields[r.formatKeys[j]].push_back(sampleValues[j]);
						}
						else {
							sampleCall.fields[r.formatKeys[j]].push_back(".");
						}
					}
					r.samples.push_back(sampleCall);
				}
			}
		}
	}
}
