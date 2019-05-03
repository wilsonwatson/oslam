#!/bin/bash

project_dir=$(readlink -f $(dirname "$0"))/..

gdb --args $project_dir/oslam_stereo $project_dir/Vocabulary/ORBvoc.bin $project_dir/configs/TUM1.yaml
