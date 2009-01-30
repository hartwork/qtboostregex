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

#ifndef QREGEXMATCH_H
#define QREGEXMATCH_H



#include "qregexmatchbase.h"

#include <QString>



class QRegexMatch : public QRegexMatchBase<const ushort *> {

    QString m_input;

public:
    QRegexMatch(const QString input);
    
    QRegexMatch(const QRegexMatch & other);

    QString cap(int nth = 0) const;
    
    QRegexMatch & operator=(const QRegexMatch & other);

};



#endif // QREGEXMATCH_H

