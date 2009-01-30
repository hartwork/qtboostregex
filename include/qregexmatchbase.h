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

#ifndef QREGEXMATCHBASE_H
#define QREGEXMATCHBASE_H



#include <QString>
#include <QStringList>
#include <boost/regex.hpp>



template <class feeder_type>
class QRegexMatchBase {

protected:
    boost::match_results<feeder_type> * m_details;
    
    int m_startOffset;

public:
    QRegexMatchBase();

    QRegexMatchBase(const QRegexMatchBase & other);

    virtual ~QRegexMatchBase();

    virtual QString cap(int nth = 0) const = 0;

    QStringList capturedTexts() const;

    int count() const;
    
    bool isValid() const;

    int length(int nth = 0) const;

    int pos(int nth = 0) const;
    
    QRegexMatchBase<feeder_type> & operator=(const QRegexMatchBase<feeder_type> & other);

public: // TODO hide in the API?
    void setDetails(boost::match_results<feeder_type> & details);

    void setStartOffset(int startOffset);

};



template <class feeder_type>
QRegexMatchBase<feeder_type>::QRegexMatchBase()
        : m_details(new boost::match_results<feeder_type>),
        m_startOffset(0) {
    // NOOP
}



template <class feeder_type>
QRegexMatchBase<feeder_type>::QRegexMatchBase(const QRegexMatchBase & other)
        : m_details(new boost::match_results<feeder_type>(*other.m_details)),
        m_startOffset(other.m_startOffset) {
    // NOOP
}



template <class feeder_type>
QRegexMatchBase<feeder_type>::~QRegexMatchBase() {
    delete m_details;
}



template <class feeder_type>
QStringList QRegexMatchBase<feeder_type>::capturedTexts() const {
    const int count = this->count();
    QStringList list;
    for(int i = 0; i < count; i++) {
        list.append(cap(i));
    }
    return list;
}



template <class feeder_type>
int QRegexMatchBase<feeder_type>::count() const {
    return static_cast<int>(m_details->size());
}



template <class feeder_type>
bool QRegexMatchBase<feeder_type>::isValid() const {
    return !m_details->empty();
}



template <class feeder_type>
int QRegexMatchBase<feeder_type>::length(int nth) const {
    if ((nth < 0) || (nth >= static_cast<int>(m_details->size()))) {
        // Capture index error
        return -1;
    }
    return m_details->length(nth);
}



template <class feeder_type>
int QRegexMatchBase<feeder_type>::pos(int nth) const {
    if ((nth < 0) || (nth >= static_cast<int>(m_details->size()))) {
        // Capture index error
        return -1;
    }
    return m_details->position(nth) + m_startOffset;
}



template <class feeder_type>
void QRegexMatchBase<feeder_type>::setDetails(boost::match_results<feeder_type> & details) {
    m_details->swap(details);
}



template <class feeder_type>
void QRegexMatchBase<feeder_type>::setStartOffset(int startOffset) {
    m_startOffset = startOffset;
}



template <class feeder_type>
QRegexMatchBase<feeder_type> & QRegexMatchBase<feeder_type>::operator=(const QRegexMatchBase<feeder_type> & other) {
    if (&other != this) {
        delete m_details;
        m_details = new boost::match_results<feeder_type>(*other.m_details);
        m_startOffset = other.m_startOffset;
    }

    return *this;
}



#endif // QREGEXMATCHBASE_H

