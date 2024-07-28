//
// Created by shivan on 7/28/24.
//

#include <example_interfaces/action/fibonacci.hpp>
#include "base_classes/action_base.h"

class MyActionServer : public BaseActionServer<example_interfaces::action::Fibonacci> {
public:
    MyActionServer()
    : BaseActionServer("my_action_server", "my_action") {}

protected:
    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const example_interfaces::action::Fibonacci::Goal> goal) override {
        RCLCPP_INFO(this->get_logger(), "Received goal request");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandle> goal_handle) override {
        RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void execute(const std::shared_ptr<GoalHandle> goal_handle) override {
        RCLCPP_INFO(this->get_logger(), "Executing goal");
        auto result = std::make_shared<example_interfaces::action::Fibonacci::Result>();
        // Do some work here
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyActionServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
