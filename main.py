import pygame, sys, asyncio
from player_class import Player
from ball_class import Ball

pygame.init()
# General setup
win_width = 900
win_height = 600
win = pygame.display.set_mode((win_width, win_height))
pygame.display.set_caption("Pong+")
clock = pygame.time.Clock()

def draw_game(win, players, balls):
    win.fill((0,0,0))

    for player in players:
        player.draw(win)
    for ball in balls:
        ball.draw(win)

    pygame.display.flip()

def reset_game():
    p1 = Player(30, win_height/2, (100, 255, 10), pygame.K_w, pygame.K_s)
    p2 = Player(win_width - 30, win_height/2, (100, 255, 10), pygame.K_UP, pygame.K_DOWN)
    players = pygame.sprite.Group()
    players.add(p1)
    players.add(p2)
    ball = Ball(win_width / 2, win_height/2, (200, 100, 10))
    balls = pygame.sprite.Group()
    balls.add(ball)
    
    return balls, players

async def main():
    balls, players = reset_game()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        userInput = pygame.key.get_pressed()

        for player in players:
            player.move(userInput, win_height)
        for ball in balls:
            ball.move(win_height, players)
            if ball.offscreen(win_width):
                balls, players = reset_game()
    
        draw_game(win, players, balls)
        clock.tick(60)
        await asyncio.sleep(0)

asyncio.run(main())