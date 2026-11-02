#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String
 
 
class RobotNewsStation(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("robot_news_station") 
        self.publisher_ = self.create_publisher()
 
 
def main(args=None):
    rclpy.init(args=args)
    node = RobotNewsStation() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()
