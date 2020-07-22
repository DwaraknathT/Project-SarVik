#include "CSVparser.hpp"

struct data { 
     float x;
     float y;
     float z;
     float dosage;
} ;        
class Parser
{
public:
	std::vector<data> records;
	void LoadStructs(std::string fileName) {
		csv::Parser parse(fileName);
		data record, rp;
		for (int i = 0; i < 1331; i++)
		{
			record.x = std::atof(parse[i][0].c_str());
			record.y = std::atof(parse[i][1].c_str());
			record.z = std::atof(parse[i][2].c_str());
			record.dosage = std::atof(parse[i][3].c_str()) / 10000;
			records.push_back(record);
		}

		for (int i = 0; i < 5; ++i)
		{
			rp = records[i];
			printf(" %ld", rp.x);
		}
	}

};

