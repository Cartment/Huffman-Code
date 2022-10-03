#include <map>
#include <deque>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <fstream>
#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <unordered_map>



// Huffman Nodes
class Node {
public:
	char val;
	int count;
	Node* l;
	Node* r;

	Node(char _val, int _count, Node* _l, Node* _r) {
		val =  _val;
		count = _count;
		l = _l;
		r = _r;
	}
};

// read file and build Huffman Tree
class Huffman{

private:
	// here are the dict and file paths
	std::unordered_map<char, std::string> dict;
	std::string input_path, output_path;
	bool showDetail;

public:
	// store_input takes the datas in the inputfile, to build store the sorted key
	std::unordered_map<char, int> store_input;
	std::map<int, std::vector<Node*>> to_build;

	void readFile_to_m(std::string in_path){
		char c;
		std::ifstream ifs(in_path);
		ifs >> c;
		while(!ifs.eof()) {
			if(c == '\n')
				continue;
			store_input[c]++;
			ifs >> c;
		}
		ifs.close();

		for(auto &i:store_input){
			// std::cout<<i.first<<" "<<i.second<<std::endl;
			if(to_build.find(i.second) != to_build.end()){
				to_build[i.second].emplace_back(new Node(i.first, i.second, nullptr, nullptr));
			}

			else{
				std::vector<Node*> temp;
				temp.emplace_back(new Node(i.first, i.second, nullptr, nullptr));
				to_build.insert(std::make_pair(i.second ,temp));//
			}
		}

		// The following comments are mean to check some datas
		if(showDetail){
			std::cout<<std::endl<<std::endl;
			for(auto &i:to_build){
				std::cout << "Character(s) below occurs " << i.first << " times." << std::endl;
				for(auto &j:i.second){
					std::cout<<j->val<<" ";
				}
				std::cout<<std::endl<<std::endl;
			}
		}
	}

	void writeFile(std::string i, std::string o){
		std::ofstream ofs;
		std::ifstream ifs(i);
		ofs.open(o, std::ios::out | std::ios::binary);
		char c;
		while(!ifs.eof()){
			if(c == '\n')
				continue;
			// for(auto &i:dict[c])
			// 	ofs<<(i-'0');
			ofs << (dict[c]);
			ifs >> c;
		}
		ifs.close();
		ofs.close();
		return;
	}

	void buildHuffmanTree(){
		while(to_build.size()>1 || to_build.begin()->second.size()>1){
			
			if(showDetail)
				std::cout << "Merge " << std::setw(7) << to_build.begin()->first << " ";
			Node* ptr1 = to_build.begin()->second.back();
			to_build.begin()->second.pop_back();
			if(to_build.begin()->second.empty())
				to_build.erase(to_build.begin());

			if(showDetail)
				std::cout << std::setw(7) << to_build.begin()->first << std::endl;
			Node* ptr2 = to_build.begin()->second.back();
			to_build.begin()->second.pop_back();
			if(to_build.begin()->second.empty())
				to_build.erase(to_build.begin());

			Node* parentNode = new Node(-1, ptr1->count + ptr2->count, ptr1, ptr2);
			to_build[parentNode -> count].emplace_back(parentNode);
		}
		if(showDetail)
			std::cout<<std::endl;
	}


	void print_and_build_dict(Node *ptr, std::string s){
		if(ptr -> l == nullptr || ptr -> r == nullptr){
			if(showDetail)
				std::cout << ptr->val << " has the frequency " << std::setw(6) << ptr->count << " has been encoded as " << s << std::endl;
			dict[ptr -> val] = s;
			return;
		}
		print_and_build_dict(ptr -> l, s + "0");
		print_and_build_dict(ptr -> r, s + "1");
	}


	Huffman(std::string _input_path, std::string _output_path, bool flag){
		showDetail = flag;
		input_path = _input_path;
		output_path = _output_path;
		readFile_to_m(input_path);
		buildHuffmanTree();
		print_and_build_dict(to_build.begin()->second.back(), std::string(""));
		writeFile(input_path, output_path);
	}
};




/* Encode Process */


// 1 3 3 3 5 6 6 6 6 12 15 18 21 21 23 24 24 29 32 35 55
// 3 3 4 5 6 6 6 6 12 15 18 21 21 23 24 24 29 32 35 55
// 4 5 6 6 6 6 6 12 15 18 21 21 23 24 24 29 32 35 55
// 6 6 6 6 6 9 12 15 18 21 21 23 24 24 29 32 35 55
// 6 6 6 9 12 12 15 18 21 21 23 24 24 29 32 35 55
// 6 9 12 12 12 15 18 21 21 23 24 24 29 32 35 55
// 12 12 12 15 15 18 21 21 23 24 24 29 32 35 55
// 12 15 15 18 21 21 23 24 24 24 29 32 35 55
// 15 18 21 21 23 24 24 24 27 29 32 35 55
// 21 21 23 24 24 24 27 29 32 33 35 55
// 23 24 24 24 27 29 32 33 35 42 55
// 24 24 27 29 32 33 35 42 47 55
// 27 29 32 33 35 42 47 48 55
// 32 33 35 42 47 48 55 56
// 35 42 47 48 55 56 65
// 47 48 55 56 65 77
// 55 56 65 77 95
// 65 77 95 111
// 95 111 142
// 142 206
// 348




