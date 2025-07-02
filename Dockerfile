# sudo docker build -t kubos-builder .
# sudo docker run --rm -v "$PWD":/src kubos-builder
# sudo docker rmi $(sudo docker images --filter "dangling=true" -q --no-trunc) -f

FROM ubuntu:22.04

RUN apt update && apt upgrade -y && \
    apt install make nasm qemu 

WORKDIR /src

CMD ["make"]
#CMD ["qemu", "-kernel", "build/main_floppy.img"]