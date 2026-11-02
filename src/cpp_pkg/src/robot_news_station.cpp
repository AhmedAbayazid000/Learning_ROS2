#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
 
using namespace std::chrono_literals;

class RobotNewsStationNode : public rclcpp::Node 
{
public:
    RobotNewsStationNode() : Node("robot_news_station")
    {
        //This line creates the publisher object. template is "create_publisher<Msg_type>("Topic_name", queue_size)". The queue size is the number of messages that can be stored in the publisher's buffer before they are sent to subscribers.
        publisher_= this->create_publisher<std_msgs::msg::String>("robot_news", 10);
        timer_=this->create_wall_timer(0.5s, std::bind(&RobotNewsStationNode::publishStr, this));
        RCLCPP_INFO(this->get_logger(), "Robot News Station Node has been started"); 
        this->declare_parameter<std::string>("robot_name", "R2D2");
        robot_name_=this->get_parameter("robot_name").as_string();
    }
 
private:
    ///Create a message and send it using the publisher object.
    void publishStr()
    {
        //Creates and empty message of type std_msgs:msg:Int32
        auto msg= std_msgs::msg::String();
        msg.data = "Robot news Station : " + robot_name_ + " is sending news to the smartphone";
        //Sends the message to the topic
        publisher_->publish(msg);
    }
    std::string robot_name_;
    //A pointer ot the publisher object, which will be used to publish messages
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}