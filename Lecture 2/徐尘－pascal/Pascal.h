//
//  Pascal.h
//  hw2.4
//
//  Created by xuchen on 1/17/15.
//  Copyright (c) 2015 __ChenXu__. All rights reserved.
//
#ifndef PASCAL_H
#define PASCAL_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class Helper{
public:
    int numDigits(int i);
    int numDigits_alternate(int i);
    string centeredInt(int i, int eltSize);
};

class Row{
    vector<int> rowData;
public:
    //construct row with data
    Row(vector<int> data):rowData(data){};
    
    //default constructor, set data as 0th row
    Row();
    
    //get next Row according to data to current Row
    Row* nextRow();
    
    //print row
    void printRow(int eltSize);
    
    //return the max element in this row 
    int maxElement();
};

class Triangle{
    vector<Row> triangleData;
    int size;
public:
    //construct a triangle with n layers
    Triangle(int rowNum);
    
    //print triangle
    void printTriangle();
};

#endif