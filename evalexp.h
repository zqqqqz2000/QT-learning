#ifndef EVALEXP_H
#define EVALEXP_H
#include <QString>
#include <QChar>
#include <stack>
class EvalExp
{
private:
    static std::stack<QString> middle2prefix(QString exp);
    static QString evalPreifx(std::stack<QString> exp);
    static bool isSimPrioHigher(QChar char1, QChar char2);
    static int sim2prioNum(QChar char_);
    static bool isZero(QString str);
public:
    static bool isLegal(QString exp);
    static QString eval(QString exp);
};

#endif // EVALEXP_H
