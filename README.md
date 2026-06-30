# INS-Nav0
Inertial Navigation System (INS) is an early Navigation method used by fighter jet to navigate without GPS "satellite" this project use the same principle
This device that i made will take you to any place on earth with no gps help or anything its relying only on math just like the old way 
i made this to learn more about ins and how does it work 

# PCB
i made a pcb to connect all the component together i choose an **ESP-32** to do the heavy math and for battery i picked a powerbank with usb-c connection 

## Schematics 
<img width="1675" height="1190" alt="schem" src="https://github.com/user-attachments/assets/89362132-34cb-49ba-8c3a-1f11e5d31108" />


## Routing 

<img width="1069" height="587" alt="pcb" src="https://github.com/user-attachments/assets/4c112cb3-776b-4440-8f6a-9d9f8ca4f7ae" />

## 3D render 

<img width="918" height="533" alt="3d" src="https://github.com/user-attachments/assets/b5c84ba5-475f-4bb5-86c4-c0f3f148c571" />


# CAD 
I optimized the enclosure to be as aesthetic as possible and reliable ( withstand some falls ) but also easy to walk with 
i used one stepper motor althought i have 3 more stepper inputs available it include a keyboard where you can put your coordinate to get a heading 

<img width="770" height="651" alt="ren" src="https://github.com/user-attachments/assets/a9a88d28-2abf-406c-9b48-636dd6a81124" />

---

# How It Works 

The firmware runs a high frequency loop that translates your physical movement into global coordinates:
1. The **PMW3901** tracks relative movement counts, which are scaled into millimeter deltas.
2. The **Magnetometer** samples the exact yaw heading angle  relative to magnetic North.
3. The ESP32 do the complicated math 

---

# How to Use It 
1. Power on the INS Nav0.
2. Type in your destination coordinates using the integrated keypad.
3. Walk forward the mechanical arrow will dynamically adjust to show your true target heading.
4. Arrive at your destination without a single GPS satellite packet!

## Wire Diagram 
<img width="1366" height="768" alt="wire" src="https://github.com/user-attachments/assets/76ff66cd-c929-404e-bad5-c698ce4b6dda" />
