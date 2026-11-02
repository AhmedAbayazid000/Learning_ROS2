#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int32.hpp"
 
using namespace std::chrono_literals;

class Number_Publisher : public rclcpp::Node 
{
public:
    Number_Publisher() : Node("number_publisher")
    {
        //This line creates the publisher object. template is "create_publisher<Msg_type>("Topic_name", queue_size)". The queue size is the number of messages that can be stored in the publisher's buffer before they are sent to subscribers.
        publisher_= this->create_publisher<example_interfaces::msg::Int32>("/number", 10);
        timer_=this->create_wall_timer(3s, std::bind(&Number_Publisher::publishInt, this));
        RCLCPP_INFO(this->get_logger(), "Number Publisher Node has been started");

    }

private:
    ///Create a message and send it using the publisher object.
    void publishInt()
    {
        //Creates and empty message of type std_msgs:msg:Int32
        auto msg= example_interfaces::msg::Int32();
        msg.data = 10;
        //Sends the message to the topic
        publisher_->publish(msg);
    }
    //A pointer ot the publisher object, which will be used to publish messages
    rclcpp::Publisher<example_interfaces::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Number_Publisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}