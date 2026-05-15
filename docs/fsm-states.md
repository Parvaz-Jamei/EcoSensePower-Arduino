# FSM States

```cpp
enum class EcoState : uint8_t {
  INIT,
  IDLE,
  WAKEUP,
  SENSE,
  PROCESS,
  REPORT,
  SLEEP
};
```

| State | Responsibility |
|---|---|
| INIT | Validate contracts and initialize deadlines |
| IDLE | Find due sensor and next deadline |
| WAKEUP | Run guards and sensor wake callbacks |
| SENSE | Execute read callback |
| PROCESS | Adaptive sampling, budget soft-limit, ledger update |
| REPORT | Report important/first/failure events |
| SLEEP | Run sleep callbacks/guards and call backend |

`node.loop()` may block during backend sleep. This is deliberate for a power runtime and should not be described as an RTOS-like scheduler.
