import pygame

class Area(pygame.sprite.Sprite):
    def __init__(self, groups, path, pos):
        super().__init__(groups)
        self.image = pygame.image.load(path).convert_alpha()
        self.rect = self.image.get_rect(center = pos)