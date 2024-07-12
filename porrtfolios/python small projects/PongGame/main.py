from turtle import Screen
import time
from turtle import Turtle
from player import Player
from keyconfig import WatchedKey
from assets import Walls, Balls
from scoreboard import Scoreboard, EnemyScoreboard

my_screen = Screen()
my_screen.bgcolor("black")
my_screen.title("Pong")
my_screen.setup(width=800, height=600)
my_screen.tracer(0) #Stops screen in automatically animating each individual command line

start_y = 280
interval_y = 25
player_1 = Player()
player_2 = Player()
player_2.enemy_mode()
player_1_score = Scoreboard()
player_2_score = EnemyScoreboard()



top_wall = Walls()
bot_wall = Walls()
top_wall.top_mode()
bot_wall.bot_mode()
ball = Balls()
ball.start_state() #initializing position of ball based on my own understanding
# ball.tutorial_state() #initializing position of ball based on bootcamp tutorial

my_screen.listen()
W_Key = WatchedKey("w") #Detects the state of Up Key, this class allows keys to be held down
S_Key = WatchedKey("s") #Detects the state of Down Key, this class allows keys to be held down
UP_Key = WatchedKey("Up") #Detects the state of Up Key, this class allows keys to be held down
DOWN_Key = WatchedKey("Down")
#MID_BOUNDARY LINE
for item in range(0, 23): #23
    item = Turtle()
    item.shape("square")
    item.color("white")
    item.penup()
    item.shapesize(stretch_len=0.10, stretch_wid= 0.5)
    item.goto(0, start_y)
    start_y -= interval_y


game_on = True
ran_once= True
time_refresh = 0.02
while game_on:
    my_screen.update()#Updates screen after doing the code blocks below
    time.sleep(time_refresh)#Refresh rate in seconds of the screen

    if ran_once:
        time.sleep(1)
        ran_once = False
    #Checls the state of each key, assigns movement if there is.
    if W_Key.down:
        player_1.move_up()
    if S_Key.down:
        player_1.move_down()

    # Allows player2 movement
    # if UP_Key.down:
    #     player_2.move_up()
    # if DOWN_Key.down:
    #     player_2.move_down()

    ball.start_move() #How I perceived the ball to move
    # ball.tutorial_move() #How the tutorial codes it to move

    # line below automates movement for 2nd player
    player_2.enemy_move()


    #Detect Collision with Wall
    if abs(ball.ycor() - top_wall.ycor()) < 20 or abs(ball.ycor() - bot_wall.ycor()) < 20:
        ball.collided(ball.heading()) #How I perceive ball collision and bouncing with angles
        # ball.tutorial_bouncey() #How tutorial interprets bouncing with coordinates

    #Detect Collision with paddle
    if abs(ball.xcor() - player_1.xcor()) < 20 and abs(ball.ycor() - player_1.ycor()) < 50:
        ball.collided_player(ball.heading())#Boucning with angles
        # ball.tutorial_bouncex()#How tutorial interprets bouncing with coordinates
    elif abs(ball.xcor() - player_2.xcor()) < 20 and abs(ball.ycor() - player_2.ycor()) < 50:
        ball.collided_player(ball.heading())#Bouncing with angles
        # ball.tutorial_bouncex()#How tutorial interprets bouncing with coordinates
    elif ball.xcor() > 400 or ball.xcor() < -400:
        if ball.xcor() > 400:
            player_1_score.getscore()
            ball.tech_turn(ball.xcor())#Original understanding, ball takes turn on the right direction and makes it opposite
            # ball.tutorial_state()
            ball.ballspeed = 15

        elif ball.xcor() < -400:
            player_2_score.getscore()
            ball.tech_turn(ball.xcor())#Original understanding, ball takes turn on the right direction and makes it opposite
            # ball.tutorial_state()
            ball.ballspeed = 15

        ran_once = True






my_screen.exitonclick()