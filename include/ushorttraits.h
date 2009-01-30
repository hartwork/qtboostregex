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

#ifndef USHORTTRAITS_P_H
#define USHORTTRAITS_P_H



#include <QtCore/QtGlobal>
#include <string>
#include <boost/regex.hpp>


#define BOOST_REGEX_HAS_OTHER_WCHAR_T


class UshortTraits {

public:
// The character container type used in the implementation of class template basic_regex.
typedef ushort char_type;

// An unsigned integer type, capable of holding the length of a null-terminated string of charT's.
typedef int size_type;

typedef std::basic_string<ushort> string_type;

// A copy constructible type that represents the locale used by the traits class.
typedef boost::cpp_regex_traits<wchar_t>::locale_type locale_type;

// Implementation defined
// A bitmask type representing a particular character classification. Multiple values
// of this type can be bitwise-or'ed together to obtain a new valid value.
typedef boost::cpp_regex_traits<wchar_t>::char_class_type char_class_type; 

private:
    boost::cpp_regex_traits<wchar_t> m_traits;

public:
// Yields the smallest i such that const ushort * p[i] == 0. Complexity is linear in i.
static size_type length(const ushort * p);
                                                   
// Returns a character such that for any character d that is to be considered
// equivalent to const ushort c then v.translate(const ushort c) == v.translate(d).
char_type translate(const ushort c) const;

// For all characters const ushort c that are to be considered equivalent to const
// ushort c when comparisons are to be performed without regard to case, then
// v.translate_nocase(const ushort c) == v.translate_nocase(const ushort c).
char_type translate_nocase(const ushort c) const;

// Returns a sort key for the character sequence designated by the iterator range
// [const ushort * f1, const ushort * f2) such that if the character sequence [G1, G2)
// sorts before the character sequence [H1, H2) then v.transform(G1, G2) < v.transform(H1, H2).
string_type transform(const ushort * f1, const ushort * f2) const;

//  Returns a sort key for the character sequence designated by the iterator range
// [const ushort * f1, const ushort * f2) such that if the character sequence [G1, G2)
// sorts before the character sequence [H1, H2) when character case is not considered then
// v.trans-form_primary(G1, G2) < v.transform_primary(H1, H2).
string_type transform_primary(const ushort * f1, const ushort * f2) const;

// Converts the character sequence designated by the iterator range
// [const ushort * f1,const ushort * f2) const; into a bitmask type that can subsequently
// be passed to isctype. Values returned from lookup_classname can be safely bitwise or'ed
// together. Returns 0 if the character sequence is not the name of a character class
// recognized by X. The value returned shall be independent of the case of the characters
// in the sequence.
char_class_type lookup_classname(const ushort * f1, const ushort * f2) const;

// Returns a sequence of characters that represents the collating element consisting
// of the character sequence designated by the iterator range [const ushort * f1,
// const ushort * f2) const;. Returns an empty string if the character sequence is
// not a valid collating element.
string_type lookup_collatename(const ushort * f1, const ushort * f2) const;
                                            
// Returns true if character const ushort c is a member of the character class designated by
// the iterator range [const ushort * f1, const ushort * f2), false otherwise.
bool isctype(const ushort c, int i) const;

// Returns the value represented by the digit const ushort c in base I if the character const
// valid digit in base I; otherwise returns -1. [Note: the value of I will only be ushort c is a
// 8, 10, or 16. -end note]
int value(const ushort c, int i) const;
                                            
// Imbues u with the locale loc, returns the previous locale used by u if any.
locale_type imbue(locale_type loc);

// Returns the current locale used by v if any.
locale_type getloc() const;

// Returns a human readable error string for the error condition i, where i is one
// of the values enumerated by type regex_constants::error_type.
// If the value i is not recognized then returns the string "Unknown error" or a localized
// equivalent.
std::string error_string(boost::regex_constants::error_type n) const;

private:
    static string_type wchartToUshort(std::basic_string<wchar_t> input);

    static void ushortToWchart(wchar_t * & w1, wchar_t * & w2, const ushort * u1, const ushort * u2);

};



#endif // USHORTTRAITS_P_H

