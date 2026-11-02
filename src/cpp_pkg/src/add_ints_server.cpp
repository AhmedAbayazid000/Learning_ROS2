#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::placeholders;

class AddIntServerNode : public rclcpp::Node {
public:
//Constructor
AddIntServerNode() : Node ("add_ints_server")
{
   server_= this->create_service<example_interfaces::srv::AddTwoInts>(
    //Service name 
    "add_two_ints", 
    std::bind(&AddIntServerNode::callbackAddTwoInts, this,_1, _2));
    RCLCPP_INFO(this->get_logger(), "Service add_two_ints has started.");
}
private:
    //you get the request and make the response in the callback function
    void callbackAddTwoInts(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
                            const example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "%d + %d = %d", (int)request->a, (int)request->b, (int)response->sum);

    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;

};



int main (int argc, char **argv){
    rclcpp::init(argc,argv);   
    auto node = std::make_shared<AddIntServerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}