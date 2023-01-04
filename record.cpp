#include "record.h"
#include <string>
Record::Record()
{


}

void Record::start()
{
 of.open(logFileName)  ;
 of.close();
}

void Record::addText(string text)
{

    of.open(logFileName,ofstream::app);
    of<< text<< endl;
    of.close();
}
