#ifndef RECORD_H
#define RECORD_H

#include<iostream>
#include<fstream>
#include<QObject>
using namespace std ;
class Record:public QObject
{
    Q_OBJECT
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
