import tkinter as tk
from datetime import datetime, timedelta
from PIL import Image, ImageTk
import pytz

def update_time():
    now = datetime.now(pytz.timezone('America/Los_Angeles'))
    target = datetime(2024, 6, 14, 0, 0, tzinfo=pytz.timezone('America/Los_Angeles'))
    remaining = target - now
    if remaining < timedelta(0):
        remaining = timedelta(0)  # Timer will not go negative
    days = remaining.days
    seconds = remaining.seconds
    hours, remainder = divmod(remaining.seconds, 3600)
    minutes, seconds = divmod(remainder, 60)
    timer_str = f"{days} days {hours:02}:{minutes:02}:{seconds:02}"
    time_label.config(text=timer_str)
    root.after(1000, update_time)  # Update the label every second

root = tk.Tk()
root.title("Countdown to Graduation")

# Set the geometry of the tkinter window
root.geometry("400x450")

# Load an image using PIL's Image module
graduate_image = Image.open("C:\\Users\\walka\\Desktop\\git\\grad_count\\graduate_image.png")
graduate_image = graduate_image.resize((400, 400), Image.Resampling.LANCZOS)
graduate_image_img = ImageTk.PhotoImage(graduate_image)

# Create a Label for the image
graduate_label = tk.Label(root, image=graduate_image_img)
graduate_label.pack()

# Create a Label for the countdown timer with a modern and bold font
time_label = tk.Label(root, font=('Helvetica', 35, 'bold'), fg='green')
time_label.pack()

# Start updating the time immediately
update_time()

root.mainloop()
