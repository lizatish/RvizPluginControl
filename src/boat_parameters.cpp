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
    Q_EMIT editionFinished();
    this->close();
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
