//
//  Pascal.cpp
//  hw2.4
//
//  Created by xuchen on 1/21/15.
//  Copyright (c) 2015 __ChenXu__. All rights reserved.
//

#include "Pascal.h"
#include <numeric>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

/**
 *  return the number of digits in a number
 *
 *  @param i a integer number
 *
 *  @return digits of i
 */
int Helper::numDigits(int i){
    int digits = 1;
    while((i/=10) != 0) {
        digits++;
    }
    return digits;
}

/**
 *  a alternative way to return the number of digits in a number
 *
 *  @param i a integer number
 *
 *  @return digits of i
 */
int Helper::numDigits_alternate(int i){
    ostringstream os;
    os << i;
    return (int)os.str().size();
}

/**
 *  return a string with a number aligned in the center of it
 *
 *  @param i       the number
 *  @param eltSize the length of output string
 *
 *  @return formatted string
 */
string Helper::centeredInt(int i, int eltSize){
    ostringstream os;
    os << i;
    string str = os.str();
    return string((eltSize - str.size())/2, ' ') + str;
}

/**
 *  default constructor for Row
 */
Row::Row(){
    rowData.push_back(1);
}

/**
 *  get next Row according to data to current Row
 *
 *  @return next Row
 */
Row* Row::nextRow(){
    vector<int> nextData;
    int previous = 0;
    for(auto elt: rowData){
        nextData.push_back(elt + previous);
        previous = elt;
    }
    nextData.push_back(previous);
    return new Row(nextData);
}

/**
 *  print Row with every number centered in a brick of given size
 *
 *  @param eltSize the width of a brick
 */
void Row::printRow(int eltSize){
    Helper* helper = new Helper();
    
    for(auto elt: rowData) {
        cout << left << setw(eltSize) <<helper->centeredInt(elt,eltSize) << " ";
    }
    cout << endl;
}

/**
 *  return max number in a row
 *
 *  @return the max value
 */
int Row::maxElement(){
    return *max_element(rowData.begin(), rowData.end());
}

/**
 *  constructor of Triangl
 *
 *  @param rowNum how many row in this triangle
 */
Triangle::Triangle(int rowNum):size(rowNum){
    if (rowNum <= 0) {
        throw std::invalid_argument("invalid input");
    }
    
    Row* row = new Row();
    for (int i = 0; i < rowNum; i++) {
        triangleData.push_back(*row);
        row = row->nextRow();
    }
}

/**
 *  print the pascal triangle in brick-wall way
 */
void Triangle::printTriangle(){
    Helper* helper = new Helper();
    Row lastRow = triangleData[size - 1];
    int maxElement = lastRow.maxElement();
    int eltSize = helper->numDigits(maxElement);
    for(int i = 0; i < size; i++) {
        string spaces((size - i - 1) * (eltSize + 1) / 2, ' ');
        cout << spaces;
        triangleData[i].printRow(eltSize);
    }
}