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

#ifndef QREGEXFEEDENGINE_H
#define QREGEXFEEDENGINE_H



#include "qregexenginebase.h"
#include "ushorttraits.h"
#include "qregexfeedmatch.h"



template <class feeder_type>
class QRegexFeedEngine : public QRegexEngineBase {

public:
    QRegexFeedEngine(const QString & pattern, Qt::CaseSensitivity cs = Qt::CaseSensitive);

    QRegexFeedMatch<feeder_type> exactMatch(feeder_type begin, feeder_type end,
            AnchorMode anchorMode = AnchorAtStartEnd) const;

    QRegexFeedMatch<feeder_type> findFirst(feeder_type begin, feeder_type end,
            AnchorMode anchorMode = AnchorAtStartEnd) const;

    QRegexFeedMatch<feeder_type> findLast(feeder_type begin, feeder_type end,
            AnchorMode anchorMode = AnchorAtStartEnd) const;

    QList<QRegexFeedMatch<feeder_type> > findAll(feeder_type begin, feeder_type end,
            AnchorMode anchorMode = AnchorAtStartEnd) const;

private:
    QRegexFeedMatch<feeder_type> getMatch(feeder_type begin, feeder_type end,
            AnchorMode anchorMode,
            bool exact) const;

    QList<QRegexFeedMatch<feeder_type> > collectMatches(feeder_type begin, feeder_type end,
            AnchorMode anchorMode, bool onlyLast) const;

};



template <class feeder_type>
QRegexFeedEngine<feeder_type>::QRegexFeedEngine(const QString & pattern, Qt::CaseSensitivity cs)
        : QRegexEngineBase(pattern, cs) {
    // NOOP
}



template <class feeder_type>
QRegexFeedMatch<feeder_type> QRegexFeedEngine<feeder_type>::exactMatch(feeder_type begin, feeder_type end,
        QRegexEngineBase::AnchorMode anchorMode) const {
    const bool EXACT = true;
    return getMatch(begin, end, anchorMode, EXACT);
}



template <class feeder_type>
QRegexFeedMatch<feeder_type> QRegexFeedEngine<feeder_type>::findFirst(feeder_type begin, feeder_type end,
        QRegexEngineBase::AnchorMode anchorMode) const {
    const bool NOT_EXACT = false;
    return getMatch(begin, end, anchorMode, NOT_EXACT);
}



template <class feeder_type>
QRegexFeedMatch<feeder_type> QRegexFeedEngine<feeder_type>::findLast(feeder_type begin, feeder_type end,
        QRegexEngineBase::AnchorMode anchorMode) const {
    const bool LAST_ONLY = true;
    QList<QRegexFeedMatch<feeder_type> > lastMatch = collectMatches(begin, end, anchorMode, LAST_ONLY);
    return lastMatch.isEmpty() ? QRegexFeedMatch<feeder_type>() : lastMatch.at(0);
}



template <class feeder_type>
QList<QRegexFeedMatch<feeder_type> > QRegexFeedEngine<feeder_type>::findAll(feeder_type begin, feeder_type end,
        QRegexEngineBase::AnchorMode anchorMode) const {
    const bool ALL = false;
    QList<QRegexFeedMatch<feeder_type> > allMatches = collectMatches(begin, end, anchorMode, ALL);
    return allMatches;
}



template <class feeder_type>
QRegexFeedMatch<feeder_type> QRegexFeedEngine<feeder_type>::getMatch(feeder_type begin, feeder_type end,
        QRegexEngineBase::AnchorMode anchorMode, bool exact) const {
    Q_ASSERT(m_regex != NULL);

    QRegexFeedMatch<feeder_type> match;
    if (!isValid()) {
        return match;
    }

    boost::match_results<feeder_type> results;
    const boost::match_flag_type flags = QRegexEngineBase::combineMatchFlags(
            QRegexEngineBase::defaultMatchFlags(), anchorMode);
    
    bool success = false;
    if (exact) {
        success = boost::regex_match<feeder_type, std::allocator<boost::sub_match<feeder_type> >,
                ushort, UshortTraits >(begin, end, results, *m_regex, flags);
    } else {
        success = boost::regex_search<feeder_type, std::allocator<boost::sub_match<feeder_type> >,
                ushort, UshortTraits >(begin, end, results, *m_regex, flags);
    }

    if (success) {
        match.setDetails(results);
    }

    return match;
}



template <class feeder_type>
QList<QRegexFeedMatch<feeder_type> > QRegexFeedEngine<feeder_type>::collectMatches(
        feeder_type begin, feeder_type end,
        QRegexEngineBase::AnchorMode anchorMode,
        bool onlyLast) const {
    QList<QRegexFeedMatch<feeder_type> > collection;
    QRegexFeedMatch<feeder_type> prevMatch;
    feeder_type afterPrevFeeder = begin;
    int afterPrevPos = 0;
    for (;;) {
        QRegexFeedMatch<feeder_type> match = findFirst(afterPrevFeeder, end, anchorMode);
        if (!match.isValid()) {
            // No more matches
            break;
        }
        match.setStartOffset(afterPrevPos);

        // Valid match, but maybe not the last one
        if (onlyLast) {
            prevMatch = match;
        } else {
    	 collection.append(match);
        }
        const int pos = match.pos(0);
        const int lenCandidate = match.length(0);
        const int len = (lenCandidate == 0) ? 1 : lenCandidate; // NOTE: To prevent endless loops
        const int advance = (pos - afterPrevPos) + len;
        afterPrevFeeder += advance;
        
        if (afterPrevFeeder >= end) {
            // No more matches
            break;
        }

        afterPrevPos += advance;
    }

    if (onlyLast) {
        collection.append(prevMatch);
    }
    return collection;
}



#endif // QREGEXFEEDENGINE_H

