#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>
#include <QString>
class QCalculatorUI : public QWidget
{
    Q_OBJECT

private:
    QCalculatorUI();
    QLineEdit* qlineEdit;
    QPushButton* qPushButtons[4][5];
    bool construct();
    QString calc(QString nowText, QString btnText);
public:
    static QCalculatorUI* NewInstance();
    void show();
protected slots:
    void qPushButtonBeClicked();
};
#endif // QCALCULATORUI_H
