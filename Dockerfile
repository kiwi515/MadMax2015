FROM ubuntu:12.04

# =============================================================================
#
# configure apt
#
# =============================================================================

# avoid debconf warnings
ARG DEBIAN_FRONTEND=noninteractive

# use EOL package repositories
RUN sed -i \
    -e 's|http://archive.ubuntu.com/ubuntu|http://old-releases.ubuntu.com/ubuntu|g' \
    -e 's|http://security.ubuntu.com/ubuntu|http://old-releases.ubuntu.com/ubuntu|g' \
    /etc/apt/sources.list

RUN apt-get update && apt-get dist-upgrade -y

# common dependencies + utilities
RUN apt-get install -y \
    build-essential \
    bzip2 \
    curl \
    make \
    vim

# =============================================================================
#
# build OpenSSL 1.1.1 (for Python)
#
# =============================================================================

WORKDIR /tmp

# OpenSSL library version
ARG OPENSSL_VER=1.1.1w

# build dependencies
RUN apt-get install -y \
    perl \
    perl-modules \
    zlib1g-dev

# download source code
RUN curl --fail --location \
    "https://www.openssl.org/source/openssl-${OPENSSL_VER}.tar.gz" \
    -o "openssl.tar.gz"

RUN tar -xf "openssl.tar.gz"

# bootstrap
WORKDIR /tmp/openssl-${OPENSSL_VER}
RUN ./config \
    --prefix=/opt/openssl-${OPENSSL_VER} \
    --openssldir=/opt/openssl-${OPENSSL_VER}/ssl \
    # make shared objects
    shared \
    # tls support
    zlib

# compile and install
RUN make -j$(nproc) && make test && make install_sw

# add to path
ENV PATH="/opt/openssl-${OPENSSL_VER}/bin:${PATH}"
ENV LD_LIBRARY_PATH="/opt/openssl-${OPENSSL_VER}/lib:${LD_LIBRARY_PATH}"
ENV PKG_CONFIG_PATH="/opt/openssl-${OPENSSL_VER}/lib/pkgconfig:${PKG_CONFIG_PATH}"

# install SSL certs
ENV SSL_CERT_FILE=/etc/ssl/certs/ca-certificates.crt
ENV SSL_CERT_DIR=/etc/ssl/certs
RUN apt-get install -y ca-certificates && update-ca-certificates

# =============================================================================
#
# build Python
#
# =============================================================================

WORKDIR /tmp

# Python interpreter version
ARG PYTHON_VER=3.9.13

# build dependencies
RUN apt-get install -y \
    libbz2-dev \
    libffi-dev \
    libgdbm-dev \
    liblzma-dev \
    libncurses5-dev \
    libreadline6-dev \
    libsqlite3-dev

# download source code
RUN curl --fail --location \
    "https://www.python.org/ftp/python/${PYTHON_VER}/Python-${PYTHON_VER}.tgz" \
    -o "python.tar.gz"

RUN tar -xf "python.tar.gz"

# boostrap
WORKDIR /tmp/Python-${PYTHON_VER}
RUN ./configure \
    --prefix=/opt/python3 \
    --enable-shared \
    --with-ensurepip=install \
    --with-openssl=/opt/openssl-${OPENSSL_VER} \
    --with-openssl-rpath=auto

# compile and install
RUN make -j$(nproc) && make install

# add to path
ENV PATH="/opt/python3/bin:${PATH}"
ENV LD_LIBRARY_PATH="/opt/python3/lib:${LD_LIBRARY_PATH}"

# =============================================================================
#
# build GCC
#
# =============================================================================

WORKDIR /tmp

# GCC compiler version
ARG GCC_VER=4.8.1

# build dependencies
RUN apt-get install -y \
    binutils \
    build-essential \
    ca-certificates \
    flex \
    gawk \
    perl \
    texinfo \
    wget \
    xz-utils

# download source code
RUN curl --fail --location \
    "https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VER}/gcc-${GCC_VER}.tar.bz2" \
    -o "gcc.tar.bz2"

RUN tar -xf "gcc.tar.bz2"

# get prereq libraries
WORKDIR /tmp/gcc-${GCC_VER}
RUN ./contrib/download_prerequisites

# bootstrap
WORKDIR /tmp/gcc-build
RUN ../gcc-${GCC_VER}/configure \
    --prefix=/opt/gcc-${GCC_VER} \
    --disable-multilib \
    --enable-languages=c,c++ \
    --enable-bootstrap

# make and install
RUN make -j$(nproc) && make install

# add to path
ENV PATH="/opt/gcc-${GCC_VER}/bin:${PATH}"
ENV LD_LIBRARY_PATH="/opt/gcc-${GCC_VER}/lib64:/opt/gcc-${GCC_VER}/lib:/opt/python3/lib:${LD_LIBRARY_PATH}"

# =============================================================================
#
# build Boost
#
# =============================================================================

WORKDIR /tmp

# Boost library version
ARG BOOST_VER=1.55.0
ARG BOOST_VER_U=1_55_0

# download source code
RUN curl --fail --location \
    "https://archives.boost.io/release/${BOOST_VER}/source/boost_${BOOST_VER_U}.tar.bz2" \
    -o "boost.tar.bz2"

RUN tar -xf "boost.tar.bz2"

# bootstrap
WORKDIR /tmp/boost_${BOOST_VER_U}
RUN ./bootstrap.sh \
    --prefix=/opt/boost-${BOOST_VER} \
    --with-toolset=gcc

# build and install
RUN ./b2 \
    --build-dir=/tmp/boost-build \
    --prefix=/opt/boost-${BOOST_VER} \
    --without-python \
    -j$(nproc) \
    install

# add to path
ENV BOOST_ROOT="/opt/boost-${BOOST_VER}"
ENV CPLUS_INCLUDE_PATH="/opt/boost-${BOOST_VER}/include"
ENV LIBRARY_PATH="/opt/boost-${BOOST_VER}/lib"

# =============================================================================
#
# MM setup
#
# =============================================================================

ARG NINJA_VER=1.10.2

WORKDIR /mm

# need ninja+yaml for the build system
RUN python3 -m pip install \
    ninja==${NINJA_VER} \
    pyyaml

CMD [ "bash" ]
