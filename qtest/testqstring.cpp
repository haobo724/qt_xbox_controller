#include "testqstring.h"
#include <QFileInfo>
#include <iostream>
#include <QTextStream>
#include <QDebug>

QTEST_MAIN(TestQString)
/* After creating QApplication instance */

TestQString::TestQString(QObject *parent)
    : QObject{parent}
{

}

void TestQString::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

void TestQString::testRecoder()
{   
	std::cout << "string to print" << endl;
	std::cout.flush();
	qDebug() << "C++ Style Debug Message";
    Record *test_reco = new Record();
    test_reco->start();
    QFileInfo file("./log_gamePad.txt");
    QVERIFY(file.isFile()==true);
}
void TestQString::testmainwindow()
{   
	
}