#include <qcalculatorui.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCalculatorUI* mainCalcUI = QCalculatorUI::NewInstance();
    if (mainCalcUI == NULL)
        return a.exec();
    mainCalcUI->show();
    return a.exec();
}
