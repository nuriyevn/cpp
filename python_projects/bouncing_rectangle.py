import pygame
 
# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
LILAC = (200, 162, 200)
 
pygame.init()

info = pygame.display.Info()

width = info.current_w / 2
height = (info.current_h - 100) /2

ext_square_w = 100
ext_square_h = 100

 
# Set the height and width of the screen
size = [width, height]
screen = pygame.display.set_mode(size)
 
pygame.display.set_caption("Bouncing Rectangle")
 
# Loop until the user clicks the close button.
done = False
 
# Used to manage how fast the screen updates
clock = pygame.time.Clock()
 
# Starting position of the rectangle
rect_x = 50
rect_y = 50

rect_x2 = 50
rect_y2 = 50
 
# Speed and direction of rectangle
rect_change_x = 2
rect_change_y = 2

rect_change_x2 = 3
rect_change_y2 = 3

class Psycho:
    rect_x = 0
    rect_y = 0
    rect_change_x = 0
    rect_change_y = 0
    color = (0, 0, 0)
    def __init__ (self, r_x, r_y, rchange_x, rchange_y, clr):
        self.rect_x = r_x
        self.rect_y = r_y
        self.rect_change_x = rchange_x
        self.rect_change_y = rchange_y
        self.color = clr
'''
psychos = []
psychos.append(Psycho(50, 50, 2, 2, GREEN))
psychos.append(Psycho(40, 40, 3, 3, LILAC))

    

psycho[0] = psycho(50, 50, 2, 2, GREEN)
psycho[1] = psycho(50, 50, 3, 3, RED)
'''
# -------- Main Program Loop -----------
while not done:
    # --- Event Processing
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
 
    # --- Logic
    # Move the rectangle starting point
    
    

    rect_x += rect_change_x
    rect_y += rect_change_y

    rect_x2 += rect_change_x2
    rect_y2 += rect_change_y2
 
    # Bounce the ball if needed
    if rect_y > height - ext_square_h or rect_y < 0:
        rect_change_y = rect_change_y * -1
    if rect_x > width - ext_square_w or rect_x < 0:
        rect_change_x = rect_change_x * -1


    if rect_y2 > height - ext_square_h or rect_y2 < 0:
        rect_change_y2 = rect_change_y2 * -1
    if rect_x2 > width - ext_square_w or rect_x2 < 0:
        rect_change_x2 = rect_change_x2 * -1
 


    # --- Drawing
    # Set the screen background
    screen.fill(BLACK)
 
    # Draw the rectangle
    pygame.draw.rect(screen, WHITE, [rect_x, rect_y, ext_square_w, ext_square_h])
    pygame.draw.rect(screen, RED, [rect_x + 10, rect_y + 10, 30, 30])
    pygame.draw.rect(screen, GREEN, [rect_x + 15, rect_y + 15, 10, 10])
    pygame.draw.rect(screen, GREEN, [rect_x + 25, rect_y + 25, 10, 10])
    pygame.draw.rect(screen, RED, [rect_x + 60, rect_y + 60, 30, 30])

    #Draw the rectangle
    pygame.draw.rect(screen, LILAC, [rect_x2, rect_y2, ext_square_w, ext_square_h])
    
          
    # --- Wrap-up
    # Limit to 60 frames per second
    clock.tick(100)
 
    # Go ahead and update the screen with what we've drawn.
    pygame.display.flip()
 
# Close everything down
pygame.quit()
