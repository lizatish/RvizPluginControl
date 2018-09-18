
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

    linear_label = new QLabel( "Speed" );
    linear_slider = new QSlider( Qt::Vertical );

    angular_label = new QLabel( "Turn" );
    angular_slider = new QSlider( Qt::Horizontal );


    linear_slider->setMinimum( -50 );
    linear_slider->setMaximum( 50 );

    stop_button = new QPushButton();
    stop_button->setStyleSheet("QPushButton {background-color: #FF0000; color: white;}");
    stop_button->setText("STOP");

    angular_slider->setMinimum( -50 );
    angular_slider->setMaximum( 50 );


    angular_speed_label = new QLabel();
    linear_speed_label = new QLabel();


    boat_name = new QLabel("Boat name");
    boat_number = new QLabel("15");

    controls_layout = new QGridLayout(this);
    boat_data_layout = new QGridLayout(this);
    stop_button_layout = new QGridLayout(this);
    main_layout = new QGridLayout(this);

    boat_data_layout->addWidget( boat_name, 0, 0);
    boat_data_layout->addWidget( boat_number, 0, 1 );

    controls_layout->addWidget( linear_label, 0, 0 );
    controls_layout->addWidget( linear_speed_label, 0, 1 );
    controls_layout->addWidget( linear_slider, 0, 2 );
    controls_layout->addWidget( angular_label, 0, 3);
    controls_layout->addWidget( angular_speed_label, 0, 4);
    controls_layout->addWidget( angular_slider, 0, 5);

    stop_button_layout->addWidget( stop_button, 0, 0 );

    boats_list = new QComboBox(this);
    boats_list->addItem("Boat 1");
    boats_list->addItem("Boat 2");
    boats_list->addItem("Boat 3");
    boat_data_layout->addWidget( boats_list, 0, 2);

    main_layout->addLayout(boat_data_layout, 0 , 0);
    main_layout->addLayout(controls_layout, 1 , 0);
    main_layout->addLayout(stop_button_layout, 2 , 0);

    setLayout( main_layout );


}


void DriveWidget::paintEvent( QPaintEvent* event )
{
    linear_speed_label->setNum(linear_velocity_);
    angular_speed_label->setNum(angular_velocity_);

    connect( linear_slider, SIGNAL( valueChanged( int )), this, SLOT( setLinearData( int )));
    connect( angular_slider, SIGNAL( valueChanged( int )), this, SLOT( setAngularData( int )));
    connect( stop_button, SIGNAL( pressed()), this, SLOT( stopBoat()));
    connect(boats_list, SIGNAL(activated(int)), this, SLOT(clickedaction(int)));

}


void DriveWidget::setLinearData( int linear_data )
{
    linear_velocity_ = linear_data;
    Q_EMIT outputVelocity( linear_velocity_, angular_velocity_ );
    update();
}
void DriveWidget::setAngularData( int angular_data )
{
    angular_velocity_ = angular_data;
    Q_EMIT outputVelocity( linear_velocity_, angular_velocity_ );
    update();
}

void DriveWidget::leaveEvent( QEvent* event )
{
    stop();
}

void DriveWidget::stopBoat(){
    stop();
}


void DriveWidget::stop()
{
    linear_velocity_ = 0;
    angular_velocity_ = 0;
    Q_EMIT outputVelocity( linear_velocity_, angular_velocity_ );
    update();
}
// END_TUTORIAL

} // end namespace rviz_plugin_tutorials
