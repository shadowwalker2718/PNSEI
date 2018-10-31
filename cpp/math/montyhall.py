from random import randint

class MontyHall(object):
    def run(self):
        doors = [0]*4 + [1]
        # a manul shuffling algo or you can use random.shufffle(list)
        def shuffle(doors):
            for i in range(0,len(doors)):
                j = i + randint(0,100000) % (len(doors)-i)
                doors[i], doors[j] = doors[j], doors[i]
            return doors
        c1, c2, MC = 0, 0, 100000
        for i in range(MC):
            shuffle(doors)
            # no switch
            c1 += (doors[0] == 1)
            # switch
            for j in range(1, len(doors)):
                if doors[j]==0:
                    doors[j], doors[-1] = doors[-1], doors[j]
                    break
            c2 += (doors[randint(1,3)] == 1)####!!!!
        return 1.0*c1/MC, 1.0*c2/MC
mh = MontyHall()
print mh.run()
