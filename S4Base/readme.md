# About the library
This library deals with bots having four wheel drive connected in an **S** formation.

## Configurations and convections
### Bot configuration
- Look at the bot from top view
- Top right and bottom left wheels are horizontal
- Top left and bottom right wheels are vertical

### Motion conventions
- Look at the bot from top view
- Motion commands are in polar form
- 0<sup>o</sup> is vertically up, measure angles counter clockwise.
- Length of vector corresponds to PWM (or power). So it's PWM, at direction. Angle convention in degrees (by default).
- A wheel is assumed to be properly connected when it rotates such that it's angular momentum vector points inwards (use right hand thumb rule) when given HIGH on direction pin.

### Debugger
Level 3 - Verbose
Level 2 - Info
Level 1 - Debug
