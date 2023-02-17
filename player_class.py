import pygame
from pygame.locals import *

pygame.init() # Initiate pygame

class Player(pygame.sprite.Sprite):
    def __init__(self, x, y, color, upKey, downKey):
        super().__init__()
        self.color = color
        self.rect = pygame.Rect(x, y, 15, 125)
        # Movement
        self.upKey = upKey
        self.downKey = downKey
        self.changeY = 0
        self.acceleration = 1
        self.deacceleration = 2
        self.maxVelY = 10
    
    def draw(self, win):
        pygame.draw.rect(win, self.color, self.rect)
    
    def move(self, userInput, win_height):
        # Moving y
        if userInput[self.downKey] and (self.rect.y < win_height - self.rect.height):
            # Accelerate the player
            if self.changeY < self.maxVelY:  # If not over top speed
                self.changeY += self.acceleration  # Accelerate
        elif userInput[self.upKey] and (self.rect.y > 0):
            # Accelerate the player
            if self.changeY > self.maxVelY * -1:  # If not over top speed
                self.changeY -= self.acceleration  # Accelerate
        else: # Else happends when there is no movement in y direction
            # Deaccelerate the player
            if self.changeY > 0: # If moving right
                self.changeY -= self.deacceleration  # Deaccelerate
            elif self.changeY < 0:  # If moving left
                self.changeY += self.deacceleration  # Deaccelerate

        # Apply movement
        self.rect.y += self.changeY
        # Check if crashing into wall
        if (self.rect.y > win_height - self.rect.height) or (self.rect.y < 0): # If crashing into wall
            self.rect.y -= self.changeY
            self.changeY = 0