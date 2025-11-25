#include "VCFParser.h"
#include <fstream>

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

	VCFParser::~VCFParser() {
		delete inputStream_;
	}
}