from launch import LaunchDescription
from launch_ros.actions import  Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="simple_relay",
            executable="cpp_publisher",
            name="cpp_pub"
        ),
        Node(
            package="simple_relay",
            executable="py_subscriber.py",
            name="py_sub",
            output="screen",
        ),
        Node(
            package="simple_relay",
            executable="intermediate_node",
            name="intermediate",
        )
    ])