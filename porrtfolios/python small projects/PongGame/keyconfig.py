import turtle
#This Class helps detect if the key is being hold down or released
class WatchedKey:
    def __init__(self, key):
        self.key = key
        self.down = False
        turtle.onkeypress(self.press, key)
        turtle.onkeyrelease(self.release, key)

    def press(self):
        self.down = True

    def release(self):
        self.down = False
