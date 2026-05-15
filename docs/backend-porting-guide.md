# Backend Porting Guide

Backends must remain isolated under `src/arch/<architecture>` and guarded by architecture macros.

Rules:

- do not include architecture-specific headers in core,
- compile-safe fallback is better than unsafe sleep claims,
- document wake source limitations,
- do not manipulate fuses or irreversible board configuration,
- use `PowerDoctor` diagnostics for missing or approximate backends.
