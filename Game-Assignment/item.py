import pygame
from random import randint

class Item(pygame.sprite.Sprite):
    def __init__(self, groups):
        super().__init__(groups)
        if randint(1, 100) > 3:
            #skill
            skillset = ['Skill_Burst', 'Skill_Lightning', 'Skill_Stun', 'Skill_Laser']
            image_path = skillset[randint(0,3)]
            self.sprite_type = 'skill'
        else:
            #EGO
            egoset = ['Card_Gevurah', 'Card_Chokmah', 'Card_Netzach']
            image_path = egoset[randint(0,2)]
            self.sprite_type = 'card'
        full_path = f'../graphics/particles/{image_path}/full.png'
        self.image = pygame.image.load(full_path).convert_alpha()
        self.rect = self.image.get_rect(topleft = (1088, 1088))
