/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   csv.cpp
 * Author: user
 *
 * Created on 22 kwietnia 2017, 19:27
 */

#include "csv.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>

using namespace std;

csv::csv() {
}

csv::csv(string fName) {
    fileName = fName;
    csv::file.open(fName.c_str(),ios_base::app);
}

csv::~csv() {
    file.close();
}

void csv::addToRecord(float fPomiar){
    char sPomiar[32];

    sprintf(sPomiar, "%f", fPomiar);
    csv::record += sPomiar;
    csv::record += ";";
    cout<<csv::record<<endl;
}


void csv::storeRecord(){
    csv::record = csv::record.substr(0, csv::record.size()-1);
    csv::record += "\n";
    csv::file.write(csv::record.c_str(), csv::record.size());
}
