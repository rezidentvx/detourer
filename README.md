# detourer
Leverage MS Detours for process hooking

Generates a DLL that will hook all the listed functions when loaded into a process.

## Workflow
1. (Optional) Modify/Create custom payloads per function being hooked. Use the existing modules as an example.
2. Move desired payload files to the modules directory.
3. Build. No need to modify anything within Detourer itself.

## Why does this work?
Frankly, magic. The secret sauce of Detourer is largely in the build process and MS Detours is quite legitimate, so there is nothing to signature. 

## Status
This working alpha code, but can change at any time--Do not expect compatibility between commits.

## Roadmap/TODO
#### One-Time
- [ ] Explore potential for global hooks
  - This would probably need to be adapted for driver use
- [x] Complete and further modularize payloads
- [ ] Configure payloads to interact well with each other
  - Ex. Don’t hook a WriteFile call when we’re trying to exfil data…
- [ ] Add class to generate hook function based on mix/matched choice of:
  - Target function, e.g. VirtualAlloc(…)
  - Payload type (the generic helper wrapper)
  - (optional) Streamlined custom payload function(s) to extend the above
- [ ] Add an attacker project template that allows for zero-knowledge configuration and deployment
- [ ] Fix redundant and bulky #includes
- [ ] Improve backwards compatibility
  - [ ] Port to C
  - [ ] Conform to standard, don’t rely on MS stuff (typedefs, etc.)
  - [ ] Minimize needed Windows SDK version and inclusion/usage
- [ ] Compare runtimes and avoid building from multiple stacks
- [ ] Remove unnecessary items from MS Detours, e.g. sample code, other archs
#### Continuous
- [ ] Add generic payload wrappers to exfil to file/IPC, modify args, etc.
- [ ] Slim down code and PE sizes even more

## Contributing
Pull requests and issues are welcome and appreciated.

## License
CC BY-NC-ND

Case-by-case consideration for:
- CC BY-NC-SA
