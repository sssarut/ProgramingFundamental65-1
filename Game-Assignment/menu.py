import pygame
from settings import *

class Menu:
    def __init__(self):
        self.start = False
        self.highscore = False
        self.exit = False
        self.display_surface = pygame.display.get_surface()
        self.font = pygame.font.Font(UI_FONT, UI_FONT_SIZE)


    def display(self):
        self.start_surf = self.font.render('START', False, 'gold')
        self.score_surf = self.font.render('HIGHSCORE', False, 'gold')
        self.exit_surf = self.font.render('EXIT', False, 'gold')

        self.start_rect = pygame.Rect(0, 200, 300, 50)
        self.start_rect.centerx = 1280 // 2
        self.score_rect = pygame.Rect(0, 300, 300, 50)
        self.score_rect.centerx = 1280 // 2
        self.exit_rect = pygame.Rect(0, 400, 300, 50)
        self.exit_rect.centerx = 1280 // 2
        
        pos  = pygame.mouse.get_pos()

        if self.start_rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1 and self.start == False:
                self.start = True
        elif self.score_rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1 and self.highscore == False:
                self.highscore = True
        elif self.exit_rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1 and self.exit == False:
                self.exit = True
        if pygame.mouse.get_pressed()[0] == 0:
            self.start = False
            self.highscore = False
            self.exit = False
        pygame.draw.rect(self.display_surface, UI_BG_COLOR, self.start_rect.inflate(20, 20))
        self.display_surface.blit(self.start_surf, self.start_rect)
        #pygame.draw.rect(self.display_surface, UI_BORDER_COLOR, self.start_rect.inflate(20, 20))

        pygame.draw.rect(self.display_surface, UI_BG_COLOR, self.score_rect.inflate(20, 20))
        self.display_surface.blit(self.score_surf, self.score_rect)
        #pygame.draw.rect(self.display_surface, UI_BORDER_COLOR, self.score_rect.inflate(20, 20))

        pygame.draw.rect(self.display_surface, UI_BG_COLOR, self.exit_rect.inflate(20, 20))
        self.display_surface.blit(self.exit_surf, self.exit_rect)
        #pygame.draw.rect(self.display_surface, UI_BORDER_COLOR, self.exit_rect.inflate(20, 20))