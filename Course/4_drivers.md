# 4. Drivers

## What Is a Driver?

A driver is the meat and butter of any embedded application. It is the source code describing *how* to interact with your hardware, and without one, you would neither collect any input data, nor have anything to do with your output data. A driver consists of an implementation and an API. The API is the public facing header file describing *what* a category of hardware can do, while the implementation describes *how* it is done by a particular device. Zephyr uses Kconfig and the devicetree to conditionally compile only the implementations for what devices are included in the board definition, creating a driver instance for each physical device. These instances each have their own data and configuration containers, and are, once again, described by the implementation corresponding to each.

## Rationale Behind Separation of API and Implementation

Keeping the driver implementation separate from the application is good
practice in any embedded project. It minimises the potential damage of having
to redo parts of the code in case of hardware replacement, and decouples the
data manipulation and application logic from the low-level device stuff.

More often than not, the application defines the requirements of the hardware,
not the other way around. The application might have need for various
sensor-readings, or access to a motor or servo. The application doesn't care if
these devices are attached to the I²C or SPI bus, analog or digital or the
driving circuitry required for them to function, as long as they fulfil the
requirements set. The hardware is a means to an end, and the application should
only focus on the end. By separating the driver into API and implementation,
the application can utilise the *what*'s provided by the API, rather than the
*how*'s described in the implementation.

This is a somewhat fuzzy and vague section, but will hopefully become clearer
in the next as we move on to

## Next step: [[./5_application.md]]
