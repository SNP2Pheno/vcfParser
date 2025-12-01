#pragma once
#include<string>
#include"VCFHeader.h"

namespace vcf {

void parseHeaderLine(const std::string& plainLine, VCFHeader&);

}