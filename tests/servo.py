#first implementation of opening and closing the claw

#imports for controlling the input
import tty
import sys
import termios

#imports for controlling the servo
import wiringpi
import time



wiringpi.wiringPiSetupGpio()
wiringpi.pinMode(18, wiringpi.GPIO.PWM_OUTPUT)
wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)

wiringpi.pwmSetClock(192)
wiringpi.pwmSetRange(2000)

#this is a dumb way to do control, fix it eventually
# saves standard input settings so that it can fix the terminal after it is done
orig_settings = termios.tcgetattr(sys.stdin)

#lets the terminal take in input without an escape char (READ:screws up the terminal)
tty.setraw(sys.stdin)    

x = 0
y = 0



while x != chr(27): # ESC

    x = sys.stdin.read(1)
    
    if x == "c":
        #if claw is !open:
        if y == 0:
            wiringpi.pwmWrite(18, 100)
            y += 1
            y = y%2
            print y
            print '\r'
        elif y == 1:
            wiringpi.pwmWrite(18, 1)
            y += 1
            y = y % 2
            print y
            print '\r'
           
        #else stop fucking up
    

# fixes the terminal
termios.tcsetattr(sys.stdin, termios.TCSADRAIN, orig_settings)
