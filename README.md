# shmtest

```
make docker
sudo docker run --ipc=host --rm -ti -v /dev/zero:/dev/zero kinvolk/shmtest --token=/dev/zero --read=0 --write=0
```
