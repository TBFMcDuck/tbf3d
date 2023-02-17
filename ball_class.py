import pygame
from pygame.locals import *

pygame.init() # Initiate pygame

class Ball(pygame.sprite.Sprite):
    def __init__(self, x, y, color):
        super().__init__()
        self.color = color
        self.rect = pygame.Rect(x, y, 20, 20)
        # Movement
        self.velx = 6
        self.vely = 0
        self.velocityDividor = 1 # The higher value, the less ball acceleration
    
    def draw(self, win):
        pygame.draw.rect(win, self.color, self.rect)
    
    def move(self, win_height, players):
        # Apply movement
        self.rect.x += self.velx
        self.rect.y += self.vely
        # Check if crashing into wall
        if (self.rect.y > win_height - self.rect.height) or (self.rect.y < 0): # If crashing into wall
            self.rect.y -= self.vely
            self.vely *= -1
        # Check if crashing into player
        if pygame.sprite.spritecollide(self, players, False): # If colliding with player
            self.velx *= -1
                
            for player in pygame.sprite.spritecollide(self, players, False):
                self.vely += player.changeY / self.velocityDividor

                if self.velx > 0: # If moving right
                    self.rect.left = player.rect.right   
                elif self.velx < 0: # If moving left
                    self.rect.right = player.rect.left
    
    def offscreen(self, win_width):
        if (self.rect.x < 0) or (self.rect.x > win_width):
            return True