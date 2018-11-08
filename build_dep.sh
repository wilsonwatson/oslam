project_dir=$(readlink -f $(dirname "$0"))
git clone https://github.com/raulmur/ORB_SLAM2 $project_dir/sourcing
cp -rf $project_dir/sourcing/Thirdparty $project_dir
cp -rf $project_dir/sourcing/Vocabulary $project_dir
rm -rf $project_dir/sourcing
cd $project_dir/Vocabulary; tar xzf ORBvoc.txt.tar.gz
cd $project_dir; patch Thirdparty/DBoW2/DBoW2/TemplatedVocabulary.h TemplatedVocabulary.patch
cd $project_dir/Thirdparty/DBoW2/; mkdir build; cd build; cmake ..; make
cd $project_dir/Thirdparty/g2o/; mkdir build; cd build; cmake ..; make
cd $project_dir; mkdir build; cd build; cmake ..; make
cd $project_dir; ./tools/bin_vocabulary
echo "Build finished. Use the scripts in $project_dir/run"
