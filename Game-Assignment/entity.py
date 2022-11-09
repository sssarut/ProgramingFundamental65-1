import pygame

class Entity(pygame.sprite.Sprite):
    def __init__(self, groups):
        super().__init__(groups)
        self.frame_idx = 0
        self.animation_speed = 0.15
        self.direction = pygame.math.Vector2()

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