FROM gcc:latest

RUN apt update -y; \
    apt upgrade -y; \
    apt install -y \
    build-essential \
    autoconf \
    pkg-config \
    bison \
    flex \
    gcc \
    python3 \
    libc6 \
    zip \
    curl \
    unzip \
    tar \
    g++ \
    git \
    perl \
    bash \
    && apt clean -y

ARG CMAKE_VERSION=3.24.2
RUN  apt install -y wget; \
    wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.sh -O cmake.sh; \
    sh cmake.sh --prefix=/usr/local/ --exclude-subdir; \
    rm -rf cmake.sh;

WORKDIR /usr/local
RUN git clone https://github.com/microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh

EXPOSE 8080 5432 

WORKDIR /live-view

COPY ./src/ ./src/
COPY ./inc/ ./inc/
COPY ./tests/ ./tests/
COPY ./CMakeLists.txt .
COPY ./vcpkg.json .

ENV PATH="/usr/local/vcpkg:${PATH}"

RUN vcpkg install

WORKDIR /live-view/build

RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH=/usr/local/vcpkg/installed/arm64-osx/share -DCMAKE_BUILD_TYPE=Debug
RUN make