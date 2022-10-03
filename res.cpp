#include "huffman.hpp"
using namespace std;


int main(){
	bool flag;
	string in_path, out_path;
	cin >> flag;
	if(flag){
		cout << "Please input the input file path : " << endl;
		cin >> in_path;
		cout << "Please input the output file path : " << endl;
		cin >> out_path;
	}
	else{
		in_path = "Inputs/Input1.txt";
		out_path = "Outputs/Output1.txt";
	}
	Huffman(in_path, out_path);
	cout<< "Encode complete!" << endl;
	return 0;
}