#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

std::tuple<double, double, double> BoxInfo(std::vector<double> v, int zn) {
    double meen = 0, med = 0, stddev = 0;
    double min, lq, uq, max, sum;
    int size = v.size();
    std::sort(v.begin(), v.end());

    for(int i = 0; i < size; i++){
        sum += v[i];
    }

    if(size%2 != 0) med = v[size/2 + 1];
    else med = v[size/2] + v[size/2 + 1];

    if((size/2)%2 != 0) lq = v[size/4 + 1];
    else lq = v[size/4] + v[size/4 + 1];

    if((size/2)%2 != 0) uq = v[size/4*3 + 1];
    else uq = v[size/4*3] + v[size/4*3 + 1];

    min = lq - 1.5*(uq-lq);
    max = uq + 1.5*(uq-lq);

    meen = sum / size;

    double tmp = 0;
    for(int i = 0; i < size; i++){
        tmp += std::pow((v[i] - meen), 2);
    }
    stddev = std::sqrt(tmp/size);

    std::vector<double> out;
    int i = 0;
    while(v[i] < min){
        out.push_back(v[i]);
        i++;
    }
    i = size - 1;
    while(v[i] > max){
        out.push_back(v[i]);
        i--;
    }

    std::cout.setf(std::ios::right);
    std::cout.precision(zn);
    std::cout << "min: " << std::cout.width(4) << std::scientific << std::setw(6) << min << std::endl;
    std::cout << "lq: " << std::cout.width(5) << std::scientific << std::setw(6) << lq << std::endl;
    std::cout << "median: " << std::cout.width(0) << std::scientific << std::setw(6) << med << std::endl;
    std::cout << "meen: " << std::cout.width(3) << std::scientific << std::setw(6) << meen << std::endl;
    std::cout << "stddev: " << std::cout.width(0) << std::scientific << std::setw(6) << stddev << std::endl;
    std::cout << "uq: " << std::cout.width(5) <<std::scientific << std::setw(6) << uq << std::endl;
    std::cout << "max: " << std::cout.width(4) << std::scientific << std::setw(6) << max << std::endl;
    if(out.size() != 0){
        std::string tmp = "";
        for(int i = 0; i < out.size(); i++){
            tmp += std::to_string(out[i]);
        }
        std::cout << "out: " << std::cout.width(4) << std::scientific << std::setw(6) << out[i] << std::endl;
    }

    return std::make_tuple(meen, med, stddev);
}