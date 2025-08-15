#include <iostream>
#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;
class SensorClientNode:public rclcpp::Node{
    public:
        SensorClientNode():Node("sensorClient"){
            client_ = create_client<std_srvs::srv::SetBool_Request>("sensorService");
            
        }
        
        rclcpp::Client<std_srvs::srv::SetBool_Request>::SharedPtr client_;


};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    std::shared_ptr<SensorClientNode> clientNode = std::make_shared<SensorClientNode>();
    auto request = std::make_shared<std_srvs::srv::SetBool_Request>();

    while (true)
    {   std::string str;
        std::cout<<"문자열을 입력하세요"<<std::endl;
        std::cin>>str;

        if (str !="")
        {
            request->data =true;
        }
        else{
            request->data=false;
        }

        while (!clientNode->client_->wait_for_service(1s))
        {
            if (!rclcpp::ok()) // not given shared ptr
            {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"Interrupted while waiting for the service. Exiting.");
                return 0;
    
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
        }
        
        
        auto result = clientNode->client_->async_send_request(request);
        if (rclcpp::spin_until_future_complete(clientNode,result) == rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %s", result.get()->message);
           
        }
        else{
             RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call Sensor service");
        }
        
    
    }
    

    

    rclcpp::shutdown();
    return 0;
}
