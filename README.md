## Symbian C Toolchain for S60 and S^3

This is a new morden toolchain based on reversing work on EKA2L1. Also based on complains about Symbian API design, I have completely change it with the libraries provided with the toolchain, by doing following:
- This libraries with the toolchain is written in C99
- There is no user allocation follow with this library. Libc will do it, and the allocator slot in the thread is replaced with a global struct which contains a static file session, and more. This struct will eats up some first bytes of the heap.
- File session and other session are inherited by default from the parent thread. User can change the session easily by calling API calls.
- Kernel calls are now exposed. You can try out things that you have never done before.

### CMake integration
- This toolchain is using CMake, a morden makefile generator. Using CMake, you can ease your development process many more. ABLD and legacy stuffs are dropped.
- Tools like elf2e32 are reused in this toolchain, you will still have to use def file to frozen your APIs.
- Check out samples to get more about how to use this in your application.

### TODO:
- Debugging library using CODA. Check out Qt's GDBStub, which exposes CODA message structure.
- Executable building.

### Instructions:
- Download arm-none-symbianelf from CodeSourcery (now mentor).
