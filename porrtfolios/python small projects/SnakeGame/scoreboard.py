from turtle import  Turtle
SCORE_POS = (0, 260)
ALIGNMENT = "center"
FONT_SIZE_TYPE = ("Courier", 24, "bold")
class Scoreboard(Turtle):
    def __init__(self):
        super().__init__()
        self.clear()
        self.color("white")
        self.penup()
        self.hideturtle()
        self.goto(SCORE_POS)
        self.score = 0
        with open("data.txt") as data:
            content = data.read()
            self.high_score = int(content)
        self.getscore()

    def getscore(self):
        self.clear()
        self.write(f"Score: {self.score} High Score: {self.high_score}", align=ALIGNMENT, font=FONT_SIZE_TYPE)

    def game_over(self):
        self.goto(0, 0)
        self.write("Game Over :(", align=ALIGNMENT, font=FONT_SIZE_TYPE)

    def reset(self):
        if self.score == self.high_score:
            with open("data.txt", mode="w") as data:
                data.write(str(self.score))
            self.high_score = self.score
        self.score = 0
        self.getscore()

    def increasescore(self):
        if self.score == self.high_score:
            self.high_score += 1
        self.score += 1
        self.getscore()


