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
        // if(!fork()){
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

            // create encoded_file
            ofstream output(argv[3]); //, ios_base::binary|ios::out
            if(!output.is_open()){
                cout << "Fatal error! Encoded file don't created." << endl;
                exit(-1);
            }

            // write res to output_file
            for(size_t i = 0; i < res.size(); i++)
                output << res[i] << " ";
            
            output.close();

            auto time_two = chrono::high_resolution_clock::now();
            size_t time = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();

            cout << "Done!" << endl;
            cout << "Compression ratio: " << sizeof(input) << " bytes / " << sizeof(output) << " bytes = " << sizeof(input)/sizeof(output) << endl;
            cout << "Compression time: " << time << " sec" << endl << endl;

        //     exit(0);
        // }
    }
    else if(argv[1] == d){ 
        if(argc != 4) {
            cout << "Fatal error! Wrong number of parameters!!!" << endl;
            exit(-1);
        }
        // if(!fork()){
            auto time_one = chrono::high_resolution_clock::now();

            // open encoded_file
            fstream encoded(argv[2]); //, ios_base::binary|ios::in
            if(!encoded.is_open()){
                cout << "Fatal error! Input file don't opened." << endl;
                exit(-1);
            }

            // read encoded code
            vector<int> code((istream_iterator<int>(encoded)), istream_iterator<int>());
            
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
            size_t time = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();

            cout << "Done!" << endl;
            cout << "Decompression time: " << time << " sec" << endl;

        //     exit(0);
        // }
    }

    return 0;
}