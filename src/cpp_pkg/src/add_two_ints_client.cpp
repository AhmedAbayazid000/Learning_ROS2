#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class AddTwoIntsClientNode : public rclcpp::Node {
public:
//Constructor
AddTwoIntsClientNode() : Node ("add_two_ints_client")
{
    client_= this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

}
void callAddTwoInts(int a, int b){
    //wait for the service for 1 second
        while (!client_->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server");
        }
    //create the request 
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;
    //send the request to the server and get the response
    client_->async_send_request(request,std::bind(&AddTwoIntsClientNode::callbackCallAddTwoInts,this,_1));


    }

private:
    
//callback function to handle the response 
    void callbackCallAddTwoInts(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future)
    {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Sum: %d", (int)response->sum);
    }

    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;

};



int main (int argc, char **argv){
    rclcpp::init(argc,argv);   
    auto node = std::make_shared<AddTwoIntsClientNode>();
    node->callAddTwoInts(77,23);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}