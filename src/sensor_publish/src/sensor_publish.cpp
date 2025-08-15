#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_interface/sensor_interface/msg/sensor.hpp"

using namespace std::chrono_literals;

class SensorPublish:public rclcpp::Node{
public:
 SensorPublish():Node("sensor"){
    publisher_ = this->create_publisher<sensor_interface::msg::Sensor>("sensorTopic",10);
    timer_=this->create_wall_timer(100ms,std::bind(&SensorPublish::timer_callback,this));

 }

private:
 void timer_callback(){
    auto value = sensor_interface::msg::Sensor();
    RCLCPP_INFO(this->get_logger(), "Publishing: '%ld'", value.num);

 }
 rclcpp::TimerBase::SharedPtr timer_;
 rclcpp::Publisher<sensor_interface::msg::Sensor>::SharedPtr publisher_;
};
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorPublish>());
  rclcpp::shutdown();
  return 0;
}