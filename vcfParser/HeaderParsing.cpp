#include "HeaderParsing.h"
#include <functional>
#include <unordered_map>
#include "utils.h"

namespace vcf {


	// lambda function to parse header lines
	using HeaderHandler = std::function<void(const std::string&, VCFHeader&)>;
	static const std::unordered_map<std::string, HeaderHandler> handlers = {
		{"fileformat", [](const std::string& value, VCFHeader& header) {
			header.fileFormat = value;
		}},
		{"filedate", [](const std::string& value, VCFHeader& header) {
			header.fileDate = value;
		}},
		{"info", [](const std::string& value, VCFHeader& header) {
			string iValue = value;
			InfoField info;
			while (iValue.find('=') != string::npos) {
				string token = iValue.substr(0, iValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, iValue.find("=")));
				string val = clearOfDoubleQuotation(token.substr(token.find("=") + 1));
				key = toLower(key);
				if (key == "id") info.ID = val;
				else if (key == "number") info.Number = val;
				else if (key == "type") info.Type = val;
				else if (key == "description") info.Description = val;
				else if (key == "source") info.Source = val;
				else if (key == "version") info.Version = val;
				else info.AdditionalAttributes[key] = val;

				if (iValue.find(',') != -1) {
					iValue = iValue.substr(iValue.find(',') + 1);
				}
				else {
					break;
				}
			}
			header.infoFields.push_back(info);

		}},
		{"filter", [](const std::string& value, VCFHeader& header) {
			string fValue = value;
			FilterField filter;
			while (fValue.find('=') != string::npos) {
				string token = fValue.substr(0, fValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, fValue.find("=")));
				string val = clearOfDoubleQuotation(token.substr(token.find("=") + 1));
				key = toLower(key);
				if (key == "id") filter.ID = val;
				else if (key == "description") filter.Description = val;
				else filter.AdditionalAttributes[key] = val;

				if (fValue.find(',') != -1) {
					fValue = fValue.substr(fValue.find(',') + 1);
				}
				else {
					break;
				}
			}
			header.filterFields.push_back(filter);

		}},
		{"format", [](const std::string& value, VCFHeader& header) {
			string fValue = value;
			FormatField format;
			while (fValue.find('=') != string::npos) {
				string token = fValue.substr(0, fValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, fValue.find("=")));
				string val = clearOfDoubleQuotation(token.substr(token.find("=") + 1));
				key = toLower(key);
				if (key == "id") format.ID = val;
				else if (key == "number") format.Number = val;
				else if (key == "type") format.Type = val;
				else if (key == "description") format.Description = val;
				else format.AdditionalAttributes[key] = val;

				if (fValue.find(',') != -1) {
					fValue = fValue.substr(fValue.find(',') + 1);
				}
				else {
					break;
				}
			}
			header.formatFields.push_back(format);

		}},
		{"alt", [](const std::string& value, VCFHeader& header) {
		string aValue = value;
			AltField alt;
			while (aValue.find('=') != string::npos) {
				string token = aValue.substr(0, aValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, aValue.find("=")));
				string val = clearOfDoubleQuotation(token.substr(token.find("=") + 1));
				key = toLower(key);
				if (key == "id") alt.ID = val;
				else if (key == "description") alt.Description = val;
				else alt.AdditionalAttributes[key] = val;

				if (aValue.find(',') != -1) {
					aValue = aValue.substr(aValue.find(',') + 1);
				}
				else {
					break;
				}
			}
			header.altFields.push_back(alt);

		}},
		{"assembly", [](const std::string& value, VCFHeader& header) {
			header.assembly = value;
		}},
		{"contig", [](const std::string& value, VCFHeader& header) {
			string cValue = value;
			ContigField contig;
			while (cValue.find('=') != string::npos) {
				string token = cValue.substr(0, cValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, token.find('=')));
				string val = clearOfDoubleQuotation(token.substr(token.find('=') + 1));
				key = toLower(key);
				if (key == "id") contig.ID = val;
				else if (key == "length") contig.Length = std::stoul(val);
				else contig.AdditionalAttributes[key] = val;
				if (cValue.find(',') != -1) {
					cValue = cValue.substr(cValue.find(',') + 1);
				}
				else {
					break;
				}
			}

			header.contigFields.push_back(contig);
		}},
		{"meta", [](const std::string& value, VCFHeader& header) {
			string mValue = value;
			MetaField meta;
			while (mValue.find('=') != string::npos) {
				string token = "";
				string key = clearOfDoubleQuotation(mValue.substr(0, mValue.find('=')));
				string val = "";
				if (toLower(key) == "values") {
					token = mValue.substr(0, mValue.find(']') + 1);
					val = clearOfDoubleQuotation(token.substr(token.find('['), token.find(']')));
					val = val.substr(1, val.size() - 2);
					while (val.find(",") != string::npos) {
						meta.Values.push_back(val.substr(0, val.find(",")));
						val = val.substr(val.find(",") + 1);
					}
					meta.Values.push_back(val);
				}
				else {
					token = mValue.substr(0, mValue.find(','));
					val = clearOfDoubleQuotation(token.substr(token.find('=') + 1));
				}
				key = toLower(key);
				if (key == "id") meta.ID = val;
				else if (key == "type") meta.Type = val;
				else meta.AdditionalAttributes[key] = val;
				if (mValue.find(',') != -1) {
					mValue = mValue.substr(mValue.find(',') + 1);
				}
				else {
					break;
				}
			}

			header.metaFields.push_back(meta);
		}},
		{ "sample", [](const std::string& value, VCFHeader& header) {
			string sValue = value;
			SampleField sample;
			while (sValue.find('=') != string::npos) {
				string token = sValue.substr(0, sValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, token.find('=')));
				string val = clearOfDoubleQuotation(token.substr(token.find('=') + 1));
				key = toLower(key);
				if (key == "id") sample.ID = val;
				else if (key == "assay") sample.Assay = val;
				else if (key == "ethnicity") sample.Ethnicity = val;
				else if (key == "disease") sample.Disease = val;
				else if (key == "description") sample.Description = val;
				else if (key == "dio") sample.DIO = val;
				else sample.AdditionalAttributes[key] = val;
				if (sValue.find(',') != -1) {
					sValue = sValue.substr(sValue.find(',') + 1);
				}
				else {
					break;
				}
			}

			header.sampleFields.push_back(sample);
		}},
		{ "pedigree", [](const std::string& value, VCFHeader& header) {
			string pValue = value;
			PedigreeField pedigree;
			while (pValue.find('=') != string::npos) {
				string token = pValue.substr(0, pValue.find(','));
				string key = clearOfDoubleQuotation(token.substr(0, token.find('=')));
				string val = clearOfDoubleQuotation(token.substr(token.find('=') + 1));
				key = toLower(key);
				if (key == "id") pedigree.ID = val;
				else pedigree.AdditionalAttributes[key] = val;
				if (pValue.find(',') != -1) {
					pValue = pValue.substr(pValue.find(',') + 1);
				}
				else {
					break;
				}
			}
			header.pedigreeFields.push_back(pedigree);
		} },
		{ "pedigreeDB", [](const std::string& value, VCFHeader& header) {
			header.pedigreeDB = value;
		}},
		{"source", [](const std::string& value, VCFHeader& header) {
			header.source = value;
		}},
		{"reference", [](const std::string& value, VCFHeader& header) {
			header.reference = value;
		}},
		{ "phasing", [](const std::string& value, VCFHeader& header) {
			header.phasing = value;
		}},
		{ "recordHeader", [](const std::string& value, VCFHeader& header) {
			header.recordHeader = splitString(value, '\t');
		} }
	};


	void parseHeaderLine(const std::string& plainLine, VCFHeader& header) {
		if (plainLine.substr(0, 2) == "#C") {
			string key = "recordHeader";
			string line = plainLine.substr(1); // Remove leading '#'
			header.headerLines.push_back(line);
			auto it = handlers.find(key);
			if (it != handlers.end()) {
				it->second(line, header);
			}
			return;
		}
		string line = plainLine.substr(2); // Remove leading '##'
		header.headerLines.push_back(line);
		string key = toLower(line.substr(0, line.find('=')));

		auto it = handlers.find(key);
		if (it != handlers.end()) {
			string value = line.substr(line.find('=') + 1);
			if (value[0] == '<' && value.back() == '>')
				value = value.substr(1, value.size() - 2);
			it->second(value, header);
		}
	
	}
}