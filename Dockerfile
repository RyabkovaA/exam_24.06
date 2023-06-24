FROM ubuntu

LABEL author = "Anna Ryabkova"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install build-essential -y
RUN apt-get install cmake -y

WORKDIR /MyProj_<221-3210>_<Ryabkova>
COPY *.cpp .
COPY *.sln .


WORKDIR /MyProj_<221-3210>_<Ryabkova>/build
RUN cmake ..
RUN make

WORKDIR /MyProj_<221-3210>_<Ryabkova>
ENTRYPOINT ["./Project4"]
