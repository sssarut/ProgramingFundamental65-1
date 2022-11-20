import pygame, sys
from settings import *
from level import Level
from menu import Menu
from name import Name
import json

scoreboard = {
	'god' : 9999999
}
try:
	with open('sc.txt') as score_file:
		scoreboard = json.load(score_file)
except: 
	pass


class Game:
	def __init__(self):

		# general setup
		pygame.init()
		self.screen = pygame.display.set_mode((WIDTH,HEIGTH))
		pygame.display.set_caption('Ruin')
		self.clock = pygame.time.Clock()

		self.level = Level()
		self.name = Name()

		# sound 
		self.image = pygame.image.load('../graphics/tilemap/Screen.png')
		self.image2 = pygame.image.load('../graphics/tilemap/Score.png')
		self.image3 = pygame.image.load('../graphics/tilemap/Wait.png')
		self.image4 = pygame.image.load('../graphics/tilemap/Text.png')
		self.font = pygame.font.Font(UI_FONT, 10)
		self.rect = self.image.get_rect(topleft = (0,0))
		main_sound = pygame.mixer.Sound('../audio/menu.wav')
		main_sound.set_volume(0.2)
		main_sound.play(loops = -1)
		self.text_surf = self.font.render('65011019 Sarut Somprasert',False,TEXT_COLOR)
		self.text_rect = self.text_surf.get_rect(center = ((1280 // 2), 700))

	def run(self):
		while True:
			self.screen.fill(WATER_COLOR)
			self.menu = Menu()
			if self.level.mode == 'm' or self.level.mode == 'r':
				if self.level.mode == 'm':
					self.screen.blit(self.image, self.rect)
				if self.level.mode == 'r':
					self.screen.blit(self.image3, self.rect)
				self.menu.display(self.level.mode)
			if self.menu.highscore == True:
				self.level.toggle_score()
			if self.level.mode == 'u':
				self.level.upgrade.display()
			if self.menu.start == True:
				self.level.game_paused = False
				self.level.toggle_time()
			if self.level.mode == 't':
				self.level.game_paused = True
				self.screen.blit(self.image4, self.rect)
				self.name.text_input(self.level, scoreboard)
			if self.level.mode == 's':
				self.level.game_paused = True
				self.screen.blit(self.image2, self.rect)
				self.name.show_score(scoreboard)

			for event in pygame.event.get():
				if event.type == pygame.QUIT or self.menu.exit == True:
					with open('sc.txt', 'w') as score_file:
						json.dump(scoreboard,score_file)
					pygame.quit()
					sys.exit()
				if event.type == pygame.KEYDOWN and self.level.mode != 't':
					if event.key == pygame.K_u and self.level.mode == 'n' and self.level.capture == 1:
						self.level.toggle_upgrade()
					if event.key == pygame.K_m and self.level.mode == 'n':
						self.level.toggle_menu()
					elif event.key == pygame.K_l:
						if self.level.mode == 'r' or self.level.mode == 'u':
							self.level.toggle_time()
						elif self.level.mode == 's':
							self.level.toggle_home()
					elif event.key == pygame.K_4:
						self.level.death = True
						self.level.mode = 't'
					elif event.key == pygame.K_5:
						self.level.player.exp += 500000000


			#Run Level 
			if self.level.end == 1:
				self.level = Level()
			if self.level.game_paused == False and self.level.end == 0:
				self.level.run()
			pygame.draw.rect(self.screen,UI_BG_COLOR,self.text_rect.inflate(20,20))
			self.screen.blit(self.text_surf,self.text_rect)
			pygame.draw.rect(self.screen,UI_BORDER_COLOR,self.text_rect.inflate(20,20),3)
			pygame.display.update()
			self.clock.tick(FPS)

if __name__ == '__main__':
	game = Game()
	game.run()