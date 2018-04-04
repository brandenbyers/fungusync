# Mushroom Environment Tracker

_This is a work in progress..._

Have you dabbled in mushroom hunting but mostly come back empty handed? Do you envy those that come home with bags full of morels, chanterelles, or `<insert your favorite mushroom here>`? Maybe you don't quite grasp the science or mysteryaround when and where mushrooms grow? Or maybe you're pretty good at finding mushrooms, but you would like to up your odds?

The Mushroom Environment Tracker (MET) is a prototype device that can be used to detect ideal growing conditions for mushrooms. If you find a good spot where mushrooms grow, you can "plant" an MET and leave it behind. Environment data (humidity, temperature, barometric pressure, and soil moisture) is tracked and sent via M2M SMS messages over LTE NB-1 (once available; for now it is 2G or 3G). This allows for year long battery life. Leave the device and forget it until a specified threshold is met, at which point you will be notified of potential mushroom growth due to ideal environmental factors.

## Hardware

- Particle Electron (temporary proof-of-concept solution using 2G/3G)
- Twilio SIM (for M2M)
- BME280 sensor (humidity, temperature, and pressure)
- Soil Moisture Sensor

## Caveats

This is currently in a pre-alpha state. Much work is still needed.

In the US, LTE NB-1 network infrastructure is still being rolled out. Until then, it will not be feasible to build this device with long battery life. 2G and 3G will devour batteries compared to LTE NB-1. Until LTE NB-1 (or alternatively Cat M1) is established, this will remain a proof-of-concept. In other parts of the world, this could be adapted new hardware and this could move beyond proof-of-concept faster.

## Todo

A lot. :)
