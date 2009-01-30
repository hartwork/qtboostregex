/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Qt Boost Regex project on Qt Software Labs.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 or 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QTime>
#include <QDebug>
#include <QStringList>
#include <QRegExp>

#include <qregexengine.h>
#include <qregexmatch.h>
#include <qregexfeedengine.h>
#include <qregexfeedmatch.h>
#include <stringlistregexfeeder.h>



const int NUM_TRIES = 20000;



void stats(int millisQRegExp, int millisBoost) {
    qDebug() << "QRegExp" << millisQRegExp << "|"
            << "Boost" << millisBoost << "|"
            << "Ratio" << (float)millisQRegExp / millisBoost;
}



void testQRegExp(const QString & pattern, const QString & text, int & millisSingle) {
    QTime t0 = QTime::currentTime();
    QRegExp engineOne(pattern);
    for (int i = 0; i < NUM_TRIES; i++) {
        bool success = engineOne.exactMatch(text);
        Q_ASSERT(success);
        success = success;
        const QString fullMatch = engineOne.cap(0);
    }
    QTime t1 = QTime::currentTime();
    millisSingle = t0.msecsTo(t1);

    Q_ASSERT(engineOne.isValid());
}



void testBoost(const QString & pattern, const QString & text, int & millisSingle) {
    QTime t2 = QTime::currentTime();
    QRegexEngine engineTwo(pattern);
    for (int j = 0; j < NUM_TRIES; j++) {
        const QRegexMatch match = engineTwo.exactMatch(text);
        Q_ASSERT(match.isValid());
        const QString fullMatch = match.cap(0);
    }
    QTime t3 = QTime::currentTime();
    millisSingle = t2.msecsTo(t3);

    Q_ASSERT(engineTwo.isValid());
}



void testPattern(const QString & pattern, const QString & text,
        int & millisSumQRegExp, int & millisSumBoost) {
    int millisSingleQRegExp = 0;
    int millisSingleBoost = 0;

    testQRegExp(pattern, text, millisSingleQRegExp);
    millisSumQRegExp += millisSingleQRegExp;

    testBoost(pattern, text, millisSingleBoost);
    millisSumBoost += millisSingleBoost;

    stats(millisSingleQRegExp, millisSingleBoost);
}



#define CASE(pattern, text) testPattern(pattern, text, millisSumQRegExp, millisSumBoost)

void runSpeedTestSuite() {
    int millisSumQRegExp = 0;
    int millisSumBoost = 0;

    CASE("(?:(h.+){2})", "hellohappyworld");
    CASE("^(\\d+ )*\\d+$", "1 12 123 1234 12345 123456 1234567 123456789 1234567890");
/*
    Regular expression speed comparison
    http://snowplow.org/martin/rebench/

    Regular Expression Performance Comparison
    http://www.boost.org/libs/regex/doc/gcc-performance.html

    C++ Regular Expression Performance: GRETA and Boost.Regex
    http://research.microsoft.com/projects/greta/regex_perf.html

    Regular Expression Matching Can Be Simple And Fast (but is slow in Java, Perl, PHP, Python, Ruby, ...)
    http://swtch.com/~rsc/regexp/regexp1.html
*/
    // Alternation
    CASE(".*(?:green|blue|white|three two|two .+ ).*", "one two three four five six");

    // Russ Cox
    CASE("(a?){10}a{10}", "aaaaaaaaaa");

    // Look ahead
    CASE(".+(?=five).+", "one two three four five six");

    // John Maddock
    CASE("([0-9]{4}[- ]){3}[0-9]{3,4}", "1234-5678-1234-456");
    CASE("^([a-zA-Z0-9_\\-\\.]+)@(([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$",
            "john@johnmaddock.co.uk");
    CASE("^[-+]?[0-9]*\\.?[0-9]*$", "123");
    CASE("^[-+]?[0-9]*\\.?[0-9]*$", "+3.14159");


    qDebug() << "";
    stats(millisSumQRegExp, millisSumBoost);
}



void testExactMatchAnchorMode() {
    const QString threeLines("one\ntwo\nthree");
    const QStringList threeLineList = (QStringList() << "one\n" << "two\n" << "three");


    // Plain string
    const QRegexEngine line("^.+$");
    Q_ASSERT(!line.exactMatch(threeLines, QRegexEngineBase::AnchorWontMatch).isValid());
    Q_ASSERT(!line.exactMatch(threeLines, QRegexEngineBase::AnchorAtStartEnd).isValid());
    Q_ASSERT(!line.exactMatch(threeLines, QRegexEngineBase::AnchorAtEachLine).isValid());

    const QRegexEngine multiLine("^(?:.|\n)+$");
    Q_ASSERT(!multiLine.exactMatch(threeLines, QRegexEngineBase::AnchorWontMatch).isValid());
    Q_ASSERT(multiLine.exactMatch(threeLines, QRegexEngineBase::AnchorAtStartEnd).isValid());
    Q_ASSERT(multiLine.exactMatch(threeLines, QRegexEngineBase::AnchorAtEachLine).isValid());


    // Complex feeder
    const StringListRegexFeeder feeder(threeLineList);
    const QRegexFeedEngine<StringListRegexFeeder> feedLine("^.+$");
    Q_ASSERT(!feedLine.exactMatch(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorWontMatch).isValid());
    Q_ASSERT(!feedLine.exactMatch(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorAtStartEnd).isValid());
    Q_ASSERT(!feedLine.exactMatch(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorAtEachLine).isValid());


    qDebug() << "testExactMatchAnchorMode" << "PASSED";
}



void testFindFirst() {
    const QString pattern("B+");


    // Plain string
    const QRegexEngine b(pattern);
    Q_ASSERT(b.findFirst("aaaaaBBBBB").pos(0) == 5);
    Q_ASSERT(b.findFirst("aaaaaBBBBBcccccBBBBB").pos(0) == 5);
    Q_ASSERT(b.findFirst("BBBBBaaaaaBBBBB").pos(0) == 0);


    // Complex feeder
    QStringList textList;
    const StringListRegexFeeder feeder(textList);
    const QRegexFeedEngine<StringListRegexFeeder> c(pattern);

    textList.clear();
    textList << "aaaaaBBBBB";
    Q_ASSERT(c.findFirst(feeder.begin(), feeder.end()).pos(0) == 5);

    textList.clear();
    textList << "aaaaaBBBBBcccccBBBBB";
    Q_ASSERT(c.findFirst(feeder.begin(), feeder.end()).pos(0) == 5);

    textList.clear();
    textList << "BBBBBaaaaaBBBBB";
    Q_ASSERT(c.findFirst(feeder.begin(), feeder.end()).pos(0) == 0);


    qDebug() << "testFindFirst" << "PASSED";
}



void testFindLast() {
    const QString pattern("a+");


    // Plain string
    const QRegexEngine a(pattern);
    Q_ASSERT(a.findLast("aaaaaBBBBBaaaaa").pos(0) == 10);
    Q_ASSERT(a.findLast("aaaaaBBBBBaaaaaCCCCC").pos(0) == 10);
    Q_ASSERT(a.findLast("aaaaaBBBBBaaaaa", 0, -6).pos(0) == 0);


    // Complex feeder
    QStringList textList;
    const StringListRegexFeeder feeder(textList);
    const QRegexFeedEngine<StringListRegexFeeder> c(pattern);

    textList.clear();
    textList << "aaaaaBBBBBaaaaa";
    Q_ASSERT(c.findLast(feeder.begin(), feeder.end()).pos(0) == 10);

    textList.clear();
    textList << "aaaaaBBBBBaaaaaCCCCC";
    Q_ASSERT(c.findLast(feeder.begin(), feeder.end()).pos(0) == 10);

    textList.clear();
    textList << "aaaaaBBBBBaaaaa";
    Q_ASSERT(c.findLast(feeder.begin(), feeder.end() - 5).pos(0) == 0);


    qDebug() << "testFindLast" << "PASSED";
}



void testFindAllAnchorMode() {
    const QString threeLines("one\ntwo\nthree");
    const QStringList threeLineList = (QStringList() << "one\n" << "two\n" << "three");
    const QString line("^.+$");
    const QString multiLine("^(?:.|\n)+$");


    // Plain string
    const QRegexEngine a1(line);
    Q_ASSERT(a1.findAll(threeLines, 0, -1, QRegexEngineBase::AnchorWontMatch).count() == 0);
    Q_ASSERT(a1.findAll(threeLines, 0, -1, QRegexEngineBase::AnchorAtStartEnd).count() == 0);
    Q_ASSERT(a1.findAll(threeLines, 0, -1, QRegexEngineBase::AnchorAtEachLine).count() == 3);

    const QRegexEngine a2(multiLine);
    Q_ASSERT(a2.findAll(threeLines, 0, -1, QRegexEngineBase::AnchorWontMatch).count() == 0);
    Q_ASSERT(a2.findAll(threeLines, 0, -1, QRegexEngineBase::AnchorAtStartEnd).count() == 1);
    Q_ASSERT(a2.findAll(threeLines, 0, -1, QRegexEngineBase::AnchorAtEachLine).count() == 1);


    // Complex feeder
    const StringListRegexFeeder feeder(threeLineList);
    const QRegexFeedEngine<StringListRegexFeeder> b1(line);
    Q_ASSERT(b1.findAll(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorWontMatch).count() == 0);
    Q_ASSERT(b1.findAll(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorAtStartEnd).count() == 0);
    Q_ASSERT(b1.findAll(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorAtEachLine).count() == 3);

    const QRegexFeedEngine<StringListRegexFeeder> b2(multiLine);
    Q_ASSERT(b2.findAll(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorWontMatch).count() == 0);
    Q_ASSERT(b2.findAll(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorAtStartEnd).count() == 1);
    Q_ASSERT(b2.findAll(feeder.begin(), feeder.end(), QRegexEngineBase::AnchorAtEachLine).count() == 1);


    qDebug() << "testFindAllAnchorMode" << "PASSED";
}



void testOffset() {
    const QString fiveAfiveB("aaaaaBBBBB");
    const QStringList fiveAfiveBList = (QStringList() << "aaaaa" << "BBBBB");
    const QString a("a+");
    const QString b("B+");


    // Plain string
    const QRegexEngine s1(a);
    Q_ASSERT(s1.findFirst(fiveAfiveB, 4).isValid());
    Q_ASSERT(!s1.findFirst(fiveAfiveB, 5).isValid());

    const QRegexEngine s2(b);
    Q_ASSERT(s2.findFirst(fiveAfiveB, 0, -5).isValid());
    Q_ASSERT(!s2.findFirst(fiveAfiveB, 0, -6).isValid());
    Q_ASSERT(s2.findFirst(fiveAfiveB, 5, -5).isValid());


    // Complex feeder
    const StringListRegexFeeder feeder(fiveAfiveBList);
    const QRegexFeedEngine<StringListRegexFeeder> f1(a);
    Q_ASSERT(f1.findFirst(feeder.begin() + 4, feeder.end()).isValid());
    Q_ASSERT(!f1.findFirst(feeder.begin() + 5, feeder.end()).isValid());

    const QRegexFeedEngine<StringListRegexFeeder> f2(b);
    Q_ASSERT(f2.findFirst(feeder.begin(), feeder.end() - 4).isValid());
    Q_ASSERT(!f2.findFirst(feeder.begin(), feeder.end() - 5).isValid());
    Q_ASSERT(f2.findFirst(feeder.begin() + 5, feeder.end() - 4).isValid());


    qDebug() << "testOffset" << "PASSED";
}



int main() {
    // Blackbox tests
    testExactMatchAnchorMode();
    testFindFirst();
    testFindLast();
    testFindAllAnchorMode();
    testOffset();
    qDebug() << "";

    // Speed comparison
    runSpeedTestSuite();
    qDebug() << "";

    return 0;
}
