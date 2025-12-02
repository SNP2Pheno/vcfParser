#pragma once
#include <string>
#include <vector>
#include "VCFHeader.h"
#include "VCFRecord.h"

using std::string;
using std::vector;


namespace vcf {

	class VCFParser {
	public:
		explicit VCFParser(const string& filePath);
		explicit VCFParser(std::istream& inputStream);

		vector<VCFRecord> parseAll();
		VCFHeader parseHeader();

		~VCFParser();
	private:
		string filePath_;
		std::istream* inputStream_ = nullptr;
		string leftoverLine_;

		VCFHeader header_;
		vector<VCFRecord> records_;
	};
}