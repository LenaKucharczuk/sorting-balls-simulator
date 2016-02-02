//
// Created by Lena khan on 2016-02-02.
//

#ifndef SORTOWANIEKULEK_SLIPPERYSLOPE_H
#define SORTOWANIEKULEK_SLIPPERYSLOPE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>

class SlipperySlope
{
private:
    std::vector<int> dataOrginal;
    std::vector<int> data;	// sortuje na nim algorytm nr 1
    std::vector<int> data2;	// sortuje na nim alg 2
    std::vector<int> data3;
    std::vector<int> ready;	// przechowuje posortowane kulki
    std::vector<int> thirds;	// przechowuje co trzecią kulkę
    int quality;
    int quality2;
    int quality3;
    double t1;
    double t2;
    double t3;

public:
    void quality_reset();
    int getQ(int algorithm);
    double getT(int algorithm);
    bool show_steps;
    void generateData(int counter, int denominator, int number);	// generator danych
    void addData();
    void show(int algorithm);
    int slipSize();

    bool shift(int algorithm, int number, int position);

    void isOk(int algorithm);

    void algorithm1();
    void algorithm2();
    void algorithm3();

    // pomocniczo dla algorytmu 1
    int howMany(int colour, int position, int end);
    bool naive(int currentColor, int position, bool lookForCurr);
    bool prepare(int modulo, int currentColor, int position);

    SlipperySlope();
};


#endif //SORTOWANIEKULEK_SLIPPERYSLOPE_H
