#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_interface/sensor_interface/msg/sensor.hpp"
#include "std_srvs/srv/set_bool.hpp"
using std::placeholders::_1,std::placeholders::_2;
using SetBool =std_srvs::srv::SetBool;
class SensorSubscriber:public rclcpp::Node{
    public:
        SensorSubscriber():Node("sensorSubscriber"),sensorValue(0){
            leftSubscriber_ = this->create_subscription<sensor_interface::msg::Sensor>("leftSensorTopic",10,std::bind(&SensorSubscriber::topic_callback,this,_1));
            rightSubscriber_ =this->create_subscription<sensor_interface::msg::Sensor>("rightSensorTopic",10,std::bind(&SensorSubscriber::topic_callback,this,_1));
            service_ = this->create_service<SetBool>("sensorService",std::bind(&SensorSubscriber::send_callback,this,_1,_2));
        }

    private:
    void topic_callback(const sensor_interface::msg::Sensor& value){
        RCLCPP_INFO(this->get_logger(), "I heard: '%ld'", value.num);
        sensorValue = value.num;

    }
    void send_callback(const std::shared_ptr<SetBool::Request>request,const std::shared_ptr<SetBool::Response>response){
        std::string leftSensor = "왼쪽 센서값: ";
        std::string rightSensor = "오른쪽 센서값: ";

        leftSensor += std::to_string(sensorValue);
        rightSensor += std::to_string(sensorValue);
        
        if (request->data)
        {
            response->message = leftSensor;
        }
        else{
            response->message = rightSensor;
        }
        

    }
    
    rclcpp::Subscription<sensor_interface::msg::Sensor>::SharedPtr rightSubscriber_;
      rclcpp::Subscription<sensor_interface::msg::Sensor>::SharedPtr leftSubscriber_;
    rclcpp::Service<SetBool>::SharedPtr service_;
    long int sensorValue;

    
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorSubscriber>());
  rclcpp::shutdown();
  return 0;
}