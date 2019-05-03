#ifndef CAMERA_THREAD_H_
#define CAMERA_THREAD_H_

#include <opencv/cv.hpp>
#include <csignal>
#include <vector>

static bool should_stop = false;

void sighandler( [[maybe_unused]] int k){
  should_stop = true;
}

template <typename T>
void camera_thread(T& t){
  std::vector<cv::VideoCapture> vcs;
  for(decltype(vcs)::size_type i = 0; i < t.video_id.size(); i++){
    vcs.emplace_back(t.video_id[i]);
    vcs.back().set(CV_CAP_PROP_FOURCC ,CV_FOURCC('M', 'J', 'P', 'G') );
    vcs.back().set(CV_CAP_PROP_FRAME_WIDTH ,640);
    vcs.back().set(CV_CAP_PROP_FRAME_HEIGHT ,480);
  }
  std::vector<cv::Mat> m(vcs.size());
  
  while(!should_stop){
    for(decltype(vcs)::size_type i = 0; i < vcs.size(); i++){
      vcs[i] >> m[i];
      cv::cvtColor(m[i], m[i], cv::COLOR_BGR2GRAY);
    }
    t.GrabImage(m);
  }
}

#endif
