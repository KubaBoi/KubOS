# sudo docker build -t kubos-builder .
# sudo docker run --rm -v "$PWD":/src kubos-builder
# sudo docker rmi $(sudo docker images --filter "dangling=true" -q --no-trunc) -f

FROM ubuntu:22.04

RUN apt update && apt upgrade -y && \
    apt -y install make nasm qemu-system-i386 \
                    dosfstools mtools bochs

WORKDIR /src

COPY docker_entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]