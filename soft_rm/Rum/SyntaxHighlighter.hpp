#ifndef __SYNTAX_HIGHLIGHTER_HPP__
#define __SYNTAX_HIGHLIGHTER_HPP__
#include <QtGui/QtGui>

class sdSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    sdSyntaxHighlighter(QTextDocument* doc);
    ~sdSyntaxHighlighter();

    void highlightBlock(const QString& txt);

public:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat keywordFormat2;
    QTextCharFormat numFormat;
    QTextCharFormat cmdFormat;
    QTextCharFormat opFormat;
};


#endif //__SYNTAX_HIGHLIGHTER_HPP__
