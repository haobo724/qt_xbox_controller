#include "record.h"
#include "test.h"
#include <string>
#include <iomanip>
#include <ctime>

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
    //convert
    time_t local_time = std::time(nullptr);
    tm tm = *std::localtime(&local_time);

    of.open(logFileName,ofstream::app);
    of<< text<<" "<<put_time(&tm, "%c %z")<<dummy_input() << endl<<endl;
    of.close();
}
