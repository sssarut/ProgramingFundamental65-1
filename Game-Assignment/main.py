import pygame, sys
from settings import *
from level import Level
from menu import Menu

class Game:
	def __init__(self):

		# general setup
		pygame.init()
		self.screen = pygame.display.set_mode((WIDTH,HEIGTH))
		pygame.display.set_caption('Depth')
		self.clock = pygame.time.Clock()

		self.level = Level()

		# sound 
		#main_sound = pygame.mixer.Sound('../audio/main.ogg')
		#main_sound.set_volume(0.5)
		#main_sound.play(loops = -1)
	
	def run(self):
		while True:
			self.screen.fill(WATER_COLOR)
			self.menu = Menu()
			if self.level.mode == 'm':
				self.menu.display()
			if self.menu.start == True:
				self.level.game_paused = False
				self.level.mode = 'n'
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					pygame.quit()
					sys.exit()
				#Use menu or other GUI
				if event.type == pygame.KEYDOWN:
					if event.key == pygame.K_u and self.level.mode == 'n':
						self.level.toggle_upgrade()
					elif event.key == pygame.K_m and self.level.mode == 'n':
						self.level.toggle_menu()
					elif event.key == pygame.K_l:
						self.level.toggle_time()

			#Run Level 
			if self.level.game_paused == False:
				self.level.run()
			pygame.display.update()
			self.clock.tick(FPS)

if __name__ == '__main__':
	game = Game()
	game.run()