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

#include "qregexmatch.h"
#include <boost/regex.hpp>



QRegexMatch::QRegexMatch(const QString input)
        : m_input(input) {
    // NOOP
}



QRegexMatch::QRegexMatch(const QRegexMatch & other)
        : QRegexMatchBase<const ushort *>(other),
        m_input(other.m_input) {
    // NOOP
}



QString QRegexMatch::cap(int nth) const {
    if ((nth < 0) || (nth >= static_cast<int>(m_details->size()))) {
        // Capture index error
        return QString();
    }

    // Optimization for strings that is npt possible for usual feeder
    const int pos = m_details->position(nth);
    const int len = m_details->length(nth);
    const ushort * const head = m_input.utf16();
    Q_ASSERT(head != NULL);
    Q_ASSERT(pos + len <= m_input.count());
    return QString::fromUtf16(head + pos, len);
}



QRegexMatch & QRegexMatch::operator=(const QRegexMatch & other) {
    if (&other != this) {
        QRegexMatchBase<const ushort *>::operator=(other);
        m_input = other.m_input;
    }

    return *this;
}

