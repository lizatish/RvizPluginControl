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
    boat_colour = ui->boat_colour_comboBox->currentIndex() + 1;

    is_parameters_setted = true;
    Q_EMIT editionFinished();

    this->close();
}
void Boat_parameters::setParametrsFromItem(QTreeWidgetItem* init_item){

    ui->boat_name_line->setText(init_item->text(0));
    ui->boat_gnss_type_comboBox->setCurrentIndex(0);
    ui->boat_gnss_topic_line->setText(init_item->text(1));

    QColor boat_colour_background = init_item->backgroundColor(2);

    if(boat_colour_background.red()){
        cout << "red " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(0);
    }
    else if (boat_colour_background.green()){
        cout << "GREEN " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(1);
    }
    else if (boat_colour_background.blue()){
        cout << "BLUE " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(2);
    }
    else if (boat_colour_background.yellow()){
        cout << "YELLOW " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(3);
    }
    else if (boat_colour_background.black()){
        cout << "blCK " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(4);
    }
    else if (boat_colour_background.cyan()){
        cout << "light-blue " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(5);
    }
    else if (boat_colour_background.magenta()){
        cout << "pink " << endl;
        ui->boat_colour_comboBox->setCurrentIndex(6);
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

void Boat_parameters::on_boat_colour_button_clicked()
{
    QColor colour = QColorDialog::getColor(Qt::yellow, this );

    if(colour.isValid())
    {
        ui->boat_colour_button->setText(colour.name());
//        ui->boat_colour_button->setStyleSheet("QPushButton {background-color:"+ colour.name() +";}");
        ui->boat_colour_button->setStyleSheet("background-color:"+ colour.name() +";");
        ui->boat_colour_button->styleSheet();
//        QPalette palette = ui->boat_colour_button->palette();
//        palette.setColor(QPalette::Background, colour);
//        ui->boat_colour_button->setPalette(palette);
//        ui->boat_colour_button->setAutoFillBackground(true);
    }

}
