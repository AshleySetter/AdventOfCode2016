import pandas
import numpy as np

def FindDistance(filename):
    instructions = np.loadtxt(filename, dtype=str, delimiter=', ')
    Posn = np.array([0.0, 0.0])
    AngleFromNorth = 0
    for instruction in instructions:
        instruction = instruction[2:-1].strip() #needed in python3
#        instruction = instruction.strip()
        #print(instruction)
        turnDir = instruction[0]
        if turnDir == 'R':
            AngleFromNorth += np.pi/2
        elif turnDir == 'L':
            AngleFromNorth -= np.pi/2
        DirectionOfTravel = np.array([np.sin(AngleFromNorth), np.cos(AngleFromNorth)])
        #print(Posn)
        #print(turnDir, AngleFromNorth/np.pi, DirectionOfTravel)
        #print(instruction, instruction[1:], float(instruction[1:]), DirectionOfTravel*float(instruction[1:]))
        Posn += DirectionOfTravel*float(instruction[1:])
    #print(Posn)
    return (abs(Posn[0]) + abs(Posn[1]))

dist = FindDistance("input.txt")
print(dist)
