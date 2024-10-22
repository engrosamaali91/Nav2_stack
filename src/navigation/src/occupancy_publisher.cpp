#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
// #include "sensor_msgs/msg/laser_scan.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"


using namespace std::chrono_literals;
class OccupancyGridPublisher : public rclcpp::Node
{
  public:
    OccupancyGridPublisher()
    : Node("occupancy_grid_publisher")
    {
      og_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("custom_occupancy_grid", 10);
      og_timer = this->create_wall_timer(500ms, std::bind(&OccupancyGridPublisher::laser_callback, this));
    }
  private:

    void laser_callback()
    {
      std::vector<float> range(100, 10.0f);

      auto og_msg = nav_msgs::msg::OccupancyGrid();
      std::vector<signed char> og_array(35);  // Corrected size to 35
        for (int i = 0; i < 35; i++) {
            og_array[i] = i % 2 == 0 ? 100 : 0;
        }




      og_msg.header.stamp = rclcpp::Clock().now();
      og_msg.header.frame_id = "map_frame";

      og_msg.info.resolution = 1.0;
      og_msg.info.width = 5;
      og_msg.info.height = 7;
      og_msg.info.origin.position.x = 0.0;
      og_msg.info.origin.position.y = 0.0;
      og_msg.info.origin.position.y = 0.0;
      og_msg.info.origin.orientation.x = 0.0;
      og_msg.info.origin.orientation.y = 0.0;
      og_msg.info.origin.orientation.z = 0.0;
      og_msg.info.origin.orientation.w = 1.0;
    //   og_msg.data = {100, 0, 0, -1, -1, 0, 0, 0, 100};
    // we can also loop to generate random map since data is an array 
      og_msg.data = og_array;


      og_publisher->publish(og_msg);
      RCLCPP_INFO(this->get_logger(), "publishing msgs");
    }


    rclcpp::TimerBase::SharedPtr og_timer;
    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr og_publisher;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OccupancyGridPublisher>());
  rclcpp::shutdown();
  return 0;
}