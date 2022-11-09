from random import randint
from tkinter import HORIZONTAL
from support import *
import pygame
from setting import *
from entity import *


class Player(Entity):
    def __init__(self,pos,groups,obs_spi,create_attack,destroy_attack, create_magic):
        super().__init__(groups)
        self.image = pygame.image.load('../graphic/test/player.png').convert_alpha()
        self.rect = self.image.get_rect(topleft = pos)
        self.hitbox = self.rect.inflate(0,-10)
        self.hitbox.y -= 20

        self.atk_cd = 400
        self.atk_time = None
        self.atking = False

        self.obs_spi = obs_spi
        self.import_player()
        self.status = 'down'
        self.create_attack = create_attack
        self.destroy_attack = destroy_attack
        self.weaponidx = 0  
        self.weapon = list(weapon_data.keys())[self.weaponidx]  
        self.can_switch_weapon = True
        self.weapon_switch_time = None 
        self.switch_duration_cooldown = 200

        self.create_magic = create_magic
        self.magicidx = 0
        self.magic = list(magic_data.keys())[self.magicidx]  
        self.can_switch_magic = True
        self.magic_switch_time = None 
        self.switch_duration_cooldown = 200


        #STAT
        self.stats = {'health' : 100, 'energy' : 60, 'attack': 10, 'magic': 4, 'speed' : 6}
        self.health = self.stats['health']
        self.energy = self.stats['energy']
        self.exp = 123
        self.speed = self.stats['speed']
    def get_status(self):

        if self.direction.x == 0 and self.direction.y == 0:
            if not 'idle' in self.status and not 'attack' in self.status:
                self.status = self.status + '_idle'
        
        if self.atking:
            self.direction.x = 0
            self.direction.y = 0
            if not 'attack' in self.status:
                if 'idle' in self.status:
                    self.status = self.status.replace('idle','attack')
                else:
                    self.status += '_attack'
        else:
            if 'attack' in self.status:
                self.status = self.status.replace('_attack','')

    def input(self):
        keys = pygame.key.get_pressed()

        if not self.atking:
            if keys[pygame.K_UP]:
                self.direction.y = -1
                self.status = 'up'
            elif keys[pygame.K_DOWN]:
                self.direction.y = 1
                self.status = 'down'
            else:
                self.direction.y = 0
            
            if keys[pygame.K_RIGHT]:
                self.direction.x = 1
                self.status = 'right'
            elif keys[pygame.K_LEFT]:
                self.direction.x = -1
                self.status = 'left'
            else:
                self.direction.x = 0

            if keys[pygame.K_SPACE]:
                self.atking = True
                self.atk_time = pygame.time.get_ticks()
                self.create_attack()
            if keys[pygame.K_LCTRL]:
                self.atk_time = pygame.time.get_ticks()
                self.atking = True
                style =  list(magic_data.keys())[self.magicidx]
                strength = list(magic_data.values())[self.magicidx]['strength'] + self.stats['magic']
                cost = list(magic_data.values())[self.magicidx]['cost']
                self.create_magic(style, strength, cost)
            if keys[pygame.K_q] and self.can_switch_weapon:
                self.can_switch_weapon = False
                self.weapon_switch_time = pygame.time.get_ticks()
                if self.weaponidx < len(list(weapon_data.keys())) - 1:
                    self.weaponidx += 1
                else:
                    self.weaponidx = 0
                self.weapon = list(weapon_data.keys())[self.weaponidx]
            if keys[pygame.K_e] and self.can_switch_magic:
                self.can_switch_magic = False
                self.magic_switch_time = pygame.time.get_ticks()
                if self.magicidx < len(list(magic_data.keys())) - 1:
                    self.magicidx += 1
                else:
                    self.magicidx = 0
                self.magic = list(magic_data.keys())[self.magicidx]

    
    def update(self):
        self.input()
        self.cooldown()
        self.get_status()
        self.animate()
        self.move(self.speed)

    def animate(self):
        animation = self.animations[self.status]

        self.frame_idx += self.animation_speed
        if self.frame_idx >= len(animation):
            self.frame_idx = 0

        self.image = animation[int(self.frame_idx)]
        self.rect = self.image.get_rect(center = self.hitbox.center)

    def import_player(self):
        cha_path = '../graphic/player/'
        self.animations = {'up' : [], 'down' : [], 'left' : [], 'right' : [], 'right_idle' : [], 'left_idle' : [], 'up_idle' : [], 'down_idle' : [],
            'right_attack' : [], 'left_attack' : [], 'up_attack' : [], 'down_attack' : []}

        for animation in self.animations.keys():
            full_path = cha_path + animation
            self.animations[animation] = import_folder(full_path)

    def cooldown(self):
        timer = pygame.time.get_ticks()

        if self.atking :
            if timer - self.atk_time >= self.atk_cd:
                self.atking = False
                self.destroy_attack()
        if not self.can_switch_weapon:
            if timer - self.weapon_switch_time >= self.switch_duration_cooldown:
                self.can_switch_weapon = True
        if not self.can_switch_magic:
            if timer - self.magic_switch_time >= self.switch_duration_cooldown:
                self.can_switch_magic = True