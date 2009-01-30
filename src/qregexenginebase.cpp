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

#include "qregexenginebase.h"

#include "ushorttraits.h"
#include <QDebug>



QRegexEngineBase::QRegexEngineBase(const QString & pattern, Qt::CaseSensitivity cs)
        : m_regex(new boost::basic_regex<ushort, UshortTraits>(
                reinterpret_cast<const ushort *>(pattern.constData()),
                combineSyntaxFlags(defaultSyntaxFlags(), cs))) {
    // NOOP
}



QRegexEngineBase::~QRegexEngineBase() {
    delete m_regex;
}



Qt::CaseSensitivity QRegexEngineBase::caseSensitivity() const {
    Q_ASSERT(m_regex != NULL);
    return isSet(m_regex->flags(), boost::regex::icase) ? Qt::CaseSensitive : Qt::CaseInsensitive;
}



bool QRegexEngineBase::isValid() const {
    Q_ASSERT(m_regex != NULL);
    return m_regex->status() == 0;
}



int QRegexEngineBase::numCaptures() const {
    if (!isValid()) {
        return 0;
    }

    Q_ASSERT(m_regex != NULL);
    return static_cast<int>(m_regex->mark_count());
}



QString QRegexEngineBase::pattern() const {
    const std::basic_string<ushort> text = m_regex->str();
    const ushort * const utf16 = text.data();
    Q_ASSERT(utf16 != NULL);
    const int len = text.size();
    return QString::fromUtf16(static_cast<const ushort *>(utf16), len);
}



void QRegexEngineBase::setCaseSensitivity(Qt::CaseSensitivity cs) {
    if (caseSensitivity() == cs) {
        return;
    }

    Q_ASSERT(m_regex != NULL);

    // Get current settings
    const std::basic_string<ushort> pattern = m_regex->str();
    const boost::basic_regex<ushort, UshortTraits>::flag_type flags
            = combineSyntaxFlags(m_regex->flags(), cs);

    // Create new regex object
    delete m_regex;
    m_regex = new boost::basic_regex<ushort, UshortTraits>(pattern, flags);
}



void QRegexEngineBase::setPattern(const QString & pattern) {
    Q_ASSERT(m_regex != NULL);

    // Get current settings (flags only)
    const boost::basic_regex<ushort, UshortTraits>::flag_type flags = m_regex->flags();

    // Create new regex object
    delete m_regex;
    m_regex = new boost::basic_regex<ushort, UshortTraits>(
            reinterpret_cast<const ushort *>(pattern.constData()),
            flags);
}



inline void QRegexEngineBase::set(boost::regex_constants::match_flag_type & flags,
        boost::regex_constants::match_flag_type enabled) const {
    if ((flags & enabled) != enabled) {
        flags |= enabled;
    }
}



inline void QRegexEngineBase::unset(boost::regex_constants::match_flag_type & flags,
        boost::regex_constants::match_flag_type disabled) const {
    if ((flags & disabled) == disabled) {
        flags &= ~disabled;
    }
}



/*static*/ inline void QRegexEngineBase::set(boost::regex_constants::syntax_option_type & flags,
        boost::regex_constants::syntax_option_type enabled) {
    if ((flags & enabled) != enabled) {
        flags |= enabled;
    }
}



/*static*/ inline void QRegexEngineBase::unset(boost::regex_constants::syntax_option_type & flags,
        boost::regex_constants::syntax_option_type disabled) {
    if ((flags & disabled) == disabled) {
        flags &= ~disabled;
    }
}



/*static*/ bool QRegexEngineBase::isSet(boost::regex_constants::syntax_option_type flags,
            boost::regex_constants::syntax_option_type check) {
    return ((flags & check) == check);
}



boost::regex_constants::match_flag_type QRegexEngineBase::combineMatchFlags(
        boost::regex_constants::match_flag_type flags,
        AnchorMode anchorMode) const {
    switch (anchorMode) {
    case AnchorWontMatch:
        set(flags, boost::regex_constants::match_not_bol);
        set(flags, boost::regex_constants::match_not_eol);
        set(flags, boost::regex_constants::match_single_line);
        break;
        
    case AnchorAtEachLine:
        unset(flags, boost::regex_constants::match_not_bol);
        unset(flags, boost::regex_constants::match_not_eol);
        unset(flags, boost::regex_constants::match_single_line);
        break;
        
    case AnchorAtStartEnd: // FALLTHROUGH
    default:
        unset(flags, boost::regex_constants::match_not_bol);
        unset(flags, boost::regex_constants::match_not_eol);
        set(flags, boost::regex_constants::match_single_line);

    }
        
    return flags;
}



boost::regex_constants::match_flag_type QRegexEngineBase::defaultMatchFlags() const {
    return boost::regex_constants::match_default
    // Specifies that if more than one match is possible then any match is an acceptable result.
//            | boost::regex_constants::match_any

    // Equivalent to the inverse of Perl's m/ modifier;
            | boost::regex_constants::match_single_line 

    // Specifies that the expression "." does not match a newline character.
            | boost::regex_constants::match_not_dot_newline 

    // Specified that the expression "." does not match a character null '\0'.
            | boost::regex_constants::match_not_dot_null
            ;
}



/*static*/ inline boost::regex_constants::syntax_option_type QRegexEngineBase::combineSyntaxFlags(
        boost::regex_constants::syntax_option_type flags,
        Qt::CaseSensitivity cs) {
    switch (cs) {
    case Qt::CaseInsensitive:
        set(flags, boost::regex::icase);
        break;
        
    case Qt::CaseSensitive: // FALLTHROUGH
    default:
        unset(flags, boost::regex::icase);
    
    }
    
    return flags;
}


        
/*static*/ inline boost::regex_constants::syntax_option_type QRegexEngineBase::defaultSyntaxFlags() {
    return 0
    // Perl flavor
            | boost::regex::perl

    // Don't throw exception for invalid pattern
            | boost::regex::no_except  

    // Trade regex oject creattion speed for matching speed
//            | boost::regex::optimize

    // Specifies that character ranges of the form [a-b] should be locale sensitive.
//            | boost::regex::collate
            ;
}

