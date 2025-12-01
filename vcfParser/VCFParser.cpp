#include "VCFParser.h"
#include <fstream>
#include <string>
#include <iostream>
#include "utils.h"
#include "HeaderParsing.h"
#include "RecordsParser.h"


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
			if (line.substr(0, 2) != "##") {
				// Reached end of header
				break;
			}
			parseHeaderLine(line, header);
		}

		return header;

	}

	vector<VCFRecord> VCFParser::parseAll() {
		vector<VCFRecord> records;
		string line;

		while (inputStream_ && std::getline(*inputStream_, line)) {
			if (line.empty() || line[0] == '#') {
				continue; // Skip header lines and empty lines
			}
			VCFRecord record;
			parseRecord(line, record);
			records.push_back(record);
		}

		return records;
	}


	VCFParser::~VCFParser() {
		delete inputStream_;
	}
}