#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hard_ware_status.hpp"

using namespace std::chrono_literals;

class HardWareStatusPublisherNode : public rclcpp::Node {  
public:
    HardWareStatusPublisherNode() : Node("hardware_status_publisher")
    {
        //This line creates the publisher object. template is "create_publisher<Msg_type>("Topic_name", queue_size)". The queue size is the number of messages that can be stored in the publisher's buffer before they are sent to subscribers.
        publisher_= this->create_publisher<my_robot_interfaces::msg::HardWareStatus>("hardware_status", 10);
        timer_=this->create_wall_timer(1s, std::bind(&HardWareStatusPublisherNode::publishStr, this));
        RCLCPP_INFO(this->get_logger(), "Hardware Status Publisher Node has been started"); 
        
        
    }
 
private:
    ///Create a message and send it using the publisher object.
    void publishStr()
    {
        //Creates and empty message of type std_msgs:msg:Int32
        auto msg= my_robot_interfaces::msg::HardWareStatus();
        msg.temperature = 26.5;
        msg.are_motors_ready = true;
        msg.debug_message = "Everything is fine";
        //Sends the message to the topic
        publisher_->publish(msg);
    }
    std::string robot_name_;
    //A pointer ot the publisher object, which will be used to publish messages
    rclcpp::Publisher<my_robot_interfaces::msg::HardWareStatus>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    

};



int main (int argc, char **argv){
    rclcpp::init(argc,argv);   
    auto node = std::make_shared<HardWareStatusPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}