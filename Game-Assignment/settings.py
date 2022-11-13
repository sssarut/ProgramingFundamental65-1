# game setup
WIDTH    = 1280	
HEIGTH   = 720
FPS      = 60
TILESIZE = 64
HITBOX_OFFSET_Y = {
	'player': -26,
	'object': -40,
	'object2': -40,
	'grass': -10,
	'invisible': 0}
HITBOX_OFFSET_X = {
	'player': -10,
	'object': -30,
	'object2': -30,
	'grass': -10,
	'invisible': 0}

# ui 
BAR_HEIGHT = 20
HEALTH_BAR_WIDTH = 200
ENERGY_BAR_WIDTH = 140
ITEM_BOX_SIZE = 80
UI_FONT = '../graphics/font/joystix.ttf'
UI_FONT_SIZE = 18

# general colors
WATER_COLOR = '#000000'
UI_BG_COLOR = '#222222'
UI_BORDER_COLOR = '#111111'
TEXT_COLOR = '#EEEEEE'

# ui colors
HEALTH_COLOR = 'red'
ENERGY_COLOR = 'blue'
UI_BORDER_COLOR_ACTIVE = 'gold'

# upgrade menu
TEXT_COLOR_SELECTED = '#111111'
BAR_COLOR = '#EEEEEE'
BAR_COLOR_SELECTED = '#111111'
UPGRADE_BG_COLOR_SELECTED = '#EEEEEE'

# weapons 
weapon_data = {
	'sword': {'cooldown': 100, 'damage': 15,'graphic':'../graphics/weapons/sword/full.png'}}

# magic
magic_data = {
	'flame': {'strength': 5,'cost': 20,'graphic':'../graphics/particles/flame/fire.png'},
	'heal' : {'strength': 20,'cost': 10,'graphic':'../graphics/particles/heal/heal.png'}}

# enemy
monster_data = {
	'red_skull': {'health': 100,'exp':5,'damage':10,'attack_type': 'Flam', 'attack_sound':'../audio/attack/slash.wav', 'speed': 2, 'resistance': 3, 'attack_radius': 30, 'notice_radius': 10000},
	'blu_skull': {'health': 100,'exp':5,'damage':10,'attack_type': 'Icey', 'attack_sound':'../audio/attack/slash.wav', 'speed': 2, 'resistance': 3, 'attack_radius': 30, 'notice_radius': 10000}}
