from player import Player
import random
import time
SPEEDS = [10, 13, 15]
SPEED = 15
CORDS = [0, 90, 180, 270]
OFFSET = 20 # Ball angle variation, higher number prevents straight vertical bouncing
angles = []
for num in range(0, 360):
    if 0 + OFFSET < num < 90 - OFFSET or 90 + OFFSET < num < 180-OFFSET:
        angles.append(num)
    elif 180 + OFFSET < num < 270 - OFFSET or 270 + OFFSET < num < 360-OFFSET:
        angles.append(num)


class Walls(Player):
    def __init__(self):
        super().__init__()
        self.shapesize(stretch_len=40.0, stretch_wid=1.0)
        self.setheading(0)

    def top_mode(self):
        self.goto(0, 305)

    def bot_mode(self):
        self.goto(0, -300)


class Balls(Player):
    def __init__(self):
        super().__init__()
        self.shape("circle")
        self.shapesize(stretch_len=1.0, stretch_wid=1.0)
        self.goto(0, 0)
        self.ballspeed = SPEED

        #Tutorial block way of moving
        choose = [SPEED, -SPEED]
        random_speed = random.choice(choose)
        self.xspeed = random_speed
        random_speed = random.choice(choose)
        self.yspeed = random_speed

    def start_state(self):
        y = random.randint(-200, 200)
        angle = random.choice(angles)
        for item in CORDS:
            if angle == item:
                angle = random.choice(angles)

        self.goto(0, y)
        self.setheading(angle)

    def start_move(self):
        self.forward(self.ballspeed)

    def tech_turn(self, xcor):
        y = random.randint(-200, 200)
        if xcor < -400:
            good_angle = False
            while not good_angle:
                angle = random.randrange(90, -90, -1)
                for item in angles:
                    if angle < 0:
                        angle += 360
                    if angle == item:
                        good_angle = True

        if xcor > 400:
            good_angle = False
            while not good_angle:
                angle = random.randrange(90, 270)
                for item in angles:
                    if angle < 0:
                        angle += 360
                    if angle == item:
                        good_angle = True

        self.goto(0, y)
        self.setheading(angle)



    def collided(self, angle):

        #Reverses the angle and makes it head to an opposite direction
        if 180 <= angle <= 270:
            angle -= 2*abs(180 - angle)
        elif 0 <= angle <= 90:
            angle -= 2*abs(0 - angle)
        elif 90 < angle < 180:
            angle += 2*abs(180 - angle)
        elif 270 < angle < 360:
            angle += 2*abs(360 - angle)

        if angle >= 360:
            angle -= 360
        elif angle <= 0:
            angle += 360

        self.setheading(angle)
        self.forward(SPEED)




    def collided_player(self, angle):
        self.ballspeed += 5

        # Reverses the angle and makes it head to an opposite direction
        if 180 <= angle <= 270:
            angle += 2*abs(270 - angle)
        elif 0 <= angle <= 90:
            angle += 2*abs(90 - angle)
        elif 90 < angle < 180:
            angle -= 2*abs(90 - angle)
        elif 270 < angle < 360:
            angle -= 2*abs(270 - angle)

        if angle > 360:
            angle -= 360
        elif angle <= 0:
            angle += 360

        self.setheading(angle)
        self.forward(SPEED)

#Below are the most efficient answers in the python bootcamp code
    def tutorial_state(self):
        SPEED = random.choice(SPEEDS)
        choose = [SPEED, -SPEED]
        random_speed = random.choice(choose)
        self.xspeed = random_speed
        random_speed = random.choice(choose)
        self.yspeed = random_speed
        y = random.randint(-200, 200)
        self.goto(0, y)

    def tutorial_move(self):

        new_x = self.xcor() + self.xspeed
        new_y = self.ycor() + self.yspeed
        self.goto(new_x, new_y)
        pass

    def tutorial_bouncey(self):
        #Bounce away from top or bottom walls
        self.yspeed *= -1

    def tutorial_bouncex(self):
        self.xspeed *= -1

