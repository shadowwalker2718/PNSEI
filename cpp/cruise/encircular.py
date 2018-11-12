''' https://www.careercup.com/question?id=5653668599693312
A robot on a plane has 2 types of commands:
1. move forward by X units (X is integer 0 <= X <= 10000 )
2. rotate by X degrees (X is integer in range [-180, 180] )
A robot looks like


def robot(commands):
    while True:
        for command in commands:
            execute(command)
Given a list of commands (of size <= 10000) tell if it's possible to build a wall around the robot such that he will never touch it.

Example:


[move(10), rotate(180), move(10)] -> answer is yes
[move(10), rotate(45), move(10), rotate(-45), move(10), rotate(45)]
'''

# Python program to check if the given path for a robot is circular
# or not
N = 0
E = 1
S = 2
W = 3


# This function returns true if the given path is circular,
# else false
def isCircular(path):
    # Initialize starting point for robot as (0, 0) and starting
    # direction as N North
    x = 0
    y = 0
    dir = N

    # Traverse the path given for robot
    for i in xrange(len(path)):

        # Find current move
        move = path[i]

        # If move is left or right, then change direction
        if move == 'R':
            dir = (dir + 1) % 4
        elif move == 'L':
            dir = (4 + dir - 1) % 4

        # If move is Go, then change x or y according to
        # current direction
        else:  # if move == 'G'
            if dir == N:
                y += 1
            elif dir == E:
                x += 1
            elif dir == S:
                y -= 1
            else:
                x -= 1

    return (x == 0 and y == 0)


# Driver program
path = "GLGLGLG"
if isCircular(path):
    print "Given sequence of moves is circular"
else:
    print "Given sequence of moves is NOT circular"
