#include <qcalculatorui.h>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QString>
#include <evalexp.h>

QString QCalculatorUI::calc(QString nowText, QString btnText)
{
    if (btnText.compare("=") == 0)
    {
        QString result = EvalExp::eval(nowText);
        return result;
    }
    if (btnText.compare("←") == 0)
    {
        return nowText.mid(0, nowText.length() - 1);
    }
    if (btnText.compare("C") == 0)
    {
        return QString("");
    }
    return nowText.append(btnText);
}


void QCalculatorUI::qPushButtonBeClicked()
{
    QPushButton* senderBtn = (QPushButton*)sender();
    QString nowText = this->qlineEdit->text();
    QString res_text = calc(nowText, senderBtn->text());
    this->qlineEdit->setText(res_text);
    this->qlineEdit->text().append(senderBtn->text());
}

bool QCalculatorUI::construct()
{
    bool ret = true;
    // the buttons text
    const char* btnText[20] =
    {
       "7", "8", "9", "+", "(",
       "4", "5", "6", "-", ")",
       "1", "2", "3", "*", "←",
       "0", ".", "=", "/", "C",
    };
    this->resize(270, 270);
    // Set the window title
    this->setWindowTitle("calculator");
    // add Line edit
    this->qlineEdit = new QLineEdit(this);
    this->qlineEdit->resize(249, 40);
    this->qlineEdit->move(10, 5);
    this->qlineEdit->setParent(this);
    // init the containor array
    for (int i = 0; (i < 4) && ret; i++)
        for (int j = 0; j < 5; j++)
        {
            this->qPushButtons[i][j] = new QPushButton(this);
            if (this->qPushButtons[i][j] == NULL)
            {
                ret = false;
                break;
            }
            qPushButtons[i][j]->setParent(this);
            this->qPushButtons[i][j]->setText(btnText[i * 5 + j]);
            this->qPushButtons[i][j]->move(10 + (10 + 40) * j, 50 + (10 + 40) * i);
            this->qPushButtons[i][j]->resize(50, 50);
            connect(this->qPushButtons[i][j], SIGNAL(clicked()), this, SLOT(qPushButtonBeClicked()));
        }
    return ret;
}

void QCalculatorUI::show()
{
    this->QWidget::show();
    setFixedSize(width(), height());
}

QCalculatorUI::QCalculatorUI(){}

QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI* ret = new QCalculatorUI();

    if((ret == NULL) || !ret->construct()) {
        delete ret;
        ret = NULL;
    }
    return ret;
}
