
#include "drive_widget.h"

namespace rviz_plugin_control
{

DriveWidget::DriveWidget( QWidget* parent )
    : QWidget( parent )
    , linear_velocity_( 0 )
    , angular_velocity_( 0 )
    , linear_scale_( 10 )
    , angular_scale_( 2 )
{
    QGridLayout* manager_buttons_layout = new QGridLayout();
    QGridLayout* controls_layout = new QGridLayout();
    QGridLayout* boat_tree_layout = new QGridLayout();
    QGridLayout* stop_button_layout = new QGridLayout();
    QGridLayout* main_layout = new QGridLayout();

    selectedItemIndex = NULL;
    //******************** Кнопки изменения листа с лодочками

    add_button = new QPushButton();
    QPushButton* edit_button = new QPushButton();
    QPushButton* remove_button = new QPushButton();

    add_button->setText("Add");
    add_button->setMaximumWidth(100);
    edit_button->setText("Edit");
    edit_button->setMaximumWidth(100);
    remove_button->setText("Remove");
    remove_button->setMaximumWidth(100);

    // Добавление в сетку расположения
    manager_buttons_layout->addWidget(add_button, 0, 0);
    manager_buttons_layout->addWidget(edit_button, 0, 1);
    manager_buttons_layout->addWidget(remove_button, 0, 2);

    //******************** Лист с лодочками

    // Общий лист лодочек
    boat_list_widget_ = new QTreeWidget();
    boat_list_widget_->setColumnCount(3);
    boat_list_widget_->setMaximumHeight(240);

    // Параметры листа
    boat_list_widget_->headerItem()->setText(0, "Number");
    boat_list_widget_->headerItem()->setText(1, "Name");
    boat_list_widget_->headerItem()->setText(2, "Colour");
    boat_list_widget_->setMinimumHeight(50);

    // Добавление в сетку расположения
    boat_tree_layout->addWidget(boat_list_widget_, 0, 0);

    //******************** Слайдеры управления скоростями

    // Имя слайдеров
    QLabel* linear_label = new QLabel( "Linear" );
    QSlider* linear_slider = new QSlider( Qt::Vertical );
    QLabel* angular_label = new QLabel( "Angular" );
    QSlider* angular_slider = new QSlider( Qt::Horizontal );

    // Предельные значения линейного слайдера
    linear_slider->setMinimum( -50 );
    linear_slider->setMaximum( 50 );
    linear_slider->setMaximumHeight(200);

    // Предельные значения углового слайдера
    angular_slider->setMinimum( -50 );
    angular_slider->setMaximum( 50 );
    angular_slider->setMaximumWidth(200);

    // Переменная со значением линейной скорости
    linear_speed_label = new QLabel();
    linear_speed_label->setMinimumWidth(25);
    linear_speed_label->setAlignment(Qt::AlignCenter);

    // Переменная со значением угловой скорости
    angular_speed_label = new QLabel();
    angular_speed_label->setMinimumWidth(25);
    angular_speed_label->setAlignment(Qt::AlignCenter);

    // Добавление в сетку расположения
    controls_layout->addWidget(linear_label, 0, 0);
    controls_layout->addWidget(linear_speed_label, 0, 1);
    controls_layout->addWidget(linear_slider, 0, 2 );
    controls_layout->addWidget(angular_label, 0, 3);
    controls_layout->addWidget(angular_speed_label, 0, 4);
    controls_layout->addWidget(angular_slider, 0, 5);

    //******************** Стоп-кнопка

    QPushButton* stop_button = new QPushButton();
    stop_button->setStyleSheet("QPushButton {background-color: #FF0000; color: white;}");
    stop_button->setText("STOP");
    stop_button->setMaximumWidth(100);

    // Добавление в сетку расположения
    stop_button_layout->addWidget( stop_button, 0, 0);

    //******************************************************

    main_layout->addLayout(manager_buttons_layout, 0, 0);
    main_layout->addLayout(boat_tree_layout, 1, 0);
    main_layout->addLayout(controls_layout, 2, 0);
    main_layout->addLayout(stop_button_layout, 3, 0);

    setLayout( main_layout );

    connect( linear_slider, SIGNAL( valueChanged( int )), this, SLOT( setLinearData( int )));
    connect( angular_slider, SIGNAL( valueChanged( int )), this, SLOT( setAngularData( int )));
    connect( stop_button, SIGNAL( pressed()), this, SLOT( stopBoat()));
    connect( add_button, SIGNAL( clicked()), this, SLOT(add_button_on_clicked() ));
    connect( edit_button, SIGNAL( clicked()), this, SLOT(edit_button_on_clicked() ));
    connect( remove_button, SIGNAL( clicked()), this, SLOT(remove_button_on_clicked() ));
}

//Добавления нового объекта
void DriveWidget::add_button_on_clicked() {

    Boat_parameters *boat_parameters_= new Boat_parameters();
    boat_list_.append(boat_parameters_);
    //Подключаем добавление виджета в список
    connect(boat_parameters_, SIGNAL(editionFinished()), this, SLOT(add_boat_on_list() ));
    boat_parameters_->show();
}
//Добавления нового объекта
void DriveWidget::remove_button_on_clicked() {

    //    QString converter = boat_list_widget_->currentItem()-/;
    //    int n = converter.toInt();
    //   QTreeWidgetItem* remove_item =  boat_list_widget_->currentItem();
    //   remove_item->i
    //removeItemWidget(QTreeWidgetItem * item, int column)
    //    int x = boat_list_widget_->currentItem()->columnCount();

    //    ROS_INFO("%d", n);
    //    boat_list_.append(boat_parameters_);
    //    //Подключаем добавление виджета в список
    //    connect(boat_parameters_, SIGNAL(editionFinished()), this, SLOT(add_boat_on_list() ));
    //    boat_parameters_->show();
}

//Добавления нового объекта
void DriveWidget::edit_button_on_clicked() {

    QModelIndex index = boat_list_widget_->currentIndex();
    selectedItemIndex = index.row();

    ROS_INFO("LIST CLICK %d", selectedItemIndex);
}

void DriveWidget::add_boat_on_list() {
    //Объект параметров платформы
    Boat_parameters *boat_parameters_ = boat_list_.last();

    //Добавляем в виджет
    QTreeWidgetItem *new_item = new QTreeWidgetItem();
    new_item->setText(0, boat_parameters_->getBoatName());
    QString topic_type = boat_parameters_->getBoatTopicGNSSname();
    new_item->setText(1, topic_type);
    //    new_item->setTextColor(1,QColor(Qt::red));
    boat_list_for_widget_.append(new_item);
    boat_list_widget_->insertTopLevelItems(0, boat_list_for_widget_);

    //    //Запускаем узел
    //    ugv_server_node *ros_node_ = new ugv_server_node();
    //    //Передаём данные
    //    ros_node_->setName(ugv_parameters_->getUGVname());
    //    if(ugv_parameters_->getUGVtopicGNSStype() == 1)
    //        ros_node_->setGNSSsubscriber(ugv_parameters_->getUGVtopicGNSSname(), ugv_server_node::nav_msgs_Odometry);
    //    if(ugv_parameters_->getUGVtopicGNSStype() == 2)
    //        ros_node_->setGNSSsubscriber(ugv_parameters_->getUGVtopicGNSSname(), ugv_server_node::sensor_msgs_NavSatFix);

    //    QThread *ros_node_thread_ = new QThread;
    //    ros_node_->moveToThread(ros_node_thread_);

    //    connect(ros_node_thread_, SIGNAL(started()), ros_node_, SLOT(process()));
    //    ////    connect(LaserScanner, SIGNAL(scanReady()), this, SLOT(laserScanProcessing()));
    //    ////    connect(this, SIGNAL(stopROS()), LaserScanner, SLOT(stop()));
    //    ros_node_thread_->start();
    //    ros_node_list_.append(ros_node_);
    //    ros_node_thread_list_.append(ros_node_thread_);
}
void DriveWidget::setLinearData( int linear_data )
{
    linear_speed_label->setNum(linear_data);
    linear_velocity_ = linear_data;
    Q_EMIT outputVelocity( linear_velocity_, angular_velocity_ );
    update();
}
void DriveWidget::setAngularData( int angular_data )
{
    angular_speed_label->setNum(angular_data);
    angular_velocity_ = angular_data;
    Q_EMIT outputVelocity( linear_velocity_, angular_velocity_ );
    update();
}

void DriveWidget::stopBoat()
{
    linear_velocity_ = 0;
    angular_velocity_ = 0;
    Q_EMIT outputVelocity( linear_velocity_, angular_velocity_ );
    update();
}
// END_TUTORIAL

} // end namespace rviz_plugin_tutorials
