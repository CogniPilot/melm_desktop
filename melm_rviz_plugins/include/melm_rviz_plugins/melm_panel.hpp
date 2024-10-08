#ifndef MELM_RVIZ_PLUGINS_MELM_PANEL_HPP_
#define MELM_RVIZ_PLUGINS_MELM_PANEL_HPP_

#include <rclcpp/subscription_base.hpp>
#include <rviz_common/panel.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <synapse_msgs/msg/status.hpp>
#include <QLabel>

namespace rviz_common {
    class VisualizationManager;
};

class QWidget;
class QLabel;

namespace melm_rviz_plugins
{
class MELMPanel : public rviz_common::Panel
{
    Q_OBJECT
public:
    explicit MELMPanel(QWidget * parent = nullptr);
    virtual void onInitialize();
protected Q_SLOTS:
    void update();
protected:
    QLabel label_arming_;
    QLabel label_fuel_;
    QLabel label_fuel_percentage_;
    QLabel label_input_status_;
    QLabel label_input_source_;
    QLabel label_status_message_;
    QLabel label_safety_;
    QLabel label_power_;
    QLabel label_mode_;
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<synapse_msgs::msg::Status>::SharedPtr sub_status_;
};

}  // namespace melm_rviz_plugins

#endif

// vi: set ts=4 sw=4 et
