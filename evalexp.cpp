#include <evalexp.h>
#include <stack>
#include <QDebug>
#include <string>
#include <exception>

int EvalExp::sim2prioNum(QChar char_)
{
    int prioSimNum = 0;
    switch (char_.unicode()) {
    case '+':
        prioSimNum = 1;
        break;
    case '-':
        prioSimNum = 1;
        break;
    case '*':
        prioSimNum = 2;
        break;
    case '/':
        prioSimNum = 2;
        break;
    case '(':
        prioSimNum = 0;
        break;
    case ')':
        prioSimNum = 0;
        break;
    case '#':
        prioSimNum = -1;
        break;
    default:
        break;
    }
    return prioSimNum;
}

bool EvalExp::isSimPrioHigher(QChar char1, QChar char2)
{
    int char1Pri = EvalExp::sim2prioNum(char1);
    int char2Pri = EvalExp::sim2prioNum(char2);
    if (char1Pri >= char2Pri)
        return true;
    return false;
}

bool EvalExp::isLegal(QString exp)
{
    exp.replace(".", "");
    if (exp.isEmpty())
    {
        return false;
    }
    exp = exp.replace(" ", "");
    std::stack<QChar> bracked;
    // to avoid +-near*/
    for (int i = 0; i < exp.length(); i++)
    {
        if ((exp[i] != '.' && exp[i] != '(' && exp[i] != ')' && exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/') && !(exp[i] >= 48 && exp[i] <= 57))
            return false;
        if (exp[i] == '(')
            bracked.push('(');
        else if(exp[i] == ')')
        {
            if (bracked.size() == 0)
                return false;
            else
                bracked.pop();
        }
    }
    if (bracked.size() != 0)
        return false;
    return true;
}

std::stack<QString> EvalExp::middle2prefix(QString exp)
{
    std::stack<QString> resStack;
    std::stack<QChar> simStack;
    simStack.push((QChar)'#');
    QString tempStr("");
    for (int i = exp.length() - 1; i >= 0; i--)
    {
        if (exp[i] >= 48 && exp[i] <= 57 || exp[i] == '.')
        {
            // if is number push it in to a tempStr
            tempStr.insert(0, exp[i]);
        }
        else
        {
            // if is a symbol, push the tempStr number into resStack, and clear it
            if (!tempStr.isEmpty())
                resStack.push(tempStr);
            tempStr.clear();
            // if is ()
            if (exp[i] == ')')
            {
                simStack.push((QChar)')');
                continue;
            }
            else if (exp[i] == '(')
            {
                while (simStack.top() != ')') {
                    resStack.push(simStack.top());
                    simStack.pop();
                }
                simStack.pop();
                continue;
            }
            // other symbol
            if (EvalExp::isSimPrioHigher(exp[i], simStack.top()))
                simStack.push(exp[i]);
            else
            {
                while (!EvalExp::isSimPrioHigher(exp[i], simStack.top())) {
                    resStack.push(simStack.top());
                    simStack.pop();
                }
                simStack.push(exp[i]);
            }
        }
    }
    if (!tempStr.isEmpty())
        resStack.push(tempStr);
    QString resExp;
    while (!simStack.empty()) {
        resStack.push(simStack.top());
        simStack.pop();
    }
    std::stack<QString>* finalStack = new std::stack<QString>();
    resStack.pop();
    while (!resStack.empty())
    {
        finalStack->push(resStack.top());
        resStack.pop();
    }
    return *finalStack;
}
bool EvalExp::isZero(QString str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != '0')
            return false;
    }
    return true;
}
QString EvalExp::evalPreifx(std::stack<QString> exp)
{
    std::stack<double> res;
    while (!exp.empty()) {
        QString temp = exp.top();
        exp.pop();
        try
        {
            double num = temp.toDouble();
            if (num == 0. && !EvalExp::isZero(temp))
                throw std::exception();
            res.push(num);
        }
        catch (...)
        {
            QChar symbol = temp[0];
            double calcRes = 0;
            double obj1 = res.top();
            res.pop();
            double obj2 = res.top();
            res.pop();
            switch (symbol.unicode()) {
            case '+':
                calcRes = obj1 + obj2;
                break;
            case '-':
                calcRes = obj1 - obj2;
                break;
            case '*':
                calcRes = obj1 * obj2;
                break;
            case '/':
                calcRes = obj1 / obj2;
                break;
            default:
                break;
            }
            res.push(calcRes);
        }
    }
    return QString::number(res.top());
}

QString EvalExp::eval(QString exp)
{
    if (!EvalExp::isLegal(exp))
        return QString("ERROR");
    std::stack<QString> prefix = EvalExp::middle2prefix(exp);
    return EvalExp::evalPreifx(prefix);
}
