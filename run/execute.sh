#!/bin/bash

project_dir=$(readlink -f $(dirname "$0"))/..

$project_dir/ORB_SLAM2_noros_exe $project_dir/Vocabulary/ORBvoc.bin $project_dir/Examples/Monocular/TUM1.yaml
