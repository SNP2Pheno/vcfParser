#include <string>
#include <vector>
#include <sstream>

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
}
