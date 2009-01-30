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

#include "stringlistregexfeeder.h"
#include <QStringList>



StringListRegexFeeder::StringListRegexFeeder()
        : m_row(0),
        m_column(0) {
    // NOOP
}



StringListRegexFeeder::StringListRegexFeeder(const QStringList & lines, int row, int column)
        : m_lines(&lines),
        m_row(row),
        m_column(column) {
    // NOOP
}



StringListRegexFeeder::StringListRegexFeeder(const StringListRegexFeeder & other)
        : m_lines(other.m_lines),
        m_row(other.m_row),
        m_column(other.m_column) {
    // NOOP
}



StringListRegexFeeder & StringListRegexFeeder::operator=(const StringListRegexFeeder & other) {
    if (&other != this) {
        m_lines = other.m_lines;
        m_row = other.m_row;
        m_column = other.m_column;
    }
    return *this;
}



bool StringListRegexFeeder::operator==(const StringListRegexFeeder & other) const {
/*
qDebug() << "this " << m_row << "x" << m_column << " / "
        << "other " << other.m_row << "x" << other.m_column << endl;

qDebug() << "==" << endl;
*/
    return !operator!=(other);
}



bool StringListRegexFeeder::operator!=(const StringListRegexFeeder & other) const {
/*
qDebug() << "this " << m_row << "x" << m_column << " / "
        << "other " << other.m_row << "x" << other.m_column << endl;
*/
    if (&other == this) {
// qDebug() << "A equal" << endl;
        return false;
    } else if ((other.m_row != m_row)
            || (other.m_column != m_column)) {
// qDebug() << "B unequal" << endl;
        return true;
    }
    
    const int countOther = other.m_lines->count();
    const int countThis = m_lines->count();
    if (countOther != countThis) {
// qDebug() << "C unequal" << endl;
        return true;
    }
    
    for (int i = 0; i < countThis; i++) {
        if (other.m_lines[i] != m_lines[i]) {
// qDebug() << "D unequal" << endl;
            return true;
        }
    }
    
// qDebug() << "E equal" << endl;
    return false;
}



const ushort & StringListRegexFeeder::operator*() const {
// qDebug() << "sdsd 1" << endl;
    return deref();
}



ushort & StringListRegexFeeder::operator*() {
// qDebug() << "sdsd 2" << endl;
    return const_cast<ushort &>(deref());
}



StringListRegexFeeder & StringListRegexFeeder::operator++() { // prefix ++a
// qDebug() << "X++" << endl;
    if (m_row >= m_lines->count()) {
        // Move to end
        m_row = m_lines->count();
        m_column = 0;
    } else if (m_column < (*m_lines)[m_row].count() - 1) {
        m_column++;
    } else if (m_row < m_lines->count()) {
        m_column = 0;
        m_row++;
    } else {
        // Move to end
        m_row = m_lines->count();
        m_column = 0;
    }
// qDebug() << "NOW " << m_row << "x" << m_column << endl;
    return *this;
}



StringListRegexFeeder & StringListRegexFeeder::operator++(int) { // postfix a++
    StringListRegexFeeder * const backup = new StringListRegexFeeder(*this);
// qDebug() << "++X" << endl;
    if (m_row >= m_lines->count()) {
        // Move to end
        m_row = m_lines->count();
        m_column = 0;
    } else if (m_column < (*m_lines)[m_row].count() - 1) {
        m_column++;
    } else if (m_row < m_lines->count()) {
        m_column = 0;
        m_row++;
    } else {
        // Move to end
        m_row = m_lines->count();
        m_column = 0;
    }
// qDebug() << "NOW " << m_row << "x" << m_column << endl;
    return *backup; // TODO free?
}



StringListRegexFeeder & StringListRegexFeeder::operator--() { // prefix --a
// qDebug() << "X--" << endl;
    if (m_column > 0) {
        m_column--;
    } else if (m_row > 0) {
        m_row--;
        m_column = (*m_lines)[m_row].count() - 1;
    } else {
        // Move to start
        m_row = 0;
        m_column = 0;
    }
// qDebug() << "NOW " << m_row << "x" << m_column << endl;
    return *this;
}



StringListRegexFeeder & StringListRegexFeeder::operator--(int) { //postfix a--
    StringListRegexFeeder * const backup = new StringListRegexFeeder(*this);
// qDebug() << "--X" << endl;
    if (m_column > 0) {
        m_column--;
    } else if (m_row > 0) {
        m_row--;
        m_column = (*m_lines)[m_row].count() - 1;
    } else {
        // Move to start
        m_row = 0;
        m_column = 0;
    }
// qDebug() << "NOW " << m_row << "x" << m_column << endl;
    return *backup; // TODO free?
}



StringListRegexFeeder StringListRegexFeeder::operator+(int operand) {
    if (operand == 0) {
        return StringListRegexFeeder(*this);
    }

    const int count = m_lines->count();
    int walkRow = m_row;
    int walkColumn = m_column;

    if (operand > 0) {
        // Forwards
        for (;;) {
            // Already at end?
            if (walkRow >= count) {
                return StringListRegexFeeder(*m_lines, count, 0);
            }
            
            // Get remainder on current line
            const int len = (*m_lines)[walkRow].count();
            const int leftOnLine = (len - walkColumn) - 1;
            
            // Move to next line
            if (operand <= leftOnLine) {
                return StringListRegexFeeder(*m_lines, walkRow, walkColumn + operand);
            } else {
                operand -= leftOnLine;

                // Skip empty lines
                for (;;) {
                    walkRow++;
                    if (walkRow >= count) {
                        walkColumn = 0;
                        operand--;
                        break;
                    }
                    
                    const int len = (*m_lines)[walkRow].count();
                    if (len > 0) {
                        walkColumn = 0;
                        operand--;
                        break;
                    }
                }
            }
        }
    } else {
        // Backwards
        for (;;) {
            // Already at beginning?
            if ((walkRow == 0) && (walkColumn == 0)) {
                return StringListRegexFeeder(*m_lines, 0, 0);
            }
            
            // Get remainder on current line
            const int leftOnLine = walkColumn;

            // Move to next line
            if (-operand <= leftOnLine) {
                return StringListRegexFeeder(*m_lines, walkRow, walkColumn + operand);
            } else {
                operand += leftOnLine;

                // Skip empty lines
                for (;;) {
                    if (walkRow == 0) {
                        walkColumn = 0;
                        break;
                    }
                    
                    walkRow--;
                    const int len = (*m_lines)[walkRow].count();
                    if (len > 0) {
                        walkColumn = len - 1;
                        operand++;
                        break;     
                    }
                }
            }
        }
    }
}



StringListRegexFeeder StringListRegexFeeder::operator-(int operand) {
    return operator+(-operand);
}



StringListRegexFeeder & StringListRegexFeeder::operator+=(int operand) {
    return (*this = operator+(operand));
}



StringListRegexFeeder & StringListRegexFeeder::operator-=(int operand) {
    return (*this = operator+(-operand));
}



bool StringListRegexFeeder::operator>=(const StringListRegexFeeder & other) {
    return (m_row > other.m_row)
            || ((m_row == other.m_row) && (m_column >= other.m_column));
}



StringListRegexFeeder StringListRegexFeeder::begin() const {
    return StringListRegexFeeder(*m_lines, 0, 0);
}



StringListRegexFeeder StringListRegexFeeder::end() const {
    return StringListRegexFeeder(*m_lines, m_lines->count(), 0);
}



const ushort & StringListRegexFeeder::deref() const {
// qDebug() << "Deref" << m_row << "x" << m_column;
    if ((m_row < 0) || (m_row >= m_lines->count())) {
        Q_ASSERT(false);
    }

    if ((m_column < 0) || (m_column >= (*m_lines)[m_row].count())) {
        Q_ASSERT(false);
    }
// qDebug() << "Deref" << reinterpret_cast<const QChar &>(*((*m_lines)[m_row].constData() + m_column));

    return reinterpret_cast<const ushort &>(*((*m_lines)[m_row].constData() + m_column));
}
