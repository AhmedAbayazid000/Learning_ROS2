#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;


int main (int argc, char **argv){
    rclcpp::init(argc,argv);   
    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client_no_oop");
    // Create a client for the "add_two_ints" service
    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    // Wait for the service to be available if after 1 second it is not available, print a warning message
    while(!client->wait_for_service(1s))
    {
        RCLCPP_WARN(node->get_logger(), "Waiting for the server");
    }

    //send the request to the server and get the response
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 66;
    request->b =4;

    // Send the request asynchronously and get a future for the response
    auto future = client->async_send_request(request);
    //spin until that future is filled/complete
    rclcpp::spin_until_future_complete(node, future);

    auto response = future.get();
    RCLCPP_INFO(node->get_logger(), "%d + %d = %d", (int)request->a, (int)request->b, (int)response->sum);


    rclcpp::shutdown();
    return 0;
}