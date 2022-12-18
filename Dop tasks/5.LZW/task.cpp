#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <chrono>
#include "lzw.hpp"


void Convert(std::vector<int>& arr, char* val){
    int len =  strlen(val);
    int res = 0;

    for(size_t i = 0; i < len; i++) {
        if(val[i] == '1')
            res += pow(2, i);
    }
    
    arr.push_back(res);
}

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
        ifstream input(argv[2], ios_base::in); //, ios_base::in
        if(!input.is_open()){
            cout << "Fatal error! Input file don't opened." << endl;
            exit(-1);
        }

        string text, tmp;
        while(!input.eof()){
            input >> tmp;
            text.append(tmp + " ");
        }
        input.close();

        vector<int> res = encoding(text);

        size_t maxv = *std::max_element(res.begin(), res.end());
        size_t mask_size = 0;
        for(mask_size; maxv >= pow(2, mask_size);){
            mask_size++;
        }

        // create encoded_file
        fstream output(argv[3], ios_base::binary|ios::out); //, ios_base::binary|ios::out
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
        vector<ulong> metav = {nulcount, mask_size, res.size()};
        for(const auto & v : metav) {
			std::bitset<8> b(v);
			meta += b.to_string();
		}
        // std::bitset<32> b(res.size());
		// meta += b.to_string();

        cout << mask_size << " " << res.size() << endl;

        for(size_t i = 0; i < meta.size()-1; i+=8) {
            std::bitset<8> b;
            std::string ss = meta.substr(i, 8);
            for(int j = 0; j < 8; j++)
                b[j] = ss[j] == '0' ? 0 : 1;
            output << static_cast<char>(b.to_ulong());
        }
        // std::bitset<32> b;
        // std::string ss = meta.substr(16, 32);
        // for(int j = 0; j < 32; j++)
        //     b[j] = ss[j] == '0' ? 0 : 1;
        // output << static_cast<char>(b.to_ulong());
        
		for(size_t i = 0; i < bitstr.size(); i+=8) {
			std::bitset<8> b;
			std::string ss = bitstr.substr(i, 8);
			for(int j = 0; j < 8; j++)
				b[j] = ss[j] == '0' ? 0 : 1;
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
        FILE * encoded;
        encoded = fopen(argv[2], "rb");
        std::bitset<8> con, mask;
        std::bitset<32> count;
        vector<int> code, meta;

        fread(&con, 8, 1, encoded);
        fread(&mask, 8, 1, encoded);
        fread(&count, 32, 1, encoded);

        Convert(meta, con.to_string().data());
        Convert(meta, mask.to_string().data());
        Convert(meta, count.to_string().data());
        cout << con.to_string() << " " << mask.to_string() << " " << count.to_string() << endl;
        cout << meta[0] << " " << meta[1] << " " << meta[2] << endl;

        int length = meta[1], fcount = meta[2];
        for(int i=0; i < fcount; i++) {
            std::bitset<16> tmp;
            fread(&tmp, length, 1, encoded);
            Convert(code, tmp.to_string().data());
            cout << code[i] << endl;
        }
        fclose(encoded);
        string res = decoding(code);

        // // create check_file
        ofstream check(argv[3], ios_base::out); //, ios_base::out
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