import serial
from tkinter import *

# Initialise la communication série avec Arduino
arduino = serial.Serial('/dev/cu.usbserial-1230', 9600, timeout=.1) # Changer ce port par le port ou votre arduino est brancher

def send_command(command):
    arduino.write(str(command).encode())

# Interface graphique
root = Tk()
root.title("Drink_bot-V3")

# Couleur et style pour les boutons
button_bg_color = 'black'
button_fg_color = 'darkgreen'  # Vert foncé
button_font = ('Arial', 14)
button_width = 15
button_height = 3

def send_eau_command():
    send_command(3)

def send_ice_tea_command():
    send_command(2)

def send_sirop_command():
    send_command(1)

# Fonction pour créer un bouton avec le style défini
def create_button(text, command):
    button = Button(root, text=text, command=command, bg=button_bg_color, fg=button_fg_color, font=button_font)
    button.config(width=button_width, height=button_height)
    button.pack(pady=10)
    return button

# Création des boutons avec le style défini
button1 = create_button("Sirop", send_sirop_command)
button2 = create_button("Ice-tea", send_ice_tea_command)
button3 = create_button("Eau", send_eau_command)

root.mainloop()
