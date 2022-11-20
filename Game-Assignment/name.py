import pygame 
from settings import *
from debug import debug



class Name:
    def __init__(self):
        self.display_surf = pygame.display.get_surface()
        self.image = pygame.image.load('../graphics/tilemap/Score.png')
        self.rect = self.image.get_rect(topleft = (0, 0))
        self.font = pygame.font.Font(UI_FONT, 30)
        self.text = ''
        self.offset = 0
        self.count = 0

    def text_input (self, level, scoreboard):
        #print('in')
        if level.death == True:
            #print('process')
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_BACKSPACE:
                        self.text = self.text[:-1]
                    elif event.key == pygame.K_RETURN:
                        scoreboard[self.text] = level.player.exp
                        self.text = ''
                        level.toggle_home()
                        level.end = 1

                    else :
                        self.text += event.unicode
            self.name_surf = self.font.render(self.text, False, 'gold')
            self.name_rect = self.name_surf.get_rect(center = ((1280 // 2), 100 + self.offset + 150))
            pygame.draw.rect(self.display_surf, UI_BG_COLOR, self.name_rect.inflate(20, 20))
            self.display_surf.blit(self.name_surf, self.name_rect)

    def show_score (self, scoreboard):

        self.offset = 0
        self.count = 0
        sorted_name = sorted(scoreboard.items(), key=lambda x:x[1], reverse=True)
        self.sorted_dict = dict(sorted_name)
        name = list(self.sorted_dict.keys())

        self.subject = self.font.render('High Score', False, 'gold')
        self.subject_rect = self.subject.get_rect(center = ((1280 // 2), 100))
        pygame.draw.rect(self.display_surf, UI_BG_COLOR, self.subject_rect.inflate(20, 20))
        self.display_surf.blit(self.subject, self.subject_rect)
        self.line = pygame.Rect(0, 0, 10, 500)
        self.line.center = ((1280 // 2) , (720 // 2) + 80)
        pygame.draw.rect(self.display_surf, UI_BG_COLOR, self.line)

        for key in name:
            if self.count <= 4:
                self.image = pygame.image.load('../graphics/tilemap/Score.png')
                self.rect = self.image.get_rect(topleft = (0, 0))
                self.text_surf = self.font.render(key, False, 'gold')
                self.text_rect = self.text_surf.get_rect(topright = ((1280 // 2) - 100, 200 + self.offset))
                self.score_surf = self.font.render(str(int(self.sorted_dict[key])), False, 'gold')
                self.score_rect = self.score_surf.get_rect(topleft = ((1280 // 2) + 100, 200 + self.offset))
                
                self.offset += 100
                self.count += 1
                pygame.draw.rect(self.display_surf, UI_BG_COLOR, self.text_rect.inflate(20, 20))
                self.display_surf.blit(self.text_surf, self.text_rect)
                pygame.draw.rect(self.display_surf, UI_BG_COLOR, self.score_rect.inflate(20, 20))
                self.display_surf.blit(self.score_surf, self.score_rect)

