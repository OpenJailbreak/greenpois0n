#ifndef POISONMAIN_H
#define POISONMAIN_H

#include <QMainWindow>

namespace Ui {
    class PoisonMain;
}

class PoisonMain : public QMainWindow {
    Q_OBJECT
public:
    PoisonMain(QWidget *parent = 0);
    ~PoisonMain();

protected:
    void changeEvent(QEvent *e);
    void updateTimerText(QString &t);

private slots:
    void ResetTimer();
    void Jailbreak();
    void countdownDFU();

private:
    Ui::PoisonMain *ui;
    int step;
    int time;
    void doJailbreak();
    QTimer *timer;
};

#endif // POISONMAIN_H
