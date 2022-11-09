from re import I
import pygame
from setting import *
from tile import Tile
from player import *
from debug import *
from support import *
#from setting import *
from random import choice
from weapon import *
from ui import *

class Level:
    def __init__(self):
        self.display_surface = pygame.display.get_surface()
        self.vis_spi = YCamGroup()
        self.obs_spi = pygame.sprite.Group()
        self.create_map()
        self.current_attack = None

        #UI
        self.ui = UI()

    def create_attack(self):
        self.current_attack = Weapon(self.player, [self.vis_spi])

    def destroy_attack(self):
        if self.current_attack != None:
            #self.current_attack = None
            self.current_attack.kill()
            self.current_attack = None

    def create_map(self):
        layouts = {
                'boundary' : import_csv_layout('../map/Floorblock_Boundary.csv'),
                'plant' : import_csv_layout('../map/Floorblock_Corpse.csv'),
                #'object' : import_csv_layout('../map/map_Objects.csv')
        }
        graphic = {
            'plant' : import_folder('../graphic/Grass'),
            #'object' : import_folder('../graphic/objects')
        }

        for style, layout in layouts.items():
            for row_idx, row in enumerate(layout):
                for col_idx, col in enumerate(row):
                    if col != '-1':
                        x = col_idx * TIL_SIZ
                        y = row_idx * TIL_SIZ
                        if style == 'boundary':
                            Tile((x, y), [self.obs_spi],'invisible')
                        if style == 'plant':
                            random_grass_image = choice(graphic['plant'])
                            Tile((x, y), [self.vis_spi], 'plant',random_grass_image)
                            #Tile((x, y), [self.vis_spi], )
                        if style == 'object':
                            surf = graphic['object'][int(col)]
                            Tile((x, y),[self.vis_spi, self.obs_spi], 'object', surf)
        #for row_idx,row in enumerate(MAP):
        #    #print(row_idx)
        #    #print(row)
        #    for  col_idx,col in enumerate(row):
        #        x = col_idx * TIL_SIZ
        #        y = row_idx * TIL_SIZ
        #        if col == 'x':
        #            Tile((x,y),[self.vis_spi,self.obs_spi])
        #        if col == 'c':
        #            self.player = Player((x,y),[self.vis_spi], self.obs_spi)
        self.player = Player((640, 640), [self.vis_spi], self.obs_spi, self.create_attack, self.destroy_attack, self.create_magic)
        self.hitbox = self.player.hitbox
    
    def create_magic(self, style, strength, cost):
        print(style)
        print(strength)
        print(cost)
    def run(self):
        self.vis_spi.custom_draw(self.player)
        pygame.draw.rect(self.display_surface, (255, 255, 255), self.hitbox, 2)
        self.vis_spi.update()
        self.ui.display(self.player)
        #debug(self.player.status)

class YCamGroup(pygame.sprite.Group):
    def __init__(self):
        super().__init__()
        self.display_surface = pygame.display.get_surface()
        self.halfwid = self.display_surface.get_size()[0] // 2
        self.halfhei = self.display_surface.get_size()[1] // 2
        self.offset = pygame.math.Vector2()
        self.floor_surface = pygame.image.load('../graphic/tilemap/groundd.png').convert()
        self.floor_rect = self.floor_surface.get_rect(topleft = (0, 0))
    
    def custom_draw(self, player):

        self.offset.x = player.rect.centerx - self.halfwid
        self.offset.y = player.rect.centery - self.halfhei
        #for sprite in self.sprites():
        floor_off_pos = self.floor_rect.topleft - self.offset
        self.display_surface.blit(self.floor_surface,floor_off_pos)
        for sprite in sorted(self.sprites(), key = lambda sprite: sprite.rect.centery):
            offset_pos = sprite.rect.topleft - self.offset
            self.display_surface.blit(sprite.image,offset_pos)