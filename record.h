#ifndef RECORD_H
#define RECORD_H

#include<iostream>
#include<fstream>
using namespace std ;
class Record
{
private:
    string logFileName = "log_gamePad.txt";
    ofstream of;
public:
    Record();
    Record(string s):logFileName(s){};
    void start();
    //template<class T>
    void addText(string text);


};

#endif // RECORD_H
