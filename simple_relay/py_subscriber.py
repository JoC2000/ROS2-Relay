#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class SubscriberNode(Node):
    def __init__(self):
        super().__init__("py_subscriber")

        self.subscription = self.create_subscription(
            String,
            'topic',
            self.listener_callback,
            10)
        
        self.subscription

    def listener_callback(self, msg):
        self.get_logger().info(f"Received message: {msg.data}")

def main(args=None):
    rclpy.init(args=args)

    node = SubscriberNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()