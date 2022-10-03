#include "huffman.hpp"
using namespace std;


int main(){
	bool flag;
	string in_path, out_path;
	cout << "Default input file path is \"Inputs/Input1.txt\"\n";
	cout << "Default output file path is \"Outputs/Output1.txt\"\n";
	cout << "Run on default file? (Yes/No : 1/0)\n";
	cin >> flag;
	if(!flag){
		cout << "Please input the input file path : " << endl;
		cin >> in_path;
		cout << "Please input the output file path : " << endl;
		cin >> out_path;
	}
	else{
		in_path = "Inputs/Input1.txt";
		out_path = "Outputs/Output1.txt";
	}
	cout << "Show Huffman Coding Detail? (Yes/No : 1/0)\n";
	cin >> flag;
	Huffman(in_path, out_path, flag);
	cout<< "Encode complete! The output file is now at " << out_path << " (relate to the current folder)" << endl;
	return 0;
}