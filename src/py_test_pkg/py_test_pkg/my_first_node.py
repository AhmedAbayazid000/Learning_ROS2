#/usr/bin/env python3
import rclpy
from rclpy.node import Node

class NyNode(Node):
    def __init__(self):
        #constructor of the base class Node is called with the name of the node as an argument
        super().__init__("py_test")
        self.counter_=0
        self.get_logger().info("Hello people ROS2")
        self.create_timer(1.0, self.timer_callback)
    def timer_callback(self):
        self.get_logger().info("Hello"+str(self.counter_))
        self.counter_ +=1



def main(args=None):
    rclpy.init(args=args)
    node = NyNode()
    #The spin() method will keep your node from exiting until the node has been shutdown
    rclpy.spin(node)
    rclpy.shutdown()

if __name__=="__main__":
    main()