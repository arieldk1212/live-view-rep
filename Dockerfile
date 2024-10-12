FROM gcc:latest

RUN apt update -y; \
    apt upgrade -y; \
    apt install -y build-essential libboost-all-dev python3; \
    apt clean -y
ARG CMAKE_VERSION=3.24.2
RUN  apt install -y wget; \
  wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.sh -O cmake.sh; \
  sh cmake.sh --prefix=/usr/local/ --exclude-subdir; \
  rm -rf cmake.sh;

EXPOSE 8080
EXPOSE 5432
EXPOSE 8000
EXPOSE 6060

WORKDIR /live-view

COPY ./src/ ./src/
COPY ./inc/ ./inc/
COPY main.cpp .
COPY ./docker/CMakeLists.txt .

# RUN rm -rf build/*
WORKDIR /live-view/build

RUN cmake ..
RUN make