#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class ResetCounterClientNode : public rclcpp::Node {
public:
//Constructor
ResetCounterClientNode() : Node ("reset_counter_client")
{
    client_= this->create_client<example_interfaces::srv::SetBool>("reset_counter");

}
void callResetCounter(bool reset){
    //wait for the service for 1 second
        while (!client_->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server");
        }
    //create the request 
    auto request = std::make_shared<example_interfaces::srv::SetBool::Request>();
    request->data = reset;
    //send the request to the server and get the response
    client_->async_send_request(request,std::bind(&ResetCounterClientNode::callbackCallSetBool,this,_1));


    }

private:
    
//callback function to handle the response 
    void callbackCallSetBool(rclcpp::Client<example_interfaces::srv::SetBool>::SharedFuture future)
    {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Status: %d", (int)response->success);
    }

    rclcpp::Client<example_interfaces::srv::SetBool>::SharedPtr client_;

};



int main (int argc, char **argv){
    rclcpp::init(argc,argv);   
    auto node = std::make_shared<ResetCounterClientNode>();
    node->callResetCounter(true);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}