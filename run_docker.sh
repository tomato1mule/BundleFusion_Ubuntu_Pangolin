xhost local:docker

docker run \
--privileged \
--gpus all \
-e DISPLAY=$DISPLAY \
-e "TERM=xterm-256color" \
--privileged \
--device /dev/dri \
--net=host \
-it \
bundlefusion-cu11.4-cudagl:latest
