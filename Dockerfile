FROM ubuntu:focal

RUN apt-get update --fix-missing && \
    DEBIAN_FRONTEND="noninteractive" apt-get install -y \
    gcc \
    clang \
    make
