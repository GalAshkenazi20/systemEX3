# Stage 10 - Producer Consumer Pattern

## Overview
Stage 10 adds a **Producer-Consumer pattern** with area monitoring to the Proactor server from Stage 9.

## Key Features

### Producer-Consumer Implementation
- **Producer**: Convex Hull calculations that update the area
- **Consumer**: Area monitoring thread that waits for area changes
- **POSIX Condition Variables**: `pthread_cond_t` for thread synchronization

### Area Monitoring
- Background thread that monitors convex hull area
- Threshold: **100 square units**
- Automatic notifications when crossing the threshold

### Messages
- **"At Least 100 units belongs to CH"** - when area reaches ≥100
- **"At Least 100 units no longer belongs to CH"** - when area drops <100

## Architecture

```
Client Commands → Proactor Threads → Convex Hull Updates → Area Monitor Thread
                                                         ↓
                                                    Condition Variable
                                                         ↓
                                                   Console Notifications
```

## Usage

1. **Start server**: `./server_proactor`
2. **Test manually**: Use `nc localhost 9034` to send commands
3. **Automated test**: `./test_stage10.sh`

## Example Test Case

```bash
# Large area (15x15 = 225 > 100)
echo "Newgraph 4 0,0 15,0 15,15 0,15" | nc localhost 9034
echo "CH" | nc localhost 9034
# Output: "At Least 100 units belongs to CH"

# Small area (1x1 = 1 < 100) 
echo "Newgraph 4 0,0 1,0 1,1 0,1" | nc localhost 9034
echo "CH" | nc localhost 9034
# Output: "At Least 100 units no longer belongs to CH"
```

## Technical Implementation

- **POSIX Threads**: `pthread_create`, `pthread_cond_wait`
- **Atomic Variables**: Thread-safe area updates
- **Mutex Protection**: Synchronized access to shared state
- **Signal Handling**: Graceful shutdown with `SIGINT`/`SIGTERM`
