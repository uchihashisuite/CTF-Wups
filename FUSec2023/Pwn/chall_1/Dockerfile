FROM ubuntu:22.04

RUN apt-get update && apt-get install -y socat
RUN useradd -UM chall

RUN mkdir -p /app

COPY chall /app
COPY flag.txt /app
COPY socat.sh /app
RUN chmod +x /app/socat.sh
RUN chmod +x /app/chall

WORKDIR /app

CMD /app/socat.sh