/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include <Eigen/Eigen>

#include<opencv2/core/core.hpp>

#include "camera_thread.h"

#include"System.h"

using namespace std;

static decltype(std::chrono::high_resolution_clock::now()) start_time;

std::ofstream mtransform;

double running_time = 0;

class ImageGrabber
{
public:
    ImageGrabber(ORB_SLAM2::System* pSLAM):mpSLAM(pSLAM){}

    void GrabImage(const cv::Mat& image);

    ORB_SLAM2::System* mpSLAM;
    
    int video_id;
};

void printall(ORB_SLAM2::System* sys, Eigen::Vector3f tran, Eigen::Quaternionf rot, [[maybe_unused]] double dt){
  mtransform << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count() << " " << tran.x() << " " << tran.y() << " " << tran.z() << " " << rot.w() << " " << rot.x() << " " << rot.y() << " " << rot.z() << "\n";
  /*
  for(auto point : sys->GetTrackedMapPoints()){
    if(point->isBad()) continue;
    //auto pos = point->GetWorldPos();
    //pos.at<float>(0),pos.at<float>(1),pos.at<float>(2);
  }
  */
}

void printstatus(std::string s){
  std::cout << s << std::endl;
}

int main(int argc, char **argv)
{
    mtransform.open ("path.txt");
    start_time = std::chrono::high_resolution_clock::now();
    if(argc != 3)
    {
        cerr << endl << "Usage: ./Mono path_to_vocabulary path_to_settings" << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    // ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR, true);
    
    SLAM.func() = printall;
    
    SLAM.status_func() = printstatus;

    ImageGrabber igb(&SLAM);
    
    igb.video_id = 0;
    
    signal(SIGINT, sighandler);
    
    camera_thread(igb);

    // Stop all threads
    SLAM.Shutdown();

    return 0;
}

void ImageGrabber::GrabImage(const cv::Mat& image)
{
    mpSLAM->TrackMonocular(image,std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count());
}


