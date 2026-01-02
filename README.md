# informer ‽

a minimalist, hardware-accelerated overlay tool for linux. 
renders text using glfw3 and freetype2 directly over your desktop windows.

## features
- **transparent overlay:** floats over everything (x11/wayland-layer).
- **custom fonts:** support for any `.ttf` via freetype2.
- **fade-in/out:** smooth alpha-blending for system notifications.
- **warping (in progress):** sine-wave deformation for organic text movement.

## why?
because standard gui notifications are for landrats. this is for the terminal-bound.

## build
requires: `glfw3`, `freetype2`, `opengl`.

```bash
make
