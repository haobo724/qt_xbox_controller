#include "testqstring.h"
#include <QFileInfo>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QPushButton>
#include <QLabel>

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

    Record *test_reco = new Record();
    test_reco->start();
    QFileInfo file("./log_gamePad.txt");
    QVERIFY(file.isFile() == true);
}

void TestQString::testmainwindow()
{
    MainWindow* test_ui = new MainWindow();
    QPushButton* testBtn = test_ui->findChild<QPushButton*>("pbnCP");
    QLabel* testlb = test_ui->findChild<QLabel*>("lbCP");


    QTest::mouseClick ( testBtn, Qt::LeftButton, Qt::NoModifier);
    QCOMPARE(testlb->text(), QString("hi"));

}
#include "testqstring.moc"

