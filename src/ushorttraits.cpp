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

#include "ushorttraits.h"
#include <QDebug>
#include <string>



/*static*/ inline UshortTraits::string_type UshortTraits::wchartToUshort(std::basic_string<wchar_t> input) {
    // TODO avoid this on Windows
    const wchar_t * const source = input.data();
    const int count = static_cast<int>(input.length());

    ushort * const dest = new ushort[count];
    for (int i = 0; i < count; i++) {
        dest[i] = static_cast<ushort>(source[i]);
    }
    
    UshortTraits::string_type res(dest, input.length());
    delete [] dest;
    return res;
}



/*static*/ inline void UshortTraits::ushortToWchart(wchar_t * & w1, wchar_t * & w2, const ushort * u1, const ushort * u2) {
    // TODO avoid this on Windows
    Q_ASSERT(u1 != NULL);
    Q_ASSERT(u2 != NULL);
    Q_ASSERT(u2 > u1);
    const int count = u2 - u1;
    w1 = new wchar_t[count];
    for (int i = 0; i < count; i++) {
        w1[i] = static_cast<wchar_t>(u1[i]);
    }
    w2 = w1 + count;
}



/*static*/ UshortTraits::size_type UshortTraits::length(const ushort * p) {
    if (p == NULL) {
        return 0;
    }
    const ushort * walker = p;
    while (*walker != ushort(0)) {
        walker++;
    }
    return walker - p;
}



// translate equivalence classes to representing
ushort UshortTraits::translate(const ushort c) const {
    // qDebug() << "translate";
    return m_traits.translate(c);
}

// translate equivalence classes to representing, also ignoreing case
ushort UshortTraits::translate_nocase(const ushort c) const {
    // qDebug() << "translate_nocase";
    return m_traits.translate_nocase(c);
}



UshortTraits::string_type UshortTraits::transform(const ushort * f1, const ushort * f2) const {
    qDebug() << "transform";
    wchar_t * w1;
    wchar_t * w2;
    UshortTraits::ushortToWchart(w1, w2, f1, f2);
    const UshortTraits::string_type res = UshortTraits::wchartToUshort(m_traits.transform(w1, w2));
    delete [] w1;
    return res;
}



UshortTraits::string_type UshortTraits::transform_primary(const ushort * f1, const ushort * f2) const {
    qDebug() << "transform_primary";
    wchar_t * w1;
    wchar_t * w2;
    UshortTraits::ushortToWchart(w1, w2, f1, f2);
    const UshortTraits::string_type res = UshortTraits::wchartToUshort(m_traits.transform_primary(w1, w2));
    delete [] w1;
    return res;
}



UshortTraits::char_class_type UshortTraits::lookup_classname(const ushort * f1, const ushort * f2) const {
    // qDebug() << "lookup_classname";
    wchar_t * w1;
    wchar_t * w2;
    UshortTraits::ushortToWchart(w1, w2, f1, f2);
    const UshortTraits::char_class_type res = m_traits.lookup_classname(w1, w2);
    delete [] w1;
    return res;
}



UshortTraits::string_type UshortTraits::lookup_collatename(const ushort * f1, const ushort * f2) const {
    qDebug() << "lookup_collatename";
    wchar_t * w1;
    wchar_t * w2;
    UshortTraits::ushortToWchart(w1, w2, f1, f2);
    const UshortTraits::string_type res = UshortTraits::wchartToUshort(m_traits.lookup_collatename(w1, w2));
    delete [] w1;
    return res;
}



bool UshortTraits::isctype(const ushort c, int i) const {
    // qDebug() << "isctype";
    return m_traits.isctype(c, i);
}



int UshortTraits::value(const ushort c, int i) const {
    // qDebug() << "value";
    return m_traits.value(c, i);
}



UshortTraits::locale_type UshortTraits::imbue(UshortTraits::locale_type loc) {
    // qDebug() << "imbue";
    return m_traits.imbue(loc);
}



UshortTraits::locale_type UshortTraits::getloc() const {
    // qDebug() << "getloc";
    return m_traits.getloc();
}



std::string UshortTraits::error_string(boost::regex_constants::error_type n) const {
    // qDebug() << "error_string";
    return m_traits.error_string(n);
}
