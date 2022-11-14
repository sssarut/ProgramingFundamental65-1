import pygame 
from settings import *
from support import import_folder
from entity import Entity
from upgrade import Upgrade

class Player(Entity):
	def __init__(self,pos,groups,obstacle_sprites,create_attack,destroy_attack,create_magic,battle):
		super().__init__(groups)
		self.image = pygame.image.load('../graphics/player/right_idle/right_0.png').convert_alpha()
		self.rect = self.image.get_rect(topleft = pos)
		self.hitbox = self.rect.inflate(-6,-20)
		self.hitbox.y += 20
		self.battle_sound = battle
		self.warpsound = pygame.mixer.Sound('../audio/tp.wav')
		self.warpsound.set_volume(0.2)

		# graphics setup
		self.import_player_assets()
		self.status = 'right'
		self.last_status = 'right'

		# movement 
		self.attacking = False
		self.casting = False
		self.attack_cooldown = 400
		self.attack_time = None
		self.obstacle_sprites = obstacle_sprites

		# weapon
		self.create_attack = create_attack
		self.destroy_attack = destroy_attack
		self.weapon_index = 0
		self.weapon = list(weapon_data.keys())[self.weapon_index]
		self.can_switch_weapon = True
		self.weapon_switch_time = None
		self.switch_duration_cooldown = 200

		# magic 
		self.create_magic = create_magic
		self.magic_index = 0
		self.magic = list(magic_data.keys())[self.magic_index]
		self.can_switch_magic = True
		self.magic_switch_time = None

		# stats
		self.stats = {'health': 800,'energy':50,'attack': 50,'magic': 50,'speed': 5}
		self.max_stats = {'health': 8000, 'energy': 500, 'attack': 500, 'magic' : 500, 'speed': 50}
		self.upgrade_cost = {'health': 100, 'energy': 100, 'attack': 100, 'magic' : 100, 'speed': 100}
		self.health = self.stats['health']
		self.energy = self.stats['energy']
		self.tping = False
		self.tp_time = None
		self.cast_time = None
		self.block_count = 0
		self.blocking = False
		self.exp = 0
		self.target = ''
		self.speed = self.stats['speed']
		self.point = 0

		# damage timer
		self.vulnerable = True
		self.hurt_time = None
		self.invulnerability_duration = 1000
		self.can_tp = True
		self.can_atk = True
		self.can_cast = True
		self.block_time = pygame.time.get_ticks()


		# import a sound
		self.weapon_attack_sound = pygame.mixer.Sound('../audio/sword.wav')
		self.weapon_attack_sound.set_volume(0.2)

	def import_player_assets(self):
		character_path = '../graphics/player/'
		self.animations = {'left': [],'right': [],
			'right_idle':[],'left_idle':[],
			'right_attack':[],'left_attack':[],'left_cast':[],'right_cast':[], 'left_tp':[], 'right_tp':[]}

		for animation in self.animations.keys():
			full_path = character_path + animation
			self.animations[animation] = import_folder(full_path)

	def input(self):
		if not self.attacking:
			keys = pygame.key.get_pressed()

			# movement input and not self.blocking
			if keys[pygame.K_w] and not self.attacking and not self.casting and not self.tping and not self.blocking:
				self.direction.y = -1
				self.status = self.last_status
			elif keys[pygame.K_s] and not self.attacking and not self.casting and not self.tping and not self.blocking:
				self.direction.y = 1
				self.status = self.last_status
			else:
				self.direction.y = 0
			if keys[pygame.K_LSHIFT] and (keys[pygame.K_a] or keys[pygame.K_s] or keys[pygame.K_d] or keys[pygame.K_w]) and not self.tping and not self.casting and not self.attacking and self.can_tp == True:
				self.tping = True
				if keys[pygame.K_a]:
					self.target = 'left'
				elif keys[pygame.K_s]:
					self.target = 'down'
				elif keys[pygame.K_w]:
					self.target = 'up'
				elif keys[pygame.K_d]:
					self.target = 'right'
				self.tp_time = pygame.time.get_ticks()
				self.frame_index = 0
				self.warpsound.play()
				self.can_tp = False

			if keys[pygame.K_p] :
				self.point += 200
			if self.blocking and ((not keys[pygame.K_f]) or self.block_count >= 6):
				self.blocking = False
				self.frame_index = 0
			if keys[pygame.K_d]  and not self.attacking and not self.casting and not self.tping and not self.blocking:
				self.direction.x = 1
				self.status = 'right'
				self.last_status = 'right'
			elif keys[pygame.K_a]  and not self.attacking and not self.casting and not self.tping and not self.blocking:
				self.direction.x = -1
				self.status = 'left'
				self.last_status = 'left'
			else:
				self.direction.x = 0

			# attack input 
			if keys[pygame.K_n] and self.hitbox.centerx >= 1024 and self.hitbox.centery >= 1024 and self.hitbox.centerx <= 1152 and self.hitbox.centery <= 1152 and self.point >= 1200:
				self.point = 0
				pygame.mixer.stop()
				self.battle_sound.set_volume(0.1)
				self.battle_sound.play(loops = -1) and not self.blocking
			elif keys[pygame.K_SPACE] and not self.casting and not self.attacking and not self.tping and self.can_atk:
				self.attacking = True
				self.attack_time = pygame.time.get_ticks()
				self.create_attack()
				self.weapon_attack_sound.play()
				self.frame_index = 0
				self.can_atk = False

			# magic input 
			if keys[pygame.K_LCTRL] and not self.attacking and not self.casting and not self.tping and self.can_cast and not self.blocking:
				self.casting = True
				self.cast_time = pygame.time.get_ticks()
				style = list(magic_data.keys())[self.magic_index]
				strength = list(magic_data.values())[self.magic_index]['strength'] + self.stats['magic']
				cost = list(magic_data.values())[self.magic_index]['cost']
				self.create_magic(style,strength,cost)
				self.frame_index = 0
				self.can_cast = False
			if keys[pygame.K_f] and not self.attacking and not self.casting and not self.tping and self.block_count <= 5:
				if not self.blocking:
					self.create_magic('block', 0, 0)
				self.blocking = True
				self.block_time = pygame.time.get_ticks()
			"""
			if keys[pygame.K_q] and self.can_switch_weapon:
				self.can_switch_weapon = False
				self.weapon_switch_time = pygame.time.get_ticks()
				
				if self.weapon_index < len(list(weapon_data.keys())) - 1:
					self.weapon_index += 1
				else:
					self.weapon_index = 0
					
				self.weapon = list(weapon_data.keys())[self.weapon_index]
			"""
			if keys[pygame.K_e] and self.can_switch_magic:
				self.can_switch_magic = False
				self.magic_switch_time = pygame.time.get_ticks()
				
				if self.magic_index < len(list(magic_data.keys())) - 1:
					self.magic_index += 1
				else:
					self.magic_index = 0

				self.magic = list(magic_data.keys())[self.magic_index]

	def get_status(self):

		# idle status
		if self.direction.x == 0 and self.direction.y == 0:
			if not 'idle' in self.status and not 'attack' in self.status and not 'cast' in self.status and not 'tp' in self.status:
				self.status = self.status + '_idle'

		if self.attacking:
			self.direction.x = 0
			self.direction.y = 0
			if not 'attack' in self.status:
				if 'idle' in self.status:
					self.status = self.status.replace('_idle','_attack')
				elif 'cast' in self.status:
					self.status = self.status.replace('_cast','_attack')
				elif 'tp' in self.status:
					self.status = self.status.replace('_tp','_attack')
				else:
					self.status = self.status + '_attack'
		elif self.tping:
			if self.target != '':
				if self.target == 'left':
					self.hitbox.x -= 300
					self.target = ''
				elif self.target == 'right':
					self.hitbox.x += 300
					self.target = ''
				elif self.target == 'up':
					self.hitbox.y -= 300
					self.target = ''
				elif self.target == 'down':
					self.hitbox.y += 300
					self.target = ''
				if self.hitbox.x < 64:
					self.hitbox.x = 64
				if self.hitbox.x > 2118:
					self.hitbox.x = 2100
				if self.hitbox.y < 64:
					self.hitbox.y = 64
				if self.hitbox.y > 2132:
					self.hitbox.y = 2100
				if not 'tp' in self.status:
					if 'idle' in self.status:
						self.status = self.status.replace('_idle','_tp')
					elif 'attack' in self.status:
						self.status = self.status.replace('_attack','_tp')
					elif 'cast' in self.status:
						self.status = self.status.replace('_cast','_tp')
					else:
						self.status = self.status + '_tp'
			
		elif self.casting:
			self.direction.x = 0
			self.direction.y = 0
			if not 'cast' in self.status:
				if 'idle' in self.status:
					self.status = self.status.replace('_idle','_cast')
				elif 'attack' in self.status:
					self.status = self.status.replace('_attack','_cast')
				elif 'tp' in self.status:
					self.status = self.status.replace('_tp','_cast')
				else:
					self.status = self.status + '_cast'
		
		else:
			if 'attack' in self.status:
				self.status = self.status.replace('_attack','')
			if 'cast' in self.status:
				self.status = self.status.replace('_cast','')
			if 'tp' in self.status:
				self.status = self.status.replace('_tp', '')

	def cooldowns(self):
		current_time = pygame.time.get_ticks()

		if self.attacking:
			if current_time - self.attack_time >= self.attack_cooldown + weapon_data[self.weapon]['cooldown']:
				self.attacking = False
				self.destroy_attack()

		if not self.blocking:
			if current_time - self.block_time >= 3000:
				self.block_count = 0

		if self.casting:
			if current_time - self.cast_time >= 800 + weapon_data[self.weapon]['cooldown']:
				self.casting = False

		if self.tping:
			if current_time -self.tp_time >= 500:
				self.tping = False
		if not self.can_tp:
			if current_time - self.tp_time >= 3000:
				self.can_tp = True
		if not self.can_cast:
			if current_time - self.cast_time >= 1000:
				self.can_cast = True
		if not self.can_atk:
			if current_time - self.attack_time >= 700:
				self.can_atk = True
		
		if not self.can_switch_weapon:
			if current_time - self.weapon_switch_time >= self.switch_duration_cooldown:
				self.can_switch_weapon = True

		if not self.can_switch_magic:
			if current_time - self.magic_switch_time >= self.switch_duration_cooldown:
				self.can_switch_magic = True

		if not self.vulnerable:
			if current_time - self.hurt_time >= self.invulnerability_duration:
				self.vulnerable = True

	def animate(self):
		animation = self.animations[self.status]

		# loop over the frame index 
		if not 'attack' in self.status and not 'cast' in self.status and not 'tp' in self.status:
			self.frame_index += self.animation_speed
			if self.frame_index >= len(animation):
				self.frame_index = 0
		else:
			if self.frame_index <= len(animation) - 1:
				self.frame_index += self.animation_speed

		# set the image
		self.image = animation[int(self.frame_index)]
		self.rect = self.image.get_rect(center = self.hitbox.center)

		# flicker 
		if not self.vulnerable:
			alpha = self.wave_value()
			self.image.set_alpha(alpha)
		else:
			self.image.set_alpha(255)

	def get_full_weapon_damage(self):
		base_damage = self.stats['attack']
		weapon_damage = weapon_data[self.weapon]['damage']
		return base_damage + weapon_damage

	def get_full_magic_damage(self):
		base_damage = self.stats['magic']
		spell_damage = magic_data[self.magic]['strength']
		return base_damage + spell_damage

	def get_value_by_index(self,index):
		return list(self.stats.values())[index]

	def get_cost_by_index(self,index):
		return list(self.upgrade_cost.values())[index]

	def energy_recovery(self):
		if self.energy < self.stats['energy']:
			self.energy += 0.01 * self.stats['magic']
		else:
			self.energy = self.stats['energy']

	def update(self):
		self.input()
		self.cooldowns()
		self.get_status()
		self.animate()
		self.move(self.stats['speed'])
		self.energy_recovery()