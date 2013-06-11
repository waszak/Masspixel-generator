#include "SyntaxHighlighter.hpp"

sdSyntaxHighlighter::sdSyntaxHighlighter(QTextDocument* doc) : QSyntaxHighlighter(doc)
{
    HighlightingRule rule;

    ////////////////////////
    /// Keywords
    keywordFormat.setForeground(QColor::fromRgb(240,223,175));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "cube\\s" << "sphere\\s" << "box\\s" << "torus\\s"
        << "cylinder\\s" << "plane\\s";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    QStringList keywordPatterns2;
    keywordFormat2.setForeground(QColor::fromRgb(255,207,175));
    keywordFormat2.setFontWeight(QFont::Bold);
    keywordPatterns2 << "boolean\\s" << "scale\\s" << "matrix\\s" << "translate\\s" << "duplicate\\s"
        << "trans\\s" << "rot\\s" << "rotate\\s";

    foreach (const QString &pattern, keywordPatterns2) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat2;
        highlightingRules.append(rule);
    }

    QStringList cmdPatterns;
    cmdFormat.setForeground(QColor::fromRgb(220,163,163));
    cmdFormat.setFontWeight(QFont::Bold);
    cmdPatterns << "mat\\s" << "light\\s" << "cam\\s" << "camera\\s" << "material\\s";

    foreach (const QString &pattern, cmdPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = cmdFormat;
        highlightingRules.append(rule);
    }

    numFormat.setForeground(QColor::fromRgb(140,208,211));
    numFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("\\b[-+]?\\d+\\b");
    rule.format = numFormat;
    highlightingRules.append(rule);


    opFormat.setForeground(QColor::fromRgb(239,239,143));
    rule.pattern = QRegExp("\\s\\<\\-\\s");
    rule.format = opFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\s=\\s"); // wtf to nie dziala jak sie polaczy z powyzszym?!
    rule.format = opFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\*[a-zA-Z][0-9a-zA-Z]*");
    rule.format = opFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\b\\w+(?=\\s+=)");
    rule.format = opFormat;
    highlightingRules.append(rule);
}

sdSyntaxHighlighter::~sdSyntaxHighlighter()
{

}

void sdSyntaxHighlighter::highlightBlock(const QString& text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}