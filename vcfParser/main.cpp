#include "VCFParser.h"

using vcf::VCFParser;

int main() {
	// Example usage of VCFParser
	VCFParser parser("1000genomes.vcf");	
	vcf::VCFHeader h = parser.parseHeader();

	return 0;
}