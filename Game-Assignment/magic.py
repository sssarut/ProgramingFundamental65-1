import pygame
from settings import *
from random import randint

class MagicPlayer:
	def __init__(self,animation_player):
		self.animation_player = animation_player
		self.sounds = {
		'heal': pygame.mixer.Sound('../audio/heal.wav'),
		'flame':pygame.mixer.Sound('../audio/Fire.wav'),
		'block': pygame.mixer.Sound('../audio/block.wav'),
		'Stun': pygame.mixer.Sound('../audio/Stun.wav'),
		'Laser': pygame.mixer.Sound('../audio/Laser.wav'),
		'Lightning': pygame.mixer.Sound('../audio/Lightning.wav')
		}
		self.block_sound = pygame.mixer.Sound('../audio/block.wav')

	def heal(self,player,strength,cost,groups):
		if player.energy >= cost:
			self.sounds['heal'].play()
			player.health += strength
			player.energy -= cost
			if player.health >= player.stats['health']:
				player.health = player.stats['health']
			self.animation_player.create_particles('aura',player.rect.center,groups, 'center')
			self.animation_player.create_particles('heal',player.rect.center,groups, 'center')

	def block(self,player,strength,cost,groups):
			self.animation_player.create_shield('block',player,groups)
	def Skill_Laser(self, player, cost, groups):
		if player.energy >= cost:
			player.energy -= cost
			
			if player.status.split('_')[0] == 'right': 
				direction = pygame.math.Vector2(1,0)
				pos = 'left'
			elif player.status.split('_')[0] == 'left': 
				direction = pygame.math.Vector2(-1,0)
				pos = 'right'
			
			self.sounds['Laser'].play()
			self.animation_player.create_particles('Skill_Laser', (player.rect.center) + (32 * direction), groups, pos)
	def flame(self,player,cost,groups):
		if player.energy >= cost:
			player.energy -= cost
			self.sounds['flame'].play()

			if player.status.split('_')[0] == 'right': direction = pygame.math.Vector2(1,0)
			elif player.status.split('_')[0] == 'left': direction = pygame.math.Vector2(-1,0)

			for i in range(-3,3):
				if direction.x: #horizontal
					offset_y = (i) * TILESIZE
					y = player.rect.centery + offset_y + randint(-TILESIZE // 3, TILESIZE // 3)
					x = player.rect.centerx + (3 * direction.x * TILESIZE) + randint(-TILESIZE // 3, TILESIZE // 3)
					self.animation_player.create_particles('flame',(x,y),groups, 'center')
				else: # vertical
					offset_y = (direction.y * i) * TILESIZE
					x = player.rect.centerx + randint(-TILESIZE // 3, TILESIZE // 3)
					y = player.rect.centery + offset_y + randint(-TILESIZE // 3, TILESIZE // 3)
					self.animation_player.create_particles('flame',(x,y),groups, 'center')


	def Lightning(self,player , pos,cost,groups,detect):
		if player.energy >= cost:
			player.energy -= cost
			for target in detect:
				self.animation_player.create_particles('Skill_Lightning', target.rect.center, groups, 'down')
				self.sounds['Lightning'].play()

