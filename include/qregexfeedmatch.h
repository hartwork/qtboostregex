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

#ifndef QREGEXFEEDMATCH_H
#define QREGEXFEEDMATCH_H



#include "qregexmatchbase.h"



template <class feeder_type>
class QRegexFeedMatch : public QRegexMatchBase<feeder_type> {

public:
    QString cap(int nth) const;

};



template <class feeder_type>
QString QRegexFeedMatch<feeder_type>::cap(int nth) const {
    if ((nth < 0) || (nth >= static_cast<int>(this->m_details->size()))) { // NOTE: "this->" is essential here!
        // Capture index error
        return QString();
    }

    QString output;
    const std::basic_string<ushort> text = this->m_details->str(nth); // NOTE: "this->" is essential here!
    const ushort * const utf16 = text.data();
    Q_ASSERT(utf16 != NULL);
    const int len = text.size();
    return QString::fromUtf16(static_cast<const ushort *>(utf16), len);
}



#endif // QREGEXFEEDMATCH_H

