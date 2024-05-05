import tkinter as tk
from time import strftime
import pygame

# Initialize Pygame mixer
pygame.mixer.init()

# Load the sound
dong_sound = pygame.mixer.Sound("dong.wav")

# Create the main window
root = tk.Tk()
root.title("ENGclk")

# Customize the window size and make it non-resizable
root.geometry("410x130")  # Width x Height
root.resizable(0, 0)  # Disable resizing

# Styling the clock to resemble a code editor
background_color = '#000000'  # Black background
normal_color = '#00FF00'  # Green color for normal time
hex_color = '#0000FF'  # Blue color for hexadecimal time
binary_color = '#FF0000'  # Red color for binary time

# Configure the main window's background color
root.configure(bg=background_color)

# Function to convert time to hexadecimal
def time_to_hex(time_str):
    return ':'.join(f'{int(part):02X}' for part in time_str.split(':'))

# Function to convert time to binary
def time_to_binary(time_str):
    return ' '.join(f'{int(part):08b}' for part in time_str.split(':'))

# Function to update time
def update_time():
    current_time = strftime('%H:%M:%S')  # 24-hour format with seconds
    if current_time.endswith("00:00"):  # Play sound every hour on the hour
        pygame.mixer.Sound.play(dong_sound)
    
    hex_time = time_to_hex(current_time)  # Convert to hexadecimal
    binary_time = time_to_binary(current_time)  # Convert to binary
    
    # Set the time display with different colors and sizes
    hex_display.config(text=hex_time)
    time_display.config(text=current_time)
    binary_display.config(text=binary_time)
    
    # Schedule this function to be called every second
    root.after(1000, update_time)

# Define the fonts
hex_font = ('Consolas', 30, 'bold')  # Larger font for hexadecimal
normal_font = ('Consolas', 20)
binary_font = ('Consolas', 20)

# Labels for displaying the time
hex_display = tk.Label(root, font=hex_font, bg=background_color, fg=hex_color, padx=0, pady=0)
hex_display.pack(fill='x', anchor='w')

time_display = tk.Label(root, font=normal_font, bg=background_color, fg=normal_color, padx=0, pady=0)
time_display.pack(fill='x', anchor='w')

binary_display = tk.Label(root, font=binary_font, bg=background_color, fg=binary_color, padx=0, pady=0)
binary_display.pack(fill='x', anchor='w')

# Start the time update loop
update_time()

# Start the Tkinter event loop
root.mainloop()
