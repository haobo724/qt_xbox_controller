#include "testqstring.h"
#include <QFileInfo>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QSharedPointer>

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
    delete test_reco;
}

void TestQString::testmainwindow()
{
        MainWindow* new_ui= new MainWindow();

   QPushButton* testBtn = new_ui->findChild<QPushButton*>("pbnCP");
   QLabel*  testlb = new_ui->findChild<QLabel*>("lbCP");


    QTest::mouseClick ( testBtn, Qt::LeftButton, Qt::NoModifier);
    QCOMPARE(testlb->text(), QString("hii"));

    delete new_ui;


}

void TestQString::testtwopb()
{
    MainWindow* new_ui = new MainWindow();

    QPushButton* testBtn = new_ui->findChild<QPushButton*>("pbnCP");
    QPushButton* endBtn = new_ui->findChild<QPushButton*>("pb_endexam");
    QLabel *  testlb = new_ui->findChild<QLabel*>("lbCP");

    testBtn->setEnabled(true);
    testlb->setText(QString("no"));
    QTest::mouseClick ( endBtn, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick ( testBtn, Qt::LeftButton, Qt::NoModifier);


    QCOMPARE(testlb->text(), QString("hii"));
    //new_ui=nullptr;
    delete new_ui;
}
#include "testqstring.moc"

