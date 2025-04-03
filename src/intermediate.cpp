#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include <chrono>

class IntermediateNode : public rclcpp::Node {
    public:
        IntermediateNode() : Node("intermediate_node")
        {
            subscriber_ = this->create_subscription<std_msgs::msg::String>(
                "topic", 10, std::bind(&IntermediateNode::sub_callback, this, std::placeholders::_1));
            
            publisher_ = this->create_publisher<std_msgs::msg::String>("processed_topic", 10);

            timer_ = this->create_wall_timer(
                std::chrono::milliseconds(500),
                std::bind(&IntermediateNode::pub_callback, this));
        }
    
    private:
        void sub_callback(const std_msgs::msg::String::SharedPtr msg)
        {
            RCLCPP_INFO(this->get_logger(), "Message received: '%s'", msg->data.c_str());
            last_msg_ = msg;
        }
        
        void pub_callback()
        {
            if(!last_msg_) return;

            auto new_msg = std_msgs::msg::String();
            auto timestamp = this->get_clock()->now();
            
            std::time_t now = static_cast<std::time_t>(timestamp.seconds());
            std::tm *now_tm = std::localtime(&now);

            int hours = now_tm->tm_hour;
            int minutes = now_tm->tm_min;
            int seconds = now_tm->tm_sec;

            std::stringstream ss;
            ss << last_msg_->data << "[Processed at " << hours << ":" << minutes << ":" << seconds << "]";
            
            new_msg.data = ss.str();

            publisher_->publish(new_msg);
        }

        std_msgs::msg::String::SharedPtr last_msg_;

        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IntermediateNode>());
    rclcpp::shutdown();
    return 0;
}
