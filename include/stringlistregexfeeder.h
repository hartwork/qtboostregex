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

#ifndef STRINGLISTREGEXFEEDER_H
#define STRINGLISTREGEXFEEDER_H



#include "qglobal.h" // ushort



class QStringList;
namespace std {
    class forward_iterator_tag;
};



class StringListRegexFeeder {

public:
    typedef ushort char_type;

    typedef ushort value_type;

    typedef int difference_type;

    typedef const value_type* pointer;

    typedef const value_type& reference;

    typedef std::forward_iterator_tag iterator_category;

private:
    const QStringList * m_lines;
    
    int m_row;
    
    int m_column;

public:
    StringListRegexFeeder(const QStringList & lines, int row = 0, int column = 0);

public: // Bidirectional Iterator stuff
    StringListRegexFeeder();

    StringListRegexFeeder(const StringListRegexFeeder & other);

    StringListRegexFeeder & operator=(const StringListRegexFeeder & other);
     
    bool operator==(const StringListRegexFeeder & other) const;

    bool operator!=(const StringListRegexFeeder & other) const;

    const ushort & operator*() const;

    ushort & operator*();

    StringListRegexFeeder & operator++(); // prefix

    StringListRegexFeeder & operator++(int); // postfix

    StringListRegexFeeder & operator--(); // prefix

    StringListRegexFeeder & operator--(int); // postfix

    StringListRegexFeeder operator+(int operand);

    StringListRegexFeeder operator-(int operand);

    StringListRegexFeeder & operator+=(int operand);

    StringListRegexFeeder & operator-=(int operand);

    bool operator>=(const StringListRegexFeeder & other);

public:
    StringListRegexFeeder begin() const;

    StringListRegexFeeder end() const;

private:
    const ushort & deref() const;

};



#endif // STRINGLISTREGEXFEEDER_H

