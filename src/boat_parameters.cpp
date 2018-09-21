#include "boat_parameters.h"
#include "ui_boat_parameters.h"

Boat_parameters::Boat_parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Boat_parameters)
{
    ui->setupUi(this);
    is_parameters_setted = false;
}

Boat_parameters::~Boat_parameters()
{
    delete ui;
}

void Boat_parameters::accept() {
    //Получаем параметры
    boat_name = ui->boat_name_line->text();
    boat_gnss_topic_type = ui->boat_gnss_type_comboBox->currentIndex() + 1;
    boat_gnss_topic_name = ui->boat_gnss_topic_line->text();
    is_parameters_setted = true;
    boat_colour = ui->boat_colour_comboBox->currentIndex() + 1;
    Q_EMIT editionFinished();
    Q_EMIT editFinished(this);

    this->close();
}
void Boat_parameters::setParametrsFromItem(QTreeWidgetItem* init_item){

    boat_name = init_item->text(0);
    boat_gnss_topic_type = 1;
    boat_gnss_topic_name = init_item->text(1);
    is_parameters_setted = true;

    ui->boat_name_line->setText(init_item->text(0));
    ui->boat_gnss_type_comboBox->setCurrentIndex(0);
    ui->boat_gnss_topic_line->setText(init_item->text(1));

    QColor boat_colour_background = init_item->backgroundColor(3);
    if(boat_colour_background.red()){
        ui->boat_colour_comboBox->setCurrentIndex(0);
        boat_colour = 1;
    }
    else if (boat_colour_background.green()){
        ui->boat_colour_comboBox->setCurrentIndex(1);
        boat_colour = 2;
    }
    else if (boat_colour_background.blue()){
        ui->boat_colour_comboBox->setCurrentIndex(2);
        boat_colour = 3;
    }
    else if (boat_colour_background.yellow()){
        ui->boat_colour_comboBox->setCurrentIndex(3);
        boat_colour = 4;
    }
    else if (boat_colour_background.black()){
        ui->boat_colour_comboBox->setCurrentIndex(4);
        boat_colour = 5;
    }
    else if (boat_colour_background.cyan()){
        ui->boat_colour_comboBox->setCurrentIndex(5);
        boat_colour = 6;
    }
    else if (boat_colour_background.magenta()){
        ui->boat_colour_comboBox->setCurrentIndex(6);
        boat_colour = 7;
    }
}

QString Boat_parameters::getBoatName() {
    if(is_parameters_setted)
        return boat_name;
}

QString Boat_parameters::getBoatTopicGNSSname() {
    if(is_parameters_setted)
        return boat_gnss_topic_name;
}

int Boat_parameters::getBoatTopicGNSStype() {
    if(is_parameters_setted)
        return boat_gnss_topic_type;
}

int Boat_parameters::getBoatColour() const
{
    return boat_colour;
}
