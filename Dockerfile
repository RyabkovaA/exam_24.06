FROM ubuntu

LABEL author = "Anna Ryabkova"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools -y
RUN apt-get install build-essential -y
RUN apt-get install -y gcc

WORKDIR /MyProj_<221-3210>_<Ryabkova>
COPY *.cpp .
COPY *.sln .


RUN cmake ..
RUN make

ENTRYPOINT ["./Project4"]
