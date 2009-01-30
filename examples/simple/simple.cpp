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

#include <qregexengine.h>
#include <qregexmatch.h>
#include <qregexfeedengine.h>
#include <qregexfeedmatch.h>
#include <stringlistregexfeeder.h>
#include <QDebug>

int main()
{
    QStringList list;
    list << QString("hello");
    list << QString("happy");
    list << QString("world");
    StringListRegexFeeder feeder(list);


    // Plain string
    QRegexEngine engineOne("(h[a-z]+){2}");
    QRegexMatch matchOne = engineOne.exactMatch(list.join(""));
    for (int j = 0; j < matchOne.count(); j++) {
        qDebug() << "[" << j << "]" << matchOne.cap(j);
    }
    qDebug() << "";


    // Complex feeder
    QRegexFeedEngine<StringListRegexFeeder> engineTwo("(h[a-z]+){2}");
    QRegexFeedMatch<StringListRegexFeeder> matchTwo = engineTwo.exactMatch(feeder.begin(), feeder.end());
    for (int i = 0; i < matchTwo.count(); i++) {
        qDebug() << "[" << i << "]" << matchTwo.cap(i);
    }
    qDebug() << "";

    return 0;
}
