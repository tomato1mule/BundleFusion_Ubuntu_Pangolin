# BundleFusion_Ubuntu_Pangolin
This is an ubuntu porting project for [https://github.com/niessner/BundleFusion](https://github.com/niessner/BundleFusion), a GPU-based 3D reconstruction method. 
<br>
<b>Youtube Demo:</b>[https://www.youtube.com/watch?v=QOHhFObUprA](https://www.youtube.com/watch?v=QOHhFObUprA)
<p align="center">
<a href="https://www.youtube.com/watch?v=QOHhFObUprA
" target="_blank"><img src="asset/demo_office2.png"
alt="demo for BundleFusion_Ubuntu" width="720" height="540" /></a>
</p>



```
@article{dai2017bundlefusion,
  title={BundleFusion: Real-time Globally Consistent 3D Reconstruction using On-the-fly Surface Re-integration},
  author={Dai, Angela and Nie{\ss}ner, Matthias and Zoll{\"o}fer, Michael and Izadi, Shahram and Theobalt, Christian},
  journal={ACM Transactions on Graphics 2017 (TOG)},
  year={2017}
}
```
---

## Docker Installation
<b>Update 03/15/2023: We add Docker support for easy usage</b>
Thanks @adizhol add the support for docker, now BundelFusion_Ubuntu_Pangolin can be deployed via docker

Requirements:
* [docker env](https://docs.docker.com/engine/install/ubuntu/)

Find suitable docker image for cuda from here: [https://hub.docker.com/r/nvidia/cudagl/](https://hub.docker.com/r/nvidia/cudagl/)
Recommanded:
* nvidia/cudagl:11.4.0-devel-ubuntu20.04 (for CUDA 11)(test passed!)
* nvidia/cudagl:10.1-devel-ubuntu18.04  (for CUDA 10)(test passed!)
* nvidia/cudagl:10.0-devel-ubuntu16.04 (for CUDA 10)(test passed!)
* nvidia/cudagl:9.1-devel-ubuntu16.04 (for CUDA 9)

```bash
sudo docker pull nvidia/cudagl:11.4.0-devel-ubuntu20.04
```

### Build:
```
docker build -t bundlefusion-cu11.4-cudagl:latest .
```

### Run Docker:
```bash
bash ./run_docker.sh
```

### Install Mamba:
```bash
wget https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-Linux-x86_64.sh
bash Mambaforge-Linux-x86_64.sh 
```

### Install Additional Packages
```bash
apt-get install -y libcanberra-gtk-module libcanberra-gtk3-module
apt-get install lsb -y
```

<!-- ### Configure Env Variables
```bash
echo "export NO_AT_BRIDGE=1" >> ~/.bashrc
``` -->

### Install pybind:
```bash
mamba install -c conda-forge pybind11
```

### Install Python Dependencies:
```bash
pip install opencv-python
```

### (Optional) Install Realsense SDK
```bash
mkdir -p /etc/apt/keyrings
curl -sSf https://librealsense.intel.com/Debian/librealsense.pgp | tee /etc/apt/keyrings/librealsense.pgp > /dev/null
apt-get install apt-transport-https lsb-release

echo "deb [signed-by=/etc/apt/keyrings/librealsense.pgp] https://librealsense.intel.com/Debian/apt-repo `lsb_release -cs` main" | tee /etc/apt/sources.list.d/librealsense.list
apt-get update

apt-get install librealsense2-dkms librealsense2-utils librealsense2-dev librealsense2-dbg
pip install pyrealsense2
```

## Troubleshooting
1. If you get `Authorization required, but no authorization protocol specified`, run the following command in your host (not in docker container)
```shell
xhost -local:root
```

2. Please check that if your host PC is using supported linux kernel for realsense.

---


## Local Installation

This code is tested under ubuntu16.04/GCC7/CUDA10.1 (GPU: RTX2060).

Requirements:

* CMake
* Eigen 3.1.0
* NVIDIA CUDA 9.0/10.+
* OpenCV

Optional:

* Pangolin

```
mkdir build && cd build
cmake -DVISUALIZATION=ON ..
make -j8
```

We use -DVISUALIZATION=OFF/ON to switch visualization plug.

## Usage

* Download datasets from BundleFusion project mainpage [http://graphics.stanford.edu/projects/bundlefusion/](http://graphics.stanford.edu/projects/bundlefusion/) and unzip it.
* Run Commands:

```
cd build
./bundle_fusion_example ../zParametersDefault.txt ../zParametersBundlingDefault.txt /PATH/TO/dataset/office2
```

A pangolin window will show up and get real time reconstruction  result.

* Save Mesh:

we provide save mesh button at pangoln GUI, you need to specify the save path at zParametersDefault.txt for item "s_generateMeshDir".



## Result

We provide a reconstruction result of dataset [office2](http://graphics.stanford.edu/projects/bundlefusion/data/office2/office2.zip) with Google Drive: [https://drive.google.com/file/d/121rR0_6H_xTpsSsYAHIHV_sZqJjHdN5R/view?usp=sharing](https://drive.google.com/file/d/121rR0_6H_xTpsSsYAHIHV_sZqJjHdN5R/view?usp=sharing)



## Issues

* Pangolin OpenGL error:

<b>Problem:</b>

```
/usr/local/include/pangolin/gl/glsl.h:709:70: error: ‘glUniformMatrix3dv’ was not declared in this scope
     glUniformMatrix3dv( GetUniformHandle(name), 1, GL_FALSE, m.data());
                                                                      ^
/usr/local/include/pangolin/gl/glsl.h: In member function ‘void pangolin::GlSlProgram::SetUniform(const string&, const Matrix4d&)’:
/usr/local/include/pangolin/gl/glsl.h:713:70: error: ‘glUniformMatrix4dv’ was not declared in this scope
     glUniformMatrix4dv( GetUniformHandle(name), 1, GL_FALSE, m.data());
```

<b>Solution:</b>

```
sudo vim /usr/local/include/pangolin/gl/glplatform.h
#goto line#58
#replace "GL/glew.h" with "/usr/include/GL/glew.h"
```

## Contact

contact with fangasfrank #at gmail.com for porting issues.
