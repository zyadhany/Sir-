import tkinter as tk
from tkinter import scrolledtext, messagebox
import subprocess
import os

exe_path = os.path.join(os.getcwd(), "sir.exe")
# Function to save the code to sir.sir and execute sir.exe
def run_code():
    code = editor.get("1.0", tk.END)
    
    # Save code to sir.sir file
    with open("sir.sir", "w") as file:
        file.write(code)
    
    # Try executing sir.exe with sir.sir as input
    try:
        result = subprocess.run([exe_path, "sir.sir"], capture_output=True, text=True)
        output_display.delete("1.0", tk.END)  # Clear previous output
        output_display.insert(tk.END, result.stdout)  # Show execution output
    except FileNotFoundError:
        messagebox.showerror("Error", "sir.exe not found")
    except Exception as e:
        messagebox.showerror("Error", f"Execution failed: {str(e)}")

# Create main window
root = tk.Tk()
root.title("Code Editor")

# Create code editor using scrolled text
editor = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=80, height=20)
editor.pack(padx=10, pady=10)

# Run button
run_button = tk.Button(root, text="Run", command=run_code)
run_button.pack(pady=5)

# Output display area
output_display = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=80, height=10)
output_display.pack(padx=10, pady=10)

# Run the Tkinter event loop
root.mainloop()
