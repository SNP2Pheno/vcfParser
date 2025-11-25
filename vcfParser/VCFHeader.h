#pragma once

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;


namespace vcf {

	/*
		Number entry
			Integer; describes the number of values that can be included with the INFO field
			1: one value
			2: two values
			A: one value per alternate allele
			R: one value per allele, including reference
			G: one value per genotype
			.: unknown number of values

		Flag entry
			Boolean; indicates that field does not contain a value; Number must be 0 in this case

		Description entry
			String; describes the INFO field, must be in Double quotes
	*/
	struct InfoField {
		string ID;
		string Number;						
		string Type;
		string Description;
		string Source;
		string Version;
	};

	struct FilterField {
		string ID;
		string Description;
	};

	/*
		Number entry
			Integer; describes the number of values that can be included with the FORMAT field
			1: one value
			2: two values
			P: one value for each allele value
	*/
	struct FormatField {
		string ID;
		string Number;
		string Type;
		string Description;
	};

	struct AltField {
		string ID;
		string Description;
	};

	struct ContigField {
		string ID;
		int Length;
		string Url;
	};

	struct MetaField {
		string ID;
		string Type;
		std::vector<string> Values;
	};

	struct SampleField {
		string ID;
		string Assay;
		string Ethnicity;
		string Disease;
		string Description;
		string DIO;
	};

	struct PedigreeField {
		string ID;
		vector<std::map<string, string>> Members;
	};


	// TODO: include frequenty used INFO, FORMAT fields as maps for easy access => see table in https://samtools.github.io/hts-specs/VCFv4.4.pdf

	struct VCFHeader {
		string fileFormat;
		vector<InfoField> infoFields;
		vector<FilterField> filterFields;
		vector<FormatField> formatFields;
		vector<AltField> altFields;
		string assembly;
		vector<ContigField> contigFields;
		vector<MetaField> metaFields;
		vector<SampleField> sampleFields;
		vector<PedigreeField> pedigreeFields;
		string pedigreeDB;
		string source;
		string reference;
		vector<string> otherLines;
		vector<string> headerLines;
	};
}