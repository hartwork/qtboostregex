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

#ifndef QREGEXENGINEBASE_H
#define QREGEXENGINEBASE_H



#include <QString>



class UshortTraits;

namespace boost {
    template <class charT, class traits>
    class basic_regex;
}



#include <boost/regex.hpp> // TODO move to private header



class QRegexEngineBase {

public:
    enum AnchorMode {
        AnchorWontMatch,
        AnchorAtStartEnd,
        AnchorAtEachLine
    };

protected:
    boost::basic_regex<ushort, UshortTraits> * m_regex;

protected:
    QRegexEngineBase(const QString & pattern, Qt::CaseSensitivity cs);
    
    // TODO copycon, assop

public:
    virtual ~QRegexEngineBase();

    Qt::CaseSensitivity caseSensitivity() const;

    bool isValid() const;

    int numCaptures() const;

    QString pattern() const;

    void setCaseSensitivity(Qt::CaseSensitivity cs);

    void setPattern(const QString & pattern);

private:
    void set(boost::regex_constants::match_flag_type & flags, boost::regex_constants::match_flag_type enabled) const;

    void unset(boost::regex_constants::match_flag_type & flags, boost::regex_constants::match_flag_type disabled) const;

    static void set(boost::regex_constants::syntax_option_type & flags,
            boost::regex_constants::syntax_option_type enabled);

    static void unset(boost::regex_constants::syntax_option_type & flags,
            boost::regex_constants::syntax_option_type disabled);

    static bool isSet(boost::regex_constants::syntax_option_type flags,
            boost::regex_constants::syntax_option_type check);

protected:
    boost::regex_constants::match_flag_type combineMatchFlags(boost::regex_constants::match_flag_type flags,
            AnchorMode anchorMode) const;
            
    boost::regex_constants::match_flag_type defaultMatchFlags() const;

private:
    static boost::regex_constants::syntax_option_type combineSyntaxFlags(
            boost::regex_constants::syntax_option_type flags,
            Qt::CaseSensitivity cs);
            
    static boost::regex_constants::syntax_option_type defaultSyntaxFlags();

};



#endif // QREGEXENGINEBASE_H

