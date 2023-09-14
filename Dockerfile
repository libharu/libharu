FROM gcc

RUN apt-get update; apt-get -y install cmake

COPY . /usr/src/libharu/src

RUN mkdir /usr/src/libharu/build
RUN cd /usr/src/libharu/build; cmake ../src -DLIBHPDF_EXAMPLES=ON
RUN cd /usr/src/libharu/build; make