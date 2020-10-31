FROM alpine

RUN apk add --update \
  bash \
  coreutils \
  g++ \
  make \
  cmake \
  boost-dev \
  git

RUN mkdir /work
COPY . /work
WORKDIR /work

RUN git clone https://github.com/WojciechMigda/Tsetlini.git && \
    cd Tsetlini/.build && \
    git reset df74200 --hard && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -Werror -march=native" .. && \
    make -j 4 install && \
    cd /work

RUN cd kernel/.build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -Werror -march=native -fconcepts" .. && \
    make -j 4 && \
    app/main -h && \
    cd /work

RUN chmod +x build.sh
RUN chmod +x train.sh
RUN chmod +x test.sh
RUN chmod +x infer.sh
RUN chmod +x merge_scores.sh
RUN chmod +x make_submission_txt.sh

#CMD /bin/sh
