    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <string>
    using namespace std;
    typedef vector<string> LINE;
    int main()
    {
    	string line;
    	int pos;
    	vector<LINE> array;
    	ifstream in("/home/felixfaker/Proj/data.csv");
    	if(!in.is_open())
    	{
    		cout << "Failed to open file" << endl;
    		return 1;
    	}
    	while( getline(in,line) )
    	{
    		LINE ln;
    		while( (pos = line.find(',')) >= 0)
    		{
    			string field = line.substr(0,pos);
    			line = line.substr(pos+1);
    			ln.push_back(field);
    		}
    		array.push_back(ln);
    	}
    	return 0;
    }
