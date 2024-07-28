//
// Created by shivan on 7/28/24.
//

#include <example_interfaces/action/fibonacci.hpp>
#include "base_classes/action_base.h"

class MyActionClient : public BaseActionClient<example_interfaces::action::Fibonacci> {
public:
    MyActionClient()
    : BaseActionClient("my_action_client", "my_action") {}

protected:
    void goal_response_callback(const GoalHandle::SharedPtr & goal_handle) override {
        if (!goal_handle) {
            RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
        } else {
            RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
        }
    }

    void feedback_callback(GoalHandle::SharedPtr, const std::shared_ptr<const example_interfaces::action::Fibonacci::Feedback> feedback) override {
        RCLCPP_INFO(this->get_logger(), "Next number in sequence: %d", feedback->sequence.back());
    }

    void result_callback(const GoalHandle::WrappedResult & result) override {
        switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            RCLCPP_INFO(this->get_logger(), "Goal succeeded");
            break;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_INFO(this->get_logger(), "Goal was canceled");
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_INFO(this->get_logger(), "Goal was aborted");
            break;
        default:
            RCLCPP_INFO(this->get_logger(), "Unknown result code");
            break;
        }
    }
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyActionClient>();

    example_interfaces::action::Fibonacci::Goal goal;
    // Set goal parameters here
    node->send_goal(goal);

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
