#include "VCFParser.h"

using vcf::VCFParser;

int main() {
	// Example usage of VCFParser
	VCFParser parser("vcfTestFileSimple.vcf");
	vcf::VCFHeader h = parser.parseHeader();

	return 0;
}