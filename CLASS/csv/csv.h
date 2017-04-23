/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   csv.h
 * Author: user
 *
 * Created on 22 kwietnia 2017, 19:27
 */

#ifndef CSV_H
#define CSV_H

#include <fstream>

using namespace std;



class csv {
public:
    string fileName;
    fstream file;
    string record;
    csv();
    /**\<html><h3>tworzy plik o nazwie fName</h2><p></p></html>
     * \param fName
     * \return void
     */
    csv(string);
    /**\<html><h2>funkcja dopisuj¹ca do rekordu kolejne pomiary</h2><p>tworzy liniê w pliku csv kolejne wartoœci rozdzielone znakiem ';'</p></html>
     * \param fPomiar float
     * \return void
     */
    void addToRecord(float);
    /**\<html><h2>zapisuje do pliku kolejny rekord (liniê)</h2><p></p></html>
     * \return void
     */
    void storeRecord();
    virtual ~csv();
private:

};

#endif /* CSV_H */

