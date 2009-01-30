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

#ifndef QREGEXENGINE_H
#define QREGEXENGINE_H



#include "qregexenginebase.h"
#include <QList>



class QRegexMatch;



class QRegexEngine : public QRegexEngineBase {

public:
    QRegexEngine(const QString & pattern, Qt::CaseSensitivity cs = Qt::CaseSensitive);

    QRegexMatch exactMatch(const QString & input, AnchorMode anchorMode = AnchorAtStartEnd) const;

    QRegexMatch findFirst(const QString & input, int startOffset = 0, int endOffset = -1,
            AnchorMode anchorMode = AnchorAtStartEnd) const;

    QRegexMatch findLast(const QString & input, int startOffset = 0, int endOffset = -1,
            AnchorMode anchorMode = AnchorAtStartEnd) const;
            
    QList<QRegexMatch> findAll(const QString & input, int startOffset = 0, int endOffset = -1,
            AnchorMode anchorMode = AnchorAtStartEnd) const;
            
private:
    QRegexMatch getMatch(const QString & input, int startOffset, int endOffset,
            AnchorMode anchorMode, bool exact) const;
            
    QList<QRegexMatch> collectMatches(const QString & input, int startOffset, int endOffset,
            AnchorMode anchorMode, bool onlyLast) const;

};



#endif // QREGEXENGINE_H

