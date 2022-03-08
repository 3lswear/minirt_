# MiniRT
A compact raytracer for X Window System written in C

![Screenshot](https://i.imgur.com/pVBaF7V.png)

Requires MiniLibX for Linux to work.

### Requirements

---

MiniLibX dependencies:

- Ubuntu (or Debian-based): 
  - libbsd: `sudo apt install libbsd libbsd-dev`
  - X11 headers: `sudo apt install xorg libxext-dev zlib1g-dev`

- Fedora (or RPM-based):
  - libbsd: `sudo dnf install libbsd libbsd-devel`
  - X11 headers: `sudo dnf group install "X Software Development"`


### Installation

---

clone with submodules:

````
git clone --recursive https://github.com/3lswear/minirt_
````

```
cd minirt_ && make
```

### Usage

---

Pass a path to a scene file as an argument to the executable:

```
./miniRT maps/spheres_plane_color_lights.rt
```

#### Keyboard bindings:

`Q` /`ESC`to quit,

`SPACE` to switch cameras if there are more than one.

**Some demo scenes are located in `maps` folder.**

### Configuration file (scene)

---

```conf
# Set window resolution
R	1366 768

# Set ambient lighting intensity and RGB color (only one)
A	0.7 255,255,255

# Add one or more cameras by setting:
# coords of a view point, normalized orientation vector, FOV
c	0,0,0 0,0,1 90

# Set up shapes such as:
# Sphere (coords of the center, diameter, color):
sp	-2,-2,-8 4 51,150,51

# Plane (coords of any point on a plane, normalized orientation vector, color):
pl	0,-15,0 0,1,0 50,50,255

# Cylinder (center coords, normalized orientation vector, diameter, length, color):
cy	0,-2,-10 0,0,1 3 14 200,200,200

# Square (center coords, normalized orientation vector, side length, color):
sq	0,-9.9,2 0,1,0 5 200,200,50

# Triangle (coords of all three points, color):
tr	1,-10,0 -1,-10,0 0,-10,-6 255,50,50
```

