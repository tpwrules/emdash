# render some text in the tiny font so it can be
# copy and pasted into the bootsplash

import pygame.freetype as ft
import pygame
import time

pygame.init()
scr = pygame.display.set_mode((640, 480))

font = ft.Font("tom-thumb.bdf")

pygame.display.flip()
scr.fill((255, 255, 255))

font.render_to(scr, (32+4*2, 30), "Electronics and software")
font.render_to(scr, (32+4*3, 36), "for wheel and dashboard")
font.render_to(scr, (32+4*4+1, 42), "(C) 2018 Thomas Watson")
font.render_to(scr, (32, 48), "github.com/tpwrules/emdash")

pygame.display.flip()
while True:
    pygame.event.pump()
    time.sleep(0.05)