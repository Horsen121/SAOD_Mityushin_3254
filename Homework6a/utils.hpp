#include <iostream>
#include <string>

class Array;

class _data {
	int* pData;
	int nCount;

	friend class Array;

	_data(int sz, int *p = 0) {
		nCount = 1;
        pData = new int[sz];
        if(*p != 0){
            for(int i = 0; i < sz; i++, p++){
                pData[i] = *p;
            }
        }
        else{
            for(int i = 0; i < sz; i++){
                pData[i] = 0;
            }
        }
	}
	~_data () { 
        delete []pData;
    }

	void AddRef() {
        nCount++;
    }
	void Release () {
        nCount--; 
        if(nCount == 0){
            delete this;
        }
    } 
};

class Array {
	_data* pDataRef;
    int rows;
    int cols;
public:
	Array(int m, int n, int *p = 0) {
        rows = m;
        cols = n;
		pDataRef = new _data(m*n, p);
	}
    Array(const Array &arr) {
        pDataRef = arr.pDataRef;
        rows = arr.rows;
        cols = arr.cols;
        pDataRef->AddRef();
    }

    int Rows()const { 
        return rows; 
    }
	int Cols()const { 
        return cols; 
    }
    int& Item(int i, int j) {
        if(i >= 0 && i < rows && j >= 0 && j < cols){
            return pDataRef->pData[i*this->cols + j];
        }
        throw std::out_of_range("Index out of range");
    }
    int Item(int i, int j)const {
        if(i >= 0 && i < rows && j >= 0 && j < cols){
            return pDataRef->pData[i*this->cols + j];
        }
        throw std::out_of_range("Index out of range");
    }
    int Ref()const {
        return pDataRef->nCount;
    }

    Array Clone(){
        return Array(this->rows, this->cols, this->pDataRef->pData);
    }

	~ Array () { 
		pDataRef -> Release();
	}
};

std::ostream & operator << (std::ostream &os, const Array &arr) {
    std::string tmp = "";
    for(int i = 0; i < arr.Rows(); i++){
        tmp += '[';
        for(int j = 0; j < arr.Cols(); j++){
            tmp += std::to_string(arr.Item(i, j));
            if(arr.Cols() - j > 1){
                tmp += ", ";
            }
        }
        tmp += "]\n";
    }
    return os << tmp;
}