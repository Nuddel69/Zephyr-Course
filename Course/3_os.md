# 3. Compiling Your OS

## The Zephyr Kernel

The Zephyr Kernel is a collection of subsystems, modules, drivers, and a
scheduler, separated into kernel space and user space. Kernel space manages
system states and can not be accessed from applications operating in user
space. User space can access kernel functions through syscalls, as is normal in
an operating system.

This is fairly standard, and not something we'll make particularly note of.
What we *do* need to consider, is that zephyr is distributed as source code
only. Every time we edit our application, we also recompile our operating
system. This might seem intimidating, but is actually a great feature of an
embedded RTOS. It allows us to be space- and memory-efficient, by giving us
fine-tuned control of what goes into our operating system. We only compile what
subsystems we need, custom kernel modules are easily integrated and tested.

## Kernel Config

Said configuration of the kernel is done through the kernel config, or
`Kconfig`, language. This is a simple language, allowing for basic
module-structuring and dependencies. The end-user interacts with it as a
collection of variables, usually all caps and prepended with `CONFIG_`, that
are set (often boolean, but also integers and other types) and passed to the
preprocessor as macros. These macros can then be used, either in source code,
or as CMake hints.

### Conditional Compilation

Conditional compolation is what makes kernel config such a powerful tool. CMake
can conditionally include source files, libraries, and directories depending on
whether or not a preprocessor macro is set, allowing your Kconfig options to
control CMake. Furthermore, devicetree can create and set new options based on
the present nodes, meaning you can conditionally choose what
driver-implementations to compile, changing nothing but the devicetree
definition.

## Next Step: [drivers](./4_drivers.md)
