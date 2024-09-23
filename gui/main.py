from tkinter import *
import matplotlib.pyplot as plt

# create the main window of the app
root = Tk()
# set the title of the window
root.title("Antivirus")
root.resizable(False, False)   # make the window not resizeable

# --------------------------------------------------------------------------------------
dashboard = Frame(root, bg='lightblue', width=1000, height=600)
dashboard.pack_propagate(False)  # Disable auto-resizing
dashboard.pack()

menu = Frame(dashboard, bg='white', width=200, height=600)
menu.pack_propagate(False)
menu.pack(side='left', padx=10, pady=10)

# scan system button
scan_system = Button(menu, text="Scan system", bg='lime', width=20, height=2, bd=0, relief="flat", fg="black")
scan_system.pack(padx=10, pady=10)  # Add padding around the button inside the frame

scan_directory = Button(menu, text="Scan directory", bg='lime', width=20, height=2, bd=0, relief="flat", fg="black")
scan_directory.pack(padx=10, pady=(0, 10))  # Add padding around the button inside the frame

update_database = Button(menu, text="Update database", bg='lime', width=20, height=2, bd=0, relief="flat", fg="black")
update_database.pack(padx=10, pady=(0, 10))  # Add padding around the button inside the frame

# right panel
board = Frame(dashboard, bg='white', width=800, height=600)
board.pack(side='right', padx=(0, 10), pady=10)

# plot
# labels = ['A', 'B', 'C', 'D']
# sizes = [15, 30, 45, 10]  # Corresponding sizes for each label
# colors = ['gold', 'lightcoral', 'lightskyblue', 'lightgreen']  # Colors for each section
# explode = (0.1, 0, 0, 0)  # Explode the first slice (A)

# plt.pie(sizes, explode=explode, labels=labels, colors=colors,autopct='%1.1f%%', shadow=True, startangle=140)

# plt.axis('equal')

# Show the pie chart
# plt.title('Simple Pie Chart Example')
# plt.show()

# --------------------------------------------------------------------------------------

# Start the Tkinter event loop
root.mainloop()

