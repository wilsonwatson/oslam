#ifndef CAMERA_THREAD_H_
#define CAMERA_THREAD_H_

#include <opencv/cv.hpp>
#include <csignal>

static bool should_stop = false;

void sighandler( [[maybe_unused]] int k){
  should_stop = true;
}

template <typename T>
void camera_thread(T& t){
  cv::VideoCapture cap(t.video_id);
  cap.set(CV_CAP_PROP_FOURCC ,CV_FOURCC('M', 'J', 'P', 'G') );
  cap.set(CV_CAP_PROP_FRAME_WIDTH ,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT ,480);
  cv::Mat m;
  
  while(!should_stop){
    cap >> m;
    cv::cvtColor(m, m, cv::COLOR_BGR2GRAY);
    t.GrabImage(m);
  }
}

#endif
