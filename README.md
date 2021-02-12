# detourer
Leverage MS Detours for process hooking

Generates a DLL that will hook all the listed functions using provided payloads when loaded into a process.

## Workflow
1. (Optional) Modify/Create custom payloads. Use the existing modules as an example.
2. Move desired payload files to the modules/payloads/build directory.
3. Build. No need to modify anything within Detourer itself.

## Why does this work?
Frankly, magic. The secret sauce of Detourer is largely in the build process and MS Detours is quite legitimate, so there is nothing to signature. 

## Status
This code works great, but there is no guarantee of compatibility across commits.

## Roadmap/TODO
#### One-Time
- [ ] Explore potential for global hooks
  - This would probably need to be adapted for driver use
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
