#ifndef BOAT_PARAMETERS_H
#define BOAT_PARAMETERS_H

#include <QDialog>
#include <QObject>
#include <QMainWindow>

#include <QTreeWidgetItem>

namespace Ui {
class Boat_parameters;
}

class Boat_parameters : public QDialog
{
    Q_OBJECT

public:
    explicit Boat_parameters(QWidget *parent = 0);
    ~Boat_parameters();

    //Возврат имени объекта
    QString getBoatName();
    QString getBoatTopicGNSSname();
    int getBoatTopicGNSStype();
    int getBoatColour() const;

    void setParametrsFromItem(QTreeWidgetItem* init_item);

private:
    Ui::Boat_parameters *ui;
    //Параметры
    //Имя платформы
    QString boat_name;
    //Тип топика GNSS
    int boat_gnss_topic_type;
    //Имя топика
    QString boat_gnss_topic_name;
    //Цвет лодки
    int boat_colour;

    //Флаг, что параметры установлены
    bool is_parameters_setted;

protected:
    void accept();

Q_SIGNALS:
    void editionFinished();
    void editFinished(const Boat_parameters*);};

#endif // BOAT_PARAMETERS_H
