import pygame
from support import import_folder
from random import choice

class AnimationPlayer:
    def __init__(self):
        self.frames = {
            # magic
            'flame': import_folder('../graphics/particles/flame/frames'),
            'aura': import_folder('../graphics/particles/aura'),
            'heal': import_folder('../graphics/particles/heal/frames'),
            
            # attacks 
            'claw': import_folder('../graphics/particles/claw'),
            'slash': import_folder('../graphics/particles/slash'),
            'sparkle': import_folder('../graphics/particles/sparkle'),
            'leaf_attack': import_folder('../graphics/particles/leaf_attack'),
            'thunder': import_folder('../graphics/particles/thunder'),
            'Flam': import_folder('../graphics/particles/Flam'),
            'Icey': import_folder('../graphics/particles/Icey'),
            'block' : import_folder('../graphics/particles/block'),
            'Skill_Lightning' : import_folder('../graphics/particles/Skill_Lightning/frames'),
            'Skill_Laser' : import_folder('../graphics/particles/Skill_Laser/frames'),

            # monster deaths
            'red_skull': import_folder('../graphics/particles/nova'), 
            'blu_skull': import_folder('../graphics/particles/nova') 
            }
    
    def reflect_images(self,frames):
        new_frames = []

        for frame in frames:
             flipped_frame = pygame.transform.flip(frame,True,False)
             new_frames.append(flipped_frame)
        return new_frames

    def create_grass_particles(self,pos,groups):
         animation_frames = choice(self.frames['leaf'])
         ParticleEffect(pos,animation_frames,groups, 'center')

    def create_particles(self,animation_type,pos,groups, where):
        animation_frames = self.frames[animation_type]
        ParticleEffect(pos,animation_frames,groups, where)
    def create_shield(self,animation_type,player,groups):
        animation_frames = self.frames[animation_type]
        BlockEffect(player,animation_frames,groups)


class ParticleEffect(pygame.sprite.Sprite):
    def __init__(self,pos,animation_frames,groups, where):
        super().__init__(groups)
        self.sprite_type = 'magic'
        self.frame_index = 0
        self.animation_speed = 0.15
        self.frames = animation_frames
        self.image = self.frames[self.frame_index]
        if where == 'center':
            self.rect = self.image.get_rect(center = pos)
        elif where == 'down':
            self.rect = self.image.get_rect(midbottom = pos)
        elif where == 'right':
            self.rect = self.image.get_rect(midright = pos)
        elif where == 'left':
            self.rect = self.image.get_rect(midleft = pos)

    def animate(self):
        self.frame_index += self.animation_speed
        if self.frame_index >= len(self.frames):
            self.kill()
        else:
            self.image = self.frames[int(self.frame_index)]

    def update(self):
        self.animate()

class BlockEffect(pygame.sprite.Sprite):
    def __init__(self,player,animation_frames,groups):
        super().__init__(groups)
        self.sprite_type = 'magic'
        self.frame_index = 0
        self.player = player
        self.animation_speed = 0.15
        self.frames = animation_frames
        self.image = self.frames[self.frame_index]
        self.rect = self.image.get_rect(center = player.rect.center)

    def animate(self):
        if not self.player.blocking:
            self.kill()
        else:
            self.image = self.frames[0]

    def update(self):
        self.animate()
