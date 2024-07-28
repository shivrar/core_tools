//
// Created by shivan on 7/28/24.
//

#ifndef ACTION_BASE_H
#define ACTION_BASE_H

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

template<typename ActionT>
class BaseActionServer : public rclcpp::Node {
public:
    using GoalHandle = rclcpp_action::ServerGoalHandle<ActionT>;

    BaseActionServer(const std::string & node_name, const std::string & action_name)
    : Node(node_name) {
        using namespace std::placeholders;

        action_server_ = rclcpp_action::create_server<ActionT>(
            this,
            action_name,
            std::bind(&BaseActionServer::handle_goal, this, _1, _2),
            std::bind(&BaseActionServer::handle_cancel, this, _1),
            std::bind(&BaseActionServer::handle_accepted, this, _1));
    }

protected:
    virtual rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const typename ActionT::Goal> goal) = 0;
    virtual rclcpp_action::CancelResponse handle_cancel(std::shared_ptr<GoalHandle> goal_handle) = 0;
    virtual void execute(std::shared_ptr<GoalHandle> goal_handle) = 0;

private:
    void handle_accepted(const std::shared_ptr<GoalHandle> goal_handle) {
        std::thread{std::bind(&BaseActionServer::execute, this, goal_handle)}.detach();
    }

    typename rclcpp_action::Server<ActionT>::SharedPtr action_server_;
};

template<typename ActionT>
class BaseActionClient : public rclcpp::Node {
public:
    using GoalHandle = rclcpp_action::ClientGoalHandle<ActionT>;

    BaseActionClient(const std::string & node_name, const std::string & action_name)
    : Node(node_name), action_name_(action_name) {
        this->client_ptr_ = rclcpp_action::create_client<ActionT>(this, action_name_);
    }

    bool send_goal(typename ActionT::Goal & goal) {
        if (!this->client_ptr_->wait_for_action_server(std::chrono::seconds(10))) {
            RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
            return false;
        }


        typename rclcpp_action::Client<ActionT>::SendGoalOptions send_goal_options;
        send_goal_options.goal_response_callback =
          std::bind(&BaseActionClient::goal_response_callback, this, std::placeholders::_1);
        send_goal_options.feedback_callback =
          std::bind(&BaseActionClient::feedback_callback, this, std::placeholders::_1, std::placeholders::_2);
        send_goal_options.result_callback =
          std::bind(&BaseActionClient::result_callback, this, std::placeholders::_1);

        this->client_ptr_->async_send_goal(goal, send_goal_options);
        return true;
    }

protected:
    virtual void goal_response_callback(const typename GoalHandle::SharedPtr & goal_handle) = 0;
    virtual void feedback_callback(typename GoalHandle::SharedPtr, std::shared_ptr<const typename ActionT::Feedback> feedback) = 0;
    virtual void result_callback(const typename GoalHandle::WrappedResult & result) = 0;

private:
    std::string action_name_;
    typename rclcpp_action::Client<ActionT>::SharedPtr client_ptr_;
};

#endif //ACTION_BASE_H
