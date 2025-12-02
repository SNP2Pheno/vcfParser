#include "VCFParser.h"
#include <fstream>
#include "HeaderParsing.h"
#include "RecordsParsing.h"
#include "utils.h"


using std::string;

namespace vcf {


	VCFParser::VCFParser(const string& filePath)
		: filePath_(filePath) {

		std::ifstream* in = new std::ifstream(filePath_);
		if (!in->is_open()) {
			delete in;
			throw std::runtime_error("Could not open file: " + filePath_);
		}

		inputStream_ = in;

	}

	VCFParser::VCFParser(std::istream& inputStream)
		: inputStream_(&inputStream) {

		if (inputStream_ == nullptr) {
			delete inputStream_;
			throw std::runtime_error("Input stream is null.");
		}
	}

	VCFHeader VCFParser::parseHeader() {
		VCFHeader header;
		string line;


		while (inputStream_ && std::getline(*inputStream_, line)) {
			line = cleanLine(line);
			if (!line.starts_with("##") && !line.starts_with("#CHROM")) {
				// Reached end of header
				leftoverLine_ = line;
				break;
			}
			parseHeaderLine(line, header);
		}
		
		header_ = header;
		return header;

	}

	vector<VCFRecord> VCFParser::parseAll() {
		if (records_.size() > 0) {
			return records_;
		}
		if (header_.headerLines.size() == 0) {
			header_ = parseHeader();
		}
		vector<VCFRecord> records;
		string line;

		if (!leftoverLine_.empty()) {
			VCFRecord record;
			parseRecord(leftoverLine_, header_.recordHeader, record);
			records.push_back(record);
		}

		while (inputStream_ && std::getline(*inputStream_, line)) {
			line = cleanLine(line);
			if (line.empty() || line[0] == '#')
				continue;

			VCFRecord record;
			parseRecord(line, header_.recordHeader, record);
			records.push_back(record);
		}


		return records;
	}


	VCFParser::~VCFParser() {
		delete inputStream_;
	}
}