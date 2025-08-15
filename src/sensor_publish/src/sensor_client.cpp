#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"
class SensorClient:public rclcpp::Node{
    public:
        SensorClient():Node("sensorClient"){
            client_ = create_client<std_srvs::srv::SetBool_Request>("sensorService");
        }
    private:
        rclcpp::Client<std_srvs::srv::SetBool_Request>::SharedPtr client_;


};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    std::shared_ptr<SensorClient> client = std::make_shared<SensorClient>();
    while (true)
    {
        /* code */
    }
    

    

    rclcpp::shutdown();
    return 0;
}
