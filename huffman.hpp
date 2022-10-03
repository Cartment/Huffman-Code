#include <map>
#include <deque>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

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


class Huffman{
private:
	std::unordered_map<char, std::string> dict;
	std::string input_path, output_path;
public:
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
			std::cout<<i.first<<" "<<i.second<<std::endl;
			if(to_build.find(i.second) != to_build.end()){
				to_build[i.second].emplace_back(new Node(i.first, i.second, nullptr, nullptr));
			}

			else{
				std::vector<Node*> temp;
				temp.emplace_back(new Node(i.first, i.second, nullptr, nullptr));
				to_build.insert(std::make_pair(i.second ,temp));//
			}
		}
	}

	void writeFile(std::string i, std::string o){
		std::ofstream ofs;
		ofs.open(o);
		std::ifstream ifs(i);
		char c;
		ifs >> c;
		while(!ifs.eof()){
			if(c == '\n')
				continue;
			ofs << (dict[c]);
			// std::cout << dict[c]<<std::endl;
			ifs >> c;
		}
		ifs.close();
		ofs.close();
		return;
	}

	void buildHuffmanTree(){
		while(to_build.size()>1 || to_build.begin()->second.size()>1){

			// std::cout << to_build.begin()->first << " ";
			Node* ptr1 = to_build.begin()->second.back();
			to_build.begin()->second.pop_back();
			if(to_build.begin()->second.empty())
				to_build.erase(to_build.begin());

			// std::cout << to_build.begin()->first << std::endl;
			Node* ptr2 = to_build.begin()->second.back();
			to_build.begin()->second.pop_back();
			if(to_build.begin()->second.empty())
				to_build.erase(to_build.begin());

			Node* parentNode = new Node(-1, ptr1->count + ptr2->count, ptr1, ptr2);
			to_build[parentNode -> count].emplace_back(parentNode);
			// std::cout << parentNode -> count<<std::endl;
		}
	}


	void print_and_build_dict(Node *ptr, std::string s){
		// std::cout<<" IN \n";
		if(ptr -> l == nullptr || ptr -> r == nullptr){
			std::cout << "Cur val is " << ptr->val << " " << s << std::endl;
			dict[ptr -> val] = s;
			return;
		}
		print_and_build_dict(ptr -> l, s + "0");
		print_and_build_dict(ptr -> r, s + "1");
	}


	Huffman(std::string _input_path, std::string _output_path){
		input_path = _input_path;
		output_path = _output_path;
		readFile_to_m(input_path);
		buildHuffmanTree();
		print_and_build_dict(to_build.begin()->second.back(), std::string(""));
		writeFile(input_path, output_path);
	}
};





// 1 3 5 6 12 15 18 21 23 24 29 32 35 55 => 4
// 4 5 6 12 15 18 21 23 24 29 32 35 55 => 9
// 6 9 12 15 18 21 23 24 29 32 35 55 => 15
// 12 15 15 18 21 23 24 29 32 35 55 => 27
// 15 18 21 23 24 27 29 32 35 55 => 33
// 21 23 24 27 29 32 33 35 55 => 44
// 24 27 29 32 33 35 44 55 => 51
// 29 32 33 35 44 51 55 => 61
// 33 35 44 51 55 61 => 68
// 44 51 55 61 68 => 95
// 55 61 68 95 => 116
// 68 95 116 => 163
// 116 163 => 274
// 274 => End