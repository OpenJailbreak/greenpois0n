#include "poisonmain.h"
#include "ui_poisonmain.h"
#include <QTimer>
#include <stdio.h>
#include "../../../injector/libpois0n.h"

Ui::PoisonMain *gui;
void update_progress(double progress, void *gui);

PoisonMain::PoisonMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PoisonMain)
{
    ui->setupUi(this);
    step = 0;
    time = 3;
    timer = new QTimer();
    gui = ui;
    pois0n_init();
    pois0n_set_callback(&update_progress, ui);
}

PoisonMain::~PoisonMain()
{
    delete ui;
}

void PoisonMain::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PoisonMain::updateTimerText(QString &t) {
    ui->lblTime->setText("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt; font-weight:600;\">" + t + "</span></p></body></html>");
}

void PoisonMain::countdownDFU() {
    QString *t = new QString();
    t->setNum(time, 10);
    updateTimerText(*t);

    if (pois0n_is_ready() != -1) {
        ui->lblStep3->setText("Release power; continue holding home");
        timer->stop();
        ui->cmdJailbreak->setEnabled(true);
        ui->cmdReset->setEnabled(false);
        timer = NULL;
        delete timer;
        delete t;
	doJailbreak();
        return;
    }

    if (time == 0) {
        switch (step) {
            case 0:
                ui->lblGetReady->setText("Get ready for DFU");
                ui->lblStep1->setText("<b>Press and hold sleep button</b>");
                time = 10;
                break;
            case 1:
                ui->lblStep1->setText("Press and hold sleep button");
                ui->lblStep2->setText("<b>Continue holding sleep; press and hold home</b>");
                time = 5;
                break;
            case 2:
                ui->lblStep2->setText("Continue holding sleep; press and hold home");
                ui->lblStep3->setText("<b>Release power; continue holding home</b>");
                time = 30;
                break;
            case 3:
               ui->lblStep3->setText("Release power; continue holding home");
               timer->stop();
               ui->cmdJailbreak->setEnabled(true);
               ui->cmdReset->setEnabled(false);
               timer = NULL;
               delete timer;
               delete t;
	       doJailbreak();
               return;
               break;
        }
        step++;
    } else {
        time--;
    }
    delete t;
}


void PoisonMain::ResetTimer() {
    step = 0;
    time = 3;
    ui->lblGetReady->setText("<b>Get ready for DFU</b>");
    ui->lblStep1->setText("Press and hold sleep button");
    ui->lblStep2->setText("Continue holding sleep; press and hold home");
    ui->lblStep3->setText("Release power; continue holding home");
}

void PoisonMain::Jailbreak() {
    if (timer == NULL)
        timer = new QTimer();
    this->ResetTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(countdownDFU()));
    timer->start();
    ui->cmdJailbreak->setEnabled(false);
    ui->cmdReset->setEnabled(true);
    ui->cmdJailbreak->setText("Entering DFU...");
}

void PoisonMain::doJailbreak() {
    //We should be in DFU now
    if (pois0n_is_ready() == -1) {
        ui->cmdJailbreak->setText("Failed to enter DFU");
        return;
    }
    if (pois0n_is_compatible() == -1) {
        ui->cmdJailbreak->setText("Incompatible Device");
        return;
    }
    ui->cmdJailbreak->setText("Exploiting...");
    pois0n_inject();
    pois0n_exit();
    ui->cmdJailbreak->setText("Done! Please wait.");
}

void update_progress(double progress, void *ui) {
    gui->progressBar->setValue(progress);
    ui = ui;
}
