FROM ubuntu:22.04

RUN apt-get update && \
    apt-get upgrade && \
    apt-get install \
        python3 \
        curl \
        zip \
        unzip \
        tar \
        git \
        bash \
        g++ \
        libstdc++ \
        libc-dev 

ARG CMAKE_VERSION=3.24.2
RUN curl -L https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz | tar --strip-components=1 -xz -C /usr/local

WORKDIR /usr/local
RUN git clone https://github.com/microsoft/vcpkg.git && \
    vcpkg/bootstrap-vcpkg.sh

EXPOSE 8080 5432 

WORKDIR /live-view

COPY ./src/ ./src/
COPY ./inc/ ./inc/
COPY ./CMakeLists.txt .
COPY ./vcpkg.json .

ENV PATH="/usr/local/vcpkg:${PATH}"

RUN vcpkg install

WORKDIR /live-view/build

RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH=/usr/local/vcpkg/installed/arm64-osx/share -DCMAKE_BUILD_TYPE=Release
RUN make