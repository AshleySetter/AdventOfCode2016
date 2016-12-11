import pandas
import numpy as np

def FindDistance(filename):
    instructions = np.loadtxt(filename, dtype=str, delimiter=', ')
    Posn = np.array([0.0, 0.0])
    AngleFromNorth = 0
    PosnList = []
    PosnList.append(list(Posn))
    for instruction in instructions:
        instruction = instruction[2:-1].strip() #needed in python3
#        instruction = instruction.strip()
        #print(instruction)
        turnDir = instruction[0]
        if turnDir == 'R':
            AngleFromNorth += np.pi/2
        elif turnDir == 'L':
            AngleFromNorth -= np.pi/2
        DirectionOfTravel = np.array([int(round(np.sin(AngleFromNorth))), int(round(np.cos(AngleFromNorth)))])
        #print(Posn)
        #print(turnDir, AngleFromNorth/np.pi, DirectionOfTravel)
        #print(instruction, instruction[1:], float(instruction[1:]), DirectionOfTravel*float(instruction[1:]))
        Posn += DirectionOfTravel*int(instruction[1:])
        print(Posn, PosnList)
        if list(Posn) in PosnList:
            return Posn[0]+Posn[1]
        PosnList.append(list(Posn))
        
    #print(Posn)
#    return (abs(Posn[0]) + abs(Posn[1]))

# need to include the intermediate steps to get from Posn1 to Posn2 and so on...!!!!!!!!!!!!

dist = FindDistance("input_2.txt")
print(dist)
