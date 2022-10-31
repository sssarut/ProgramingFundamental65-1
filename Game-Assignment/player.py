from tkinter import HORIZONTAL
from support import *
import pygame
from setting import *


class Player(pygame.sprite.Sprite):
    def __init__(self,pos,groups,obs_spi,create_attack,destroy_attack):
        super().__init__(groups)
        self.image = pygame.image.load('../graphic/test/player.png').convert_alpha()
        self.rect = self.image.get_rect(topleft = pos)
        self.hitbox = self.rect.inflate(0,-10)
        self.hitbox.y -= 20

        self.direction = pygame.math.Vector2()
        self.speed = 5
        self.atk_cd = 400
        self.atk_time = None
        self.atking = False
        self.frame_idx = 0
        self.animation_speed = 0.15 

        self.obs_spi = obs_spi
        self.import_player()
        self.status = 'down'
        self.create_attack = create_attack
        self.destroy_attack = destroy_attack
        self.weaponidx = 0
        self.weapon = list(weapon_data.keys())[self.weaponidx]   
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
                print('mage')

    
    def move(self,speed):
        if self.direction.magnitude() != 0:
            self.direction = self.direction.normalize()
        #self.rect.center += self.direction * self.speed
        self.hitbox.x += self.direction.x * speed
        self.collision('horizontal')
        self.hitbox.y += self.direction.y * speed
        self.collision('vertical')
        self.rect.center = self.hitbox.center
        self.rect.y = self.hitbox.y - 10

    def collision(self, direction):
        if direction == 'horizontal':
            for sprite in self.obs_spi:
                if sprite.hitbox.colliderect(self.hitbox):
                    if self.direction.x > 0:
                        self.hitbox.right = sprite.hitbox.left
                    if self.direction.x < 0:
                        self.hitbox.left = sprite.hitbox.right
        if direction == 'vertical':
            for sprite in self.obs_spi:
                if sprite.hitbox.colliderect(self.hitbox):
                    if self.direction.y > 0:
                        self.hitbox.bottom = sprite.hitbox.top
                    if self.direction.y < 0:
                        self.hitbox.top = sprite.hitbox.bottom
    
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