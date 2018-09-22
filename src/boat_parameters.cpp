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
void Boat_parameters::setParametrsFromItem(QTreeWidgetItem* init_item){

    ui->boat_name_line->setText(init_item->text(0));
    ui->boat_gnss_type_comboBox->setCurrentIndex(0);
    ui->boat_gnss_topic_line->setText(init_item->text(1));
    setColorOnButton(init_item->backgroundColor(2));
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

QColor Boat_parameters::getBoatColor() const
{
    return boat_color;
}

void Boat_parameters::on_boat_color_button_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );

    if(color.isValid())
    {
        setColorOnButton(color);
    }
}
void Boat_parameters::setColorOnButton(QColor color){
    ui->boat_color_button->setStyleSheet("background-color:" + color.name() +";");
    ui->boat_color_button->styleSheet();
    boat_color = color;
}

