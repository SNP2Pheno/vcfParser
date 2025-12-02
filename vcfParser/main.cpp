#include "VCFParser.h"

using vcf::VCFParser;

int main() {
	// Example usage of VCFParser
	VCFParser parser("vcfTestFileSimple.vcf");
	vcf::VCFHeader h = parser.parseHeader();
	std::vector<vcf::VCFRecord> records = parser.parseAll();
	return 0;
}