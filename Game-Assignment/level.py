from random import choice, randint

import pygame

from debug import debug
from enemy import Enemy
from magic import MagicPlayer
from particles import AnimationPlayer
from player import Player
from settings import *
from support import *
from tile import Tile
from ui import UI
from upgrade import Upgrade
from weapon import Weapon
from menu import Menu


class Level:
	def __init__(self):

		# get the display surface 
		self.display_surface = pygame.display.get_surface()
		self.game_paused = True
		self.alpha = 0
		self.mode = 'm'
		self.capture = 0
		self.fog_timer = 0
		self.surf = pygame.image.load('../graphics/tilemap/FoW.png')
		self.surf2 = pygame.image.load('../graphics/tilemap/WoF.png')

		# sprite group setup
		self.visible_sprites = YSortCameraGroup()
		self.obstacle_sprites = pygame.sprite.Group()

		# attack sprites
		self.current_attack = None
		self.attack_sprites = pygame.sprite.Group()
		self.attackable_sprites = pygame.sprite.Group()

		# sprite setup
		self.create_map()
		self.fog_state = True

		# user interface 
		self.ui = UI()
		self.menu = Menu()
		self.max = 8
		self.upgrade = Upgrade(self.player)

		# particles
		self.animation_player = AnimationPlayer()
		self.magic_player = MagicPlayer(self.animation_player)


		self.enemy = 0

	def create_map(self):
		layouts = {
			'boundary': import_csv_layout('../map/map_FloorBlocks.csv'),
			#'grass': import_csv_layout('../map/map_Grass.csv'),
			'object': import_csv_layout('../map/map_Objects.csv'),
			'entities': import_csv_layout('../map/map_Entities.csv')
		}
		graphics = {
			'grass': import_folder('../graphics/Grass'),
			'objects': import_folder('../graphics/objects')
		}

		for style,layout in layouts.items():
			for row_index,row in enumerate(layout):
				for col_index, col in enumerate(row):
					if col != '-1':
						x = col_index * TILESIZE
						y = row_index * TILESIZE
						if style == 'boundary':
							Tile((x,y),[self.obstacle_sprites],'invisible')
						if style == 'grass':
							random_grass_image = choice(graphics['grass'])
							Tile(
								(x,y),
								[self.visible_sprites,self.obstacle_sprites,self.attackable_sprites],
								'grass',
								random_grass_image)

						if style == 'object':
							if col == '0':
								surf = graphics['objects'][int(col)]
								Tile((x,y),[self.visible_sprites,self.obstacle_sprites],'object',surf)
							else :
								surf = graphics['objects'][int(col)]
								Tile((x,y),[self.visible_sprites,self.obstacle_sprites],'object2',surf)


						if style == 'entities':
							if col == '394':
								self.player = Player(
									(x,y),
									[self.visible_sprites],
									self.obstacle_sprites,
									self.create_attack,
									self.destroy_attack,
									self.create_magic)
							else:
								#if col == '18': monster_name = 'blu_skull'
								#elif col == '20': monster_name = 'red_skull'
								#Enemy(
								#	monster_name,
								#	(x,y),
								#	[self.visible_sprites,self.attackable_sprites],
								#	self.obstacle_sprites,
								#	self.damage_player,
								#	self.trigger_death_particles,
								#	self.add_exp)
								pass

	def create_attack(self):
		
		self.current_attack = Weapon(self.player,[self.visible_sprites,self.attack_sprites])

	def create_magic(self,style,strength,cost):
		if style == 'heal':
			self.magic_player.heal(self.player,strength,cost,[self.visible_sprites])

		if style == 'flame':
			self.magic_player.flame(self.player,cost,[self.visible_sprites,self.attack_sprites])

	def destroy_attack(self):
		if self.current_attack:
			self.current_attack.kill()
		self.current_attack = None

	def player_attack_logic(self):
		if self.attack_sprites:
			for attack_sprite in self.attack_sprites:
				collision_sprites = pygame.sprite.spritecollide(attack_sprite,self.attackable_sprites,False)
				if collision_sprites:
					for target_sprite in collision_sprites:
						if target_sprite.sprite_type == 'grass':
							pos = target_sprite.rect.center
							offset = pygame.math.Vector2(0,75)
							for leaf in range(randint(3,6)):
								self.animation_player.create_grass_particles(pos - offset,[self.visible_sprites])
							target_sprite.kill()
						else:
							target_sprite.get_damage(self.player,attack_sprite.sprite_type)

	def damage_player(self,amount,attack_type):
		if self.player.vulnerable:
			self.player.health -= amount
			self.player.vulnerable = False
			self.player.hurt_time = pygame.time.get_ticks()
			self.animation_player.create_particles(attack_type,self.player.rect.center,[self.visible_sprites])

	def trigger_death_particles(self,pos,particle_type):

		self.animation_player.create_particles(particle_type,pos,self.visible_sprites)
		self.enemy -= 1
		monster_data[particle_type]['health'] += 10
		monster_data[particle_type]['damage'] += 10 
	def add_exp(self,amount):

		self.player.exp += amount

	def toggle_time(self):
		self.mode = 'n'
		self.game_paused = not self.game_paused
	def toggle_upgrade(self):
		self.mode = 'u'
		self.game_paused = not self.game_paused 
	def toggle_menu(self):
		self.mode = 'm'
		debug('change')
		self.game_paused = not self.game_paused 
	
	def KoTH(self):
		if self.player.hitbox.centerx >= 1024 and self.player.hitbox.centery >= 1024 and self.player.hitbox.centerx <= 1152 and self.player.hitbox.centery <= 1152 and self.capture == 0:
			self.player.point += 1
			if self.fog_state == True:
				self.alpha = 0
			self.fog_state = False
		else :
			if self.fog_state == False:
				self.alpha = 0
			self.fog_state = True

	
	def fog(self):
		self.fog_timer = pygame.time.get_ticks()
		if self.alpha <= 255 :
			self.alpha += 20
			self.surf.set_alpha(self.alpha)
			self.surf2.set_alpha(self.alpha)
		rect = self.surf.get_rect(topleft = (0, 0))
		if self.fog_state :
			self.display_surface.blit(self.surf, rect)
		elif not self.fog_state :
			self.display_surface.blit(self.surf2, rect)


	def spawn(self):
		layouts = {
			'spawn': import_csv_layout('../map/map_Spawn.csv')
		}
		for style,layout in layouts.items():
			for row_index,row in enumerate(layout):
				for col_index, col in enumerate(row):
					if col != '-1':
						x = col_index * TILESIZE
						y = row_index * TILESIZE
						if style == 'spawn':
							if col == '2' and self.enemy <= self.max:
								rand = randint(0, 100)
								rand2 = randint(0, 100)
								if rand == 0 and rand2 >= 95:
									self.enemy += 1
									Enemy(
										'red_skull',
										(x,y),
										[self.visible_sprites,self.attackable_sprites],
										self.obstacle_sprites,
										self.damage_player,
										self.trigger_death_particles,
										self.add_exp)
								elif rand == 1 and rand2 >= 90:
									self.enemy += 1
									Enemy(
										'blu_skull',
										(x,y),
										[self.visible_sprites,self.attackable_sprites],
										self.obstacle_sprites,
										self.damage_player,
										self.trigger_death_particles,
										self.add_exp)
								else : pass

							
	def run(self):
		time = pygame.time.get_ticks()
		self.visible_sprites.custom_draw(self.player)
		if self.player.point >= 1200 and self.capture == 0:
			self.max += 2
			self.capture = 1
			self.player.exp += 200
		elif self.player.point < 1200:
			self.capture = 0
		if self.capture == 0:
			self.fog()
			self.spawn()
		self.ui.display(self.player)
		self.KoTH()
		debug(self.mode)
		
		if self.game_paused:
			if self.mode == 'u':
				self.upgrade.display()
			if self.mode == 'm':
				self.menu.display()
		else:
			self.visible_sprites.update()
			self.visible_sprites.enemy_update(self.player)
			self.player_attack_logic()
		

class YSortCameraGroup(pygame.sprite.Group):
	def __init__(self):

		# general setup 
		super().__init__()
		self.display_surface = pygame.display.get_surface()
		self.half_width = self.display_surface.get_size()[0] // 2
		self.half_height = self.display_surface.get_size()[1] // 2
		self.offset = pygame.math.Vector2()

		# creating the floor
		self.floor_surf = pygame.image.load('../graphics/tilemap/ground.png').convert()
		self.floor_rect = self.floor_surf.get_rect(topleft = (0,0))

	def custom_draw(self,player):

		# getting the offset 
		self.offset.x = player.rect.centerx - self.half_width
		self.offset.y = player.rect.centery - self.half_height

		# drawing the floor
		floor_offset_pos = self.floor_rect.topleft - self.offset
		self.display_surface.blit(self.floor_surf,floor_offset_pos)

		# for sprite in self.sprites():
		for sprite in sorted(self.sprites(),key = lambda sprite: sprite.rect.centery):
			offset_pos = sprite.rect.topleft - self.offset
			self.display_surface.blit(sprite.image,offset_pos)

	def enemy_update(self,player):
		enemy_sprites = [sprite for sprite in self.sprites() if hasattr(sprite,'sprite_type') and sprite.sprite_type == 'enemy']
		for enemy in enemy_sprites:
			enemy.enemy_update(player)
