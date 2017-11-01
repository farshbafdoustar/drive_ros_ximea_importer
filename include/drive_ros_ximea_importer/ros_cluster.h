/******************************************************************************

Copyright 2016  Abdelhamid El-Bably (University of Waterloo)
                      [ahelbably@uwaterloo.ca]
                Arun Das (University of Waterloo)
                      [adas@uwaterloo.ca]
                Michael Tribou (University of Waterloo)
                      [mjtribou@uwaterloo.ca]
                Simon Schulz (University of Bielefeld)
                      [sschulz@techfak.uni-bielefeld.de]

All rights reserved.

********************************************************************************/
#ifndef INCLUDE_XIMEA_CAMERA_ROS_CLUSTER_H_
#define INCLUDE_XIMEA_CAMERA_ROS_CLUSTER_H_

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <dynamic_reconfigure/Config.h>
#include <drive_ros_ximea_importer/ros_driver.h>

#include <string>
#include <vector>

namespace ximea_camera {

class RosCluster {
 public:
    explicit RosCluster(int num_cams);
    explicit RosCluster(std::vector < std::string > filenames);
    void addCamera(boost::shared_ptr<RosDriver> xd);
    void removeCamera(std::string serial_no);

    // cluster functions
    void clusterInit();
    void clusterAcquire();
    void clusterPublishImages();
    void clusterPublishCamInfo();
    void clusterPublishImageAndCamInfo();
    void clusterEnd();

    bool isDeviceOpen() {
        return devices_open_;
    }

    // individual camera functions (encapsulated for thread security)
    void setImageDataFormat(std::string serial_no, std::string s);

 private:
    int getCameraIndex(std::string serial_no);

    std::vector<boost::shared_ptr<RosDriver> > cams_;
    std::vector<boost::thread*> threads_;
    bool devices_open_;
    int num_cams_;
};

}  // namespace ximea_camera

#endif  // INCLUDE_XIMEA_CAMERA_ROS_CLUSTER_H_
