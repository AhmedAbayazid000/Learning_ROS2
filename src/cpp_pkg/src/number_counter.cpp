#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int32.hpp"


using namespace std::placeholders;
using namespace std::chrono_literals;

class Number_Counter : public rclcpp::Node 
{
public:
    Number_Counter() : Node("number_counter") 
    {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int32>(
            "/number", 10,
             std::bind(&Number_Counter::callbackNumber, this, _1));
            publisher_ = this->create_publisher<example_interfaces::msg::Int32>("/number_count", 10);
        RCLCPP_INFO(this->get_logger(), "Number counter Node has been started");
    }

private:
    void callbackNumber(const example_interfaces::msg::Int32::SharedPtr msg){
    RCLCPP_INFO(this->get_logger(), "%d", msg->data);
    counter_++;
    publishInt32();
}
    void publishInt32()
    {
        //Creates and empty message of type std_msgs:msg:Int32
        auto msg= example_interfaces::msg::Int32();
        msg.data = counter_;
        //Sends the message to the topic
        publisher_->publish(msg);
    }

    int counter_=0;
    rclcpp::Subscription<example_interfaces::msg::Int32>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int32>::SharedPtr publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Number_Counter>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}