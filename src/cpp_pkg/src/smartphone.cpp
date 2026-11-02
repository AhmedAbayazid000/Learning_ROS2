#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


using namespace std::placeholders;

class SmartphoneNode : public rclcpp::Node 
{
public:
    SmartphoneNode() : Node("smartphone") 
    {
        subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "robot_news", 10,
             std::bind(&SmartphoneNode::callbackRobotNews, this, _1));
        RCLCPP_INFO(this->get_logger(), "Smartphone Node has been started");
    }

private:
    void callbackRobotNews(const std_msgs::msg::String::SharedPtr msg){
    RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
}

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartphoneNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}