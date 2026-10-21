# Convex-Hull Server: from Reactor to Proactor

![C++17](https://img.shields.io/badge/C++17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![POSIX Threads](https://img.shields.io/badge/POSIX-pthreads-555555?style=flat-square)
![TCP](https://img.shields.io/badge/TCP-sockets-555555?style=flat-square)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black)

An interactive convex-hull service in **C++17** that grows over 10 stages, from a single-process algorithm into a concurrent network server. Each stage adds one systems concept, so the repository reads as a hands-on tour of server design.

## Stages

| Stage | What it adds | Key concepts |
|:--:|:--|:--|
| 1 | Convex hull of a point set | Computational geometry |
| 2 | Two implementations, `std::list` vs `std::deque`, with timing | Data-structure performance (`std::chrono`) |
| 3 | Interactive commands (`Newgraph`, `Newpoint`, `Removepoint`, `CH`) | Command parsing, state management |
| 4 | Multi-client TCP server and client | Sockets, shared state |
| 5 | **Reactor** library, built as static and shared libraries | Event demultiplexing, callbacks, `extern "C"` API |
| 6 | Server rebuilt on top of the Reactor | Event-driven I/O |
| 7 | Thread-per-client server | `pthreads`, mutex-protected shared graph |
| 8 | **Proactor** library (`startProactor` / `stopProactor`) with a demo server | Thread-per-connection completion handling |
| 9 | Stage-7 shared-state server rebuilt on top of the Proactor | Proactor pattern in practice |
| 10 | **Producer-consumer** area monitor | `pthread_cond_t`, atomics, graceful `SIGINT`/`SIGTERM` shutdown |

## Quick start (stage 10)

```bash
cd stage10
make
./server_proactor &
echo "Newgraph 4 0,0 15,0 15,15 0,15" | nc localhost 9034
echo "CH" | nc localhost 9034
# server console → "At Least 100 units belongs to CH"
```

Every stage has its own `Makefile`. Stage 10 also ships an automated test script, `test_stage10.sh`.
