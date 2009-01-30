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

#include "qregexengine.h"

#include "qregexmatch.h"
#include <QString>

#include "qregexmatch.h"
#include "ushorttraits.h"
#include <boost/regex.hpp>
#include <QDebug>



QRegexEngine::QRegexEngine(const QString & pattern, Qt::CaseSensitivity cs)
        : QRegexEngineBase(pattern, cs) {
    // NOOP
}



QRegexMatch QRegexEngine::exactMatch(const QString & input, QRegexEngineBase::AnchorMode anchorMode) const {
    const bool EXACT = true;
    return getMatch(input, 0, -1, anchorMode, EXACT);
}



QRegexMatch QRegexEngine::findFirst(const QString & input, int startOffset, int endOffset,
            QRegexEngineBase::AnchorMode anchorMode) const {
    const bool NOT_EXACT = false;
    return getMatch(input, startOffset, endOffset, anchorMode, NOT_EXACT);
}



QRegexMatch QRegexEngine::findLast(const QString & input, int startOffset, int endOffset,
            QRegexEngineBase::AnchorMode anchorMode) const {
    const bool LAST_ONLY = true;
    QList<QRegexMatch> lastMatch = collectMatches(input, startOffset, endOffset, anchorMode, LAST_ONLY);
    return lastMatch.isEmpty() ? QRegexMatch(input) : lastMatch.at(0);
}



QList<QRegexMatch> QRegexEngine::findAll(const QString & input, int startOffset, int endOffset,
            QRegexEngineBase::AnchorMode anchorMode) const {
    const bool ALL = false;
    QList<QRegexMatch> allMatches = collectMatches(input, startOffset, endOffset, anchorMode, ALL);
    return allMatches;
}



QRegexMatch QRegexEngine::getMatch(const QString & input, int startOffset, int endOffset,
        QRegexEngineBase::AnchorMode anchorMode, bool exact) const {
    Q_ASSERT(m_regex != NULL);
    QRegexMatch match(input);
    if (!isValid()) {
        return match;
    }

    const ushort * const head = reinterpret_cast<const ushort *>(input.constData());
    Q_ASSERT(head != NULL);
    const ushort * const first = head + startOffset;
    const ushort * const afterLast = head + input.count() + endOffset + 1;
    Q_ASSERT(first <= afterLast);
    boost::match_results<const ushort *, std::allocator<boost::sub_match<const ushort *> > > results;
    const boost::match_flag_type flags = QRegexEngineBase::combineMatchFlags(
            QRegexEngineBase::defaultMatchFlags(), anchorMode);

    bool success = false;
    if (exact) {
        success = boost::regex_match(first, afterLast, results, *m_regex, flags);
    } else {
        success = boost::regex_search(first, afterLast, results, *m_regex, flags);
    }
    
    if (success) {
        match.setDetails(results);
        match.setStartOffset(startOffset);
    }
    
    return match;
}



QList<QRegexMatch> QRegexEngine::collectMatches(const QString & input, int startOffset, int endOffset,
        QRegexEngineBase::AnchorMode anchorMode, bool onlyLast) const {
    const int inputLen = input.count();
    QList<QRegexMatch> collection;

    if ((startOffset < 0) || (startOffset >= inputLen)
            || (endOffset < -inputLen) || (endOffset >= 0)) {
        // Error
        return collection;
    }

    QRegexMatch prevMatch(input);
    int prevPos = startOffset;
    int prevLen = 0;
    for (;;) {
        QRegexMatch match = findFirst(input, prevPos + prevLen, endOffset, anchorMode);
        if (!match.isValid()) {
            // No more matches
            break;
        }

        // Valid match, but maybe not the last one
        if (onlyLast) {
            prevMatch = match;
        } else {
            collection.append(match);
        }
        const int pos = match.pos(0);
        const int len = match.length(0);
        prevPos = pos;
        prevLen = (len == 0) ? 1 : len; // NOTE: To prevent endless loops
		
        if (prevPos + prevLen >= inputLen + endOffset + 1) {
            // No more matches
            break;
        }
    }

    if (onlyLast) {
        collection.append(prevMatch);
    }

    return collection;
}
