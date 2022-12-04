#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <chrono>
#include "lzw.hpp"

int main(int argc, char* argv[]){
    using std::cout;
    using std::endl;

    string h = "-h";
    string e = "-e";
    string d = "-d";

    if(argv[1] == h){
        cout << endl << "This is LZW coding compressor for ASCII text files." << endl;
        cout << "General options:" << endl;
        cout << "\t-h [ --help ]              Show help" << endl;
        cout << "\t-e [ --encoding ]          Encoding file (-e input.txt output.encoded)" << endl;
        cout << "\t-d [ --decoding ]          Decoding file (-d output.encoded check.txt)" << endl;
    }
    else if(argv[1] == e) {
        if(argc != 4) {
            cout << "Fatal error! Wrong number of parameters!!!" << endl;
            exit(-1);
        }
        auto time_one = chrono::high_resolution_clock::now();

        // open input_file
        ifstream input(argv[2]); //, ios_base::in
        if(!input.is_open()){
            cout << "Fatal error! Input file don't opened." << endl;
            exit(-1);
        }

        string text;
        input >> text;
        vector<int> res = encoding(text);
        input.close();

        size_t maxv = *std::max_element(res.begin(), res.end());
        size_t mask_size = 0;
        for(mask_size; maxv >= pow(2, mask_size);){
            mask_size++;
        }

        // create encoded_file
        fstream output(argv[3], ios_base::binary); //, ios_base::binary|ios::out
        if(!output.is_open()){
            cout << "Fatal error! Encoded file don't created." << endl;
            exit(-1);
        }

        // // write res to output_file
        std::bitset<1024> bs(maxv);
        std::string s = bs.to_string().substr(1024-mask_size, mask_size);
        std::string bitstr;
        for(const auto & v : res) {
			std::bitset<1024> b(v);
			bitstr += b.to_string().substr(1024-mask_size, mask_size);
		}

        size_t nulcount = 0;
		while(bitstr.size() % 8 != 0){
            nulcount++;
			bitstr.push_back('0');
        }

        std::string meta;
        vector<ulong> metav = {nulcount, mask_size, ']'};
        for(const auto & v : metav) {
			std::bitset<10> b(v);
			meta += b.to_string();
		}

        for (size_t i = 0; i < meta.size(); i++){
            std::bitset<8> b;
            std::string ss = meta.substr(i, 8);
            for(int j = 0; j < 8; j++)
                b[j] = ss[7-j] == '0' ? 0 : 1;
            output << static_cast<char>(b.to_ulong());
        }
        
		for(size_t i = 0; i < bitstr.size(); i+=8) {
			std::bitset<8> b;
			std::string ss = bitstr.substr(i, 8);
			for(int j = 0; j < 8; j++)
				b[j] = ss[7-j] == '0' ? 0 : 1;
			output << static_cast<char>(b.to_ulong());
		}
        
        output.close();
        auto time_two = chrono::high_resolution_clock::now();
        size_t time = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
        cout << "Done!" << endl;
        size_t size_i = input.tellg(), size_o = output.tellg();
        cout << "Compression ratio: " << size_i << " bytes / " << size_o << " bytes = " << size_i/size_o << endl;
        cout << "Compression time: " << time << " sec" << endl << endl;
    }
    else if(argv[1] == d){ 
        if(argc != 4) {
            cout << "Fatal error! Wrong number of parameters!!!" << endl;
            exit(-1);
        }
        auto time_one = chrono::high_resolution_clock::now();

        // open encoded_file
        fstream encoded(argv[2], ios_base::binary); //, ios_base::binary|ios::in
        if(!encoded.is_open()){
            cout << "Fatal error! Input file don't opened." << endl;
            exit(-1);
        }

        // read encoded code
        // vector<int> code((istream_iterator<int>(encoded)), istream_iterator<int>());
        string tmp;
        vector<int> code;

        string res = decoding(code);
        encoded.close();
        // create check_file
        ofstream check(argv[3]); //, ios_base::out
        if(!check.is_open()){
            cout << "Fatal error! Encoded file don't created." << endl;
            exit(-1);
        }
        // write res to check_file
        check.write(res.data(), strlen(res.data())*sizeof(char));
        
        check.close();
        auto time_two = chrono::high_resolution_clock::now();
        size_t time = chrono::duration_cast<chrono::seconds>(time_two - time_one).count();
        cout << "Done!" << endl;
        cout << "Decompression time: " << time << " sec" << endl;
    }

    return 0;
}