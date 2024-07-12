from turtle import Turtle
UP = 90
DOWN = 270
enemy_start_y = 235
upward = True
SPEED = 30
Y_LIMIT_UP = 235
Y_LIMIT_DOWN = -235
class Player(Turtle):
    def __init__(self):
        super().__init__()
        self.shape("square")
        self.speed("fastest")
        self.color("white")
        self.penup()
        self.shapesize(stretch_len=5, stretch_wid=1)
        self.setheading(90)
        self.goto(-380, 0)

    def enemy_mode(self):
        self.goto(380, enemy_start_y)

    def enemy_move(self):
        global upward
        y = self.ycor()
        if upward:
            self.forward(SPEED)
            if self.ycor() >= Y_LIMIT_UP:
                upward = False
        else:
            self.backward(SPEED)
            if self.ycor() <= Y_LIMIT_DOWN:
                upward = True

    def move_down(self):
        if self.ycor() > Y_LIMIT_DOWN:
            self.backward(SPEED)#Backward means DOWN

    def move_up(self):
        if self.ycor() < Y_LIMIT_UP:
            self.forward(SPEED)#Forward mean UP
