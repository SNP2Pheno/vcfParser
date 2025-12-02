#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "VCFRecord.h"

namespace vcf
{
    std::string toLower(std::string s) {
        for (char& c : s)
            c = std::tolower((unsigned char)c);
        return s;
    }

    std::string clearOfDoubleQuotation(std::string s) {
        if (s[0] == 34 && s.back() == 34)
            return s.substr(1, s.size() - 2);
        return s;
    }

	std::vector<std::string> splitString(const std::string& str, char delimiter) {
        std::string s = str;

        std::stringstream ss(s);
        std::vector<std::string> res;

		while (std::getline(ss, s, delimiter)) {
			res.push_back(s);
		}

		return res;
	}


    EChrom mapChromosome(std::string chrom)
    {
        // normalize: uppercase
        std::transform(chrom.begin(), chrom.end(), chrom.begin(),
            [](unsigned char c) { return std::toupper(c); });

        // remove leading "CHR"
        if (chrom.rfind("CHR", 0) == 0)
            chrom = chrom.substr(3);

        // numeric 1–22
        if (std::all_of(chrom.begin(), chrom.end(), ::isdigit)) {
            int num = std::stoi(chrom);
            if (num >= 1 && num <= 22)
                return static_cast<EChrom>(num);
            else
                return EChrom::NONSTANDARD;
        }

        // special chromosomes
        if (chrom == "X")
            return EChrom::CHRX;
        if (chrom == "Y")
            return EChrom::CHRY;
        if (chrom == "MT" || chrom == "M")
            return EChrom::CHRM;

        // hs37d5 and 1000 Genomes have many nonstandard contigs
        return EChrom::NONSTANDARD;
    }

    std::string cleanLine(std::string l) {

        // UTF-8 BOM (EF BB BF)
        if (l.size() >= 3 &&
            (unsigned char)l[0] == 0xEF &&
            (unsigned char)l[1] == 0xBB &&
            (unsigned char)l[2] == 0xBF) {

            l = l.substr(3);
        }

        // trim left
        while (!l.empty() && (l.front() == ' ' || l.front() == '\t'))
            l.erase(l.begin());

        // trim right
        while (!l.empty() && (l.back() == ' ' || l.back() == '\t'))
            l.pop_back();

        return l;
    }
}
