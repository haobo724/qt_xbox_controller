#ifndef TESTQSTRING_H
#define TESTQSTRING_H

#include <QObject>
#include <QTest>
#include "record.h"

/* In Header */


class TestQString : public QObject
{
    Q_OBJECT
public:
    explicit TestQString(QObject *parent = nullptr);

private slots:
    void toUpper();
    void testRecoder();
    void testmainwindow();
};

#endif // TESTQSTRING_H
