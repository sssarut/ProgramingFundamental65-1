import pygame
from settings import *
from name import Name

class Menu:
    def __init__(self):
        self.start = False
        self.name =  Name()
        self.highscore = False
        self.exit = False
        self.display_surface = pygame.display.get_surface()
        self.font = pygame.font.Font(UI_FONT, 30)


    def display(self, mode):
        if mode == 'm':
            self.start_surf = self.font.render('START', False, 'gold')
            self.image = pygame.image.load('../graphics/tilemap/Screen.png')
            self.rect = self.image.get_rect(topleft = (0,0))
        elif mode == 'r':
            self.start_surf = self.font.render('RESUME', False, 'gold')
            self.image = pygame.image.load('../graphics/tilemap/Wait.png')
            self.rect = self.image.get_rect(topleft = (0,0))
        self.score_surf = self.font.render('HIGHSCORE', False, 'gold')
        self.exit_surf = self.font.render('EXIT', False, 'gold')

        self.start_rect = self.start_surf.get_rect(center = ((1280 // 2), 300))
        self.score_rect = self.score_surf.get_rect(center = ((1280 // 2), 400))
        self.exit_rect = self.exit_surf.get_rect(center = ((1280 // 2), 500))
        
        pos  = pygame.mouse.get_pos()

        if self.start_rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1 and self.start == False:
                self.start = True
        elif self.score_rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1 and self.highscore == False:
                self.highscore = True
                self.display_surface.blit(self.image, self.rect)
        elif self.exit_rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1 and self.exit == False:
                self.exit = True
        if pygame.mouse.get_pressed()[0] == 0:
            self.start = False
            self.highscore = False
            self.exit = False
        pygame.draw.rect(self.display_surface, UI_BG_COLOR, self.start_rect.inflate(20, 20))
        self.display_surface.blit(self.start_surf, self.start_rect)

        pygame.draw.rect(self.display_surface, UI_BG_COLOR, self.score_rect.inflate(20, 20))
        self.display_surface.blit(self.score_surf, self.score_rect)

        pygame.draw.rect(self.display_surface, UI_BG_COLOR, self.exit_rect.inflate(20, 20))
        self.display_surface.blit(self.exit_surf, self.exit_rect)