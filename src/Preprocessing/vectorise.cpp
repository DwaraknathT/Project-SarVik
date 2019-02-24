#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

struct xyz {
    float x;
    float y;
    float z;
};
//function protoypes
void print_xyz(xyz g);


int main(){

    ifstream myfile("test.csv"); //file opening constructor
    //Operation to check if the file opened
    if ( myfile.is_open() ){
        vector<xyz> data;
        float x, y, z;
        char delimiter;
        // Read the file.
        while(myfile >> x >> delimiter >> y >> delimiter >> z){
            data.push_back({x, y, z});
        }
        //To print, uncomment this block
        /* 
        cout << "X" << "   Y" << "   Z \n";
        for (int i(0); i < data.size(); ++i){
            print_xyz( data.at(i) );
        }
        */
    }
    else{
        cerr<<"ERROR: The file isnt open.\n";
    }
    return 0;
}

//To print the vectors

void print_xyz(xyz g){
    cout << g.x << "  "<< g.y <<"  "<< g.z << "\n";
}
