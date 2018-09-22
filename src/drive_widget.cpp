
#include "drive_widget.h"

namespace rviz_plugin_control
{

DriveWidget::DriveWidget( QWidget* parent )
    : QWidget( parent )
    , linear_velocity_( 0 )
    , angular_velocity_( 0 )
    , currentItemIndex ( NULL )
{
    QGridLayout* manager_buttons_layout = new QGridLayout();
    QGridLayout* controls_layout = new QGridLayout();
    QGridLayout* boat_tree_layout = new QGridLayout();
    QGridLayout* stop_button_layout = new QGridLayout();
    QGridLayout* main_layout = new QGridLayout();

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
    boat_list_widget_->headerItem()->setText(1, "Topic");
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
    connect( boat_list_widget_, SIGNAL( itemClicked(QTreeWidgetItem*, int)), this, SLOT(set_current_item()));

}
DriveWidget::~DriveWidget(){
    //    delete boat_list_for_widget_ [];
    //    delete boat_list_ [];
    delete boat_list_widget_;
    delete angular_speed_label;
    delete linear_speed_label;
    delete add_button;
}

// Добавления нового объекта
void DriveWidget::add_button_on_clicked() {

    Boat_parameters* boat_parameters_= new Boat_parameters();
    boat_list_.append(boat_parameters_);
    //Подключаем добавление виджета в список
    connect(boat_parameters_, SIGNAL(editionFinished()), this, SLOT(add_boat_on_list() ));
    boat_parameters_->show();
}

// Удаление выбранного объекта
void DriveWidget::remove_button_on_clicked() {
    if(currentItemIndex >= 0){
        delete boat_list_widget_->takeTopLevelItem(currentItemIndex);
        boat_list_for_widget_.removeAt(currentItemIndex);
        boat_list_.removeAt(currentItemIndex);
    }
}

// Редактирование выбранного объекта
void DriveWidget::edit_button_on_clicked() {
    if(currentItemIndex >= 0){
        Boat_parameters* boat_parameters_ = new Boat_parameters();
        boat_parameters_->setParametrsFromItem(boat_list_widget_->currentItem());
        boat_parameters_->show();

        //Подключаем добавление виджета в список
        connect(boat_parameters_, SIGNAL(editionFinished()), this, SLOT(edit_boat_to_boat_list()));
    }
}

void DriveWidget::edit_boat_to_boat_list() {

    Boat_parameters* boat_parameters_ = (Boat_parameters*)qobject_cast<QWidget*>(sender());
    QTreeWidgetItem* edit_item = new QTreeWidgetItem();

    //Добавляем в виджет
    edit_item->setText(0, boat_parameters_->getBoatName());
    edit_item->setText(1, boat_parameters_->getBoatTopicGNSSname());
    edit_item->setBackground(2, QBrush(boat_parameters_->getBoatColor()));

    boat_list_widget_->takeTopLevelItem(currentItemIndex);
    boat_list_widget_->insertTopLevelItem(currentItemIndex, edit_item);
    boat_list_widget_->setCurrentItem(boat_list_widget_->topLevelItem(currentItemIndex));
}

void DriveWidget::add_boat_on_list() {

    //Объект параметров платформы
    Boat_parameters *boat_parameters_ = boat_list_.last();

    //Добавляем в виджет
    QTreeWidgetItem *new_item = new QTreeWidgetItem();

    new_item->setText(0, boat_parameters_->getBoatName());
    new_item->setText(1, boat_parameters_->getBoatTopicGNSSname());
    new_item->setBackground(2, QBrush(boat_parameters_->getBoatColor()));

    boat_list_for_widget_.append(new_item);
    boat_list_widget_->insertTopLevelItems(0, boat_list_for_widget_);

    //Запускаем узел
    Boat_server_node *ros_node_ = new Boat_server_node();
    //Передаём данные
    ros_node_->setName(boat_parameters_->getBoatName());
    if(boat_parameters_->getBoatTopicGNSStype() == 1)
        ros_node_->setGNSSpublisher(boat_parameters_->getBoatTopicGNSSname(), Boat_server_node::geometry_msgs_Twist);


    QThread *ros_node_thread_ = new QThread;
    ros_node_->moveToThread(ros_node_thread_);
    connect(ros_node_thread_, SIGNAL(started()), ros_node_, SLOT(process()));

    ros_node_thread_->start();
    ros_node_list_.append(ros_node_);
    ros_node_thread_list_.append(ros_node_thread_);
}
void DriveWidget::setLinearData( int linear_data )
{
    linear_speed_label->setNum(linear_data);
    linear_velocity_ = linear_data;
    update();
}
void DriveWidget::setAngularData( int angular_data )
{
    angular_speed_label->setNum(angular_data);
    angular_velocity_ = angular_data;

    ros_node_list_.takeAt(currentItemIndex);
    update();
}

void DriveWidget::stopBoat(){

}

void DriveWidget::set_current_item(){
    currentItemIndex = boat_list_widget_->currentIndex().row();
}

void DriveWidget::save( rviz::Config config ) const
{
    //    rviz::Panel::save( config );
    //    config.mapSetValue( "Topic_objects", output_topic_objects_ );
    //    config.mapSetValue( "Topic_path", output_topic_log_path );
    //    config.mapSetValue( "Map_file_path", pathToMap );
    //    config.mapSetValue( "Log_file_path", pathToLog );
}

// Load all configuration data for this panel from the given Config object.
void DriveWidget::load( const rviz::Config& config )
{
    //    rviz::Panel::load( config );
    //    QString topic_map_objects;
    //    if(config.mapGetString( "Topic_objects", &topic_map_objects )) {
    //        setTopic_objects(topic_map_objects);
    //    }
    //    QString topic_log;
    //    if(config.mapGetString( "Topic_path", &topic_log )) {
    //        setTopic_log_path(topic_log);
    //    }

    //    if( config.mapGetString( "Map_file_path", &pathToMap ))
    //    {
    //        this->loadMap();
    //    }
    //    if( config.mapGetString( "Log_file_path", &pathToLog ))
    //    {
    //        this->loadLog();
    //    }

}
// END_TUTORIAL

} // end namespace rviz_plugin_tutorials
