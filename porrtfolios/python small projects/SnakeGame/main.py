from turtle import Screen
import time
from food import Food
from Snake import Snake
from scoreboard import Scoreboard
my_screen = Screen()
my_screen.bgcolor("black")
my_screen.title("My Snake Game")
my_screen.setup(width=600, height=600)
my_screen.tracer(0) #Stops screen in automatically animating each individual command line
snake = Snake()
food = Food()
scoreboard = Scoreboard()
collision_delay = 15
my_screen.listen()
my_screen.onkey(key="Up", fun=snake.move_up)
my_screen.onkey(key="Down", fun=snake.move_down)
my_screen.onkey(key="Left", fun=snake.move_left)
my_screen.onkey(key="Right", fun=snake.move_right)


game_on = True


while game_on:
    my_screen.update()#Updates screen after doing the code blocks below
    time.sleep(0.1)#Refresh rate in seconds of the screen
    snake.move()
    #Detect collision with food
    if snake.segments[0].distance(food) < collision_delay:
        snake.extend()
        food.refresh()
        scoreboard.increasescore()
    #Detect collision with wall
    if snake.segments[0].xcor() > 280 or snake.segments[0].xcor() < -280 or snake.segments[0].ycor() > 280 or snake.segments[0].ycor() < -290:
        scoreboard.reset()
        snake.reset()
    #detect collision with tail
    for segment in snake.segments[1:]:
        if snake.head.distance(segment) < 10:
            snake.reset()
            scoreboard.reset()



my_screen.exitonclick()