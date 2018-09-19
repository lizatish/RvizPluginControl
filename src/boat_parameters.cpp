#include "boat_parameters.h"

//#include "ui_ugv_parameters.h"

Boat_parameters::Boat_parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ugv_parameters)
{
    ui->setupUi(this);
    is_parameters_setted = false;
}

Boat_parameters::~ugv_parameters()
{
    delete ui;
}

void Boat_parameters::accept() {
    //Получаем параметры
    boat_name = ui->ugv_name_lineEdit->text();
    boat_gnss_topic_type = ui->ugv_gnss_type_comboBox->currentIndex() + 1;
    boat_gnss_topic_name = ui->ugv_gnss_topic_lineEdit->text();
    boat_battery_topic_name = ui->ugv_battery_topic_lineEdit->text();
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
