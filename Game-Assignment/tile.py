import pygame 
from settings import *

class Tile(pygame.sprite.Sprite):
	def __init__(self,pos,groups,sprite_type,surface = pygame.Surface((TILESIZE,TILESIZE))):
		super().__init__(groups)
		self.sprite_type = sprite_type
		y_offset = HITBOX_OFFSET_Y[sprite_type]
		x_offset = HITBOX_OFFSET_X[sprite_type]
		self.image = surface
		if sprite_type == 'object' or sprite_type == 'object2':
			self.rect = self.image.get_rect(topleft = (pos[0],pos[1] - (TILESIZE)))
		else:
			self.rect = self.image.get_rect(topleft = pos)
		if sprite_type == 'object2':
			self.hitbox = self.rect.inflate(x_offset,y_offset - 32)
			self.hitbox.y += 32
		else:
			self.hitbox = self.rect.inflate(x_offset,y_offset)