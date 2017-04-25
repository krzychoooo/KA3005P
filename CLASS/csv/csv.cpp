/*
 * zachowajta mój email i róbta co chceta.
 */

/*
 * File:   csv.cpp
 * Author: fajnysoft@gmail.com
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
    csv::file.close();
}

void csv::addToRecord(float fPomiar){
    char sPomiar[32];
    setlocale(LC_ALL, "Polish");
    sprintf(sPomiar, "%f", fPomiar);
    csv::record += sPomiar;
    csv::record += ";";
    setlocale(LC_ALL, "USA");
    //cout<<csv::record<<endl;
}

void csv::storeRecord(){
    csv::record = csv::record.substr(0, csv::record.size()-1);
    csv::record += "\n";
    csv::file.write(csv::record.c_str(), csv::record.size());
    csv::record = "";
}
