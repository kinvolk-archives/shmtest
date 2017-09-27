FROM alpine:3.5

ADD shmtest /bin

ENTRYPOINT ["/bin/shmtest"]

