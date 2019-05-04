#!/bin/bash

project_dir=$(readlink -f $(dirname "$0"))

mkdir -p $project_dir/Thirdparty/g2o/build
cd $project_dir/Thirdparty/g2o/build; cmake ..; make -j3

mkdir -p $project_dir/Thirdparty/DBoW2/build
cd $project_dir/Thirdparty/DBoW2/build; cmake ..; make -j3

mkdir -p $project_dir/build
cd $project_dir/build; cmake ..; make -j3
