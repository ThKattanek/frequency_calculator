#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculate_clicked()
{
    double in_frequency_factor;
    double out_frequency_factor;

    switch(ui->in_frequency_unit->currentIndex())
    {
    case 0: // Hz - 10⁰
            in_frequency_factor = 1;
        break;
    case 1: // KHz - 10³
            in_frequency_factor = 1000;
        break;
    case 2: // MHz - 10⁶
            in_frequency_factor = 1000000;
        break;
    case 3: // GHz - 10⁹
            in_frequency_factor = 1000000000;
        break;
    }

    switch(ui->out_frequency_unit->currentIndex())
    {
    case 0: // Hz - 10⁰
            out_frequency_factor = 1;
        break;
    case 1: // KHz - 10³
            out_frequency_factor = 1000;
        break;
    case 2: // MHz - 10⁶
            out_frequency_factor = 1000000;
        break;
    case 3: // GHz - 10⁹
            out_frequency_factor = 1000000000;
        break;
    }

    double factor = ((double) ui->out_frequency->value() * in_frequency_factor) / ((double) ui->in_frequency->value() * out_frequency_factor);
    double calc = 0;

    uint32_t numerator = 0;
    uint32_t denominator = 1;

    uint32_t calc_numerator;
    uint32_t calc_denominator;

    uint32_t max_counter_bits_mask = (1 << ui->max_counter_bits->value()) - 1;

    do{
        calc_denominator = denominator;
        calc_numerator = numerator;

        if(denominator > 0) calc = (double)numerator / (double)denominator;
            else calc = 0;
        numerator++;
        if(numerator == max_counter_bits_mask)
        {
            numerator = 0;
            denominator++;
            denominator &= max_counter_bits_mask;
        }
    }while((factor != calc) && (denominator != 0));

    if(factor == calc)
    {
        ui->out_numerator->setText(QString::number(calc_numerator));
        ui->out_denominator->setText(QString::number(calc_denominator));

        QString n = "\"";
        QString d = "\"";

        uint32_t mask = 1 << (ui->max_counter_bits->value() - 1);

        for(int i=0; i<ui->max_counter_bits->value(); i++)
        {
            if(calc_numerator & mask)
                n += "1";
            else n += "0";

            if(calc_denominator & mask)
                d += "1";
            else d += "0";

            mask >>= 1;
        }

        ui->out_numerator_bits->setText(n + "\"");
        ui->out_denominator_bits->setText(d + "\"");
    }
    else
    {
        ui->out_numerator->setText("Not Found!");
        ui->out_denominator->setText("Not Found!");
    }
}
