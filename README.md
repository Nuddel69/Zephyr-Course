# Zephyr Course

This repository contains both the course material and the finished blinky application. The application is meant as a reference in case of issues, *not* a replacement for following the course!

Find the course at <https://nuddel69.github.io/Zephyr-Course/>, or start reading at `docs/intro-course/0_overview.mdx`
The course begins at [overview](Course/0_overview.md)

The blinky application can be moved to your zephyr workspace and built with
`west build -b nucleo_h753zi Blinky --
-DDTC_OVERLAY_FILE=boards/nucleo_h753zi.overlay`

> [!TIP]
> Lacking stimulation? No pictures? The text is broken at 80 characters and can
> comfortably be viewed at half a screen. Split your screen, and you'll have
> room for subway surfers (or a code editor…) at the other half!
