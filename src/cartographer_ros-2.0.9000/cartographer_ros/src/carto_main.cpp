/*
 * Copyright 2016 The Cartographer Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <cstdlib>
#include <boost/filesystem.hpp>
#include "carto_slam.h"
#include "gflags/gflags.h"
#include "cartographer_ros/ros_log_sink.h"

int main(int argc, char** argv) {
  std::string log_dir = std::getenv("HOME")
                        + std::string("/log/latest/");
  boost::filesystem::path p(log_dir);
  if (!boost::filesystem::exists(p)) {
    std::cout << 
        "log directory is not exist, trying to create new";
    if (!boost::filesystem::create_directories(p)) {
      std::cout 
        << "Create new log directory failed, saved in HOME.";
      log_dir = std::getenv("HOME");
    } else {
      std::cout << "New log directory created: \n\t" << log_dir; 
    }
  }
  // Init rclcpp first because gflags reorders command line flags in argv
  rclcpp::init(argc, argv, "cartographer_node");

  google::AllowCommandLineReparsing();
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);

  cartographer_ros::ScopedRosLogSink ros_log_sink;
  // cartographer_ros::Run();
  // ::rclcpp::shutdown();

  // ROS_INFO("cartographer version v1.3.1");
  cartographer_ros::CartoSlam cs;
  cs.Run();
}
