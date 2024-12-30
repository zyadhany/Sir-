import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext, messagebox
import tkinter.font as tkFont
import subprocess
import os
import platform

if platform.system() == "Windows":
    exe_path = os.path.join(os.getcwd(), "sss.exe")
else:
    exe_path = os.path.join(os.getcwd(), "./sir.exe")

root = tk.Tk()
root.title("Code Editor")
root.geometry("800x600")

font_size = 12
text_font = tkFont.Font(family="Courier", size=font_size)


def increase_font_size(event=None):
    global font_size
    font_size += 1
    text_font.configure(size=font_size)
    editor.configure(font=text_font)
    output_display.configure(font=text_font)


def decrease_font_size(event=None):
    global font_size
    font_size = max(8, font_size - 1)  # Minimum font size is 8
    text_font.configure(size=font_size)
    editor.configure(font=text_font)
    output_display.configure(font=text_font)


def run_code():
    output_display.delete("1.0", tk.END)
    code = editor.get("1.0", tk.END)
    code_lines = code.splitlines()

    with open("sir.sir", "w") as file:
        for line in code_lines:
            file.write(line + "\n")
    try:
        result = subprocess.run([exe_path, "sir.sir"], capture_output=True, text=True)
        output_display.delete("1.0", tk.END)
        # output_display.insert(tk.END, result.stdout)
        if result.stdout:
            output_display.insert(tk.END, result.stdout)

            # Display the standard error (runtime errors)
        if result.stderr:
            output_display.insert(tk.END, "\n[Error Output]:\n", "error")
            output_display.insert(tk.END, result.stderr, "error")

    except FileNotFoundError:
        messagebox.showerror("Error", f"{exe_path} not found")
    except Exception as e:
        messagebox.showerror("Error", f"Execution failed: {str(e)}")


icon_path = "sirsharp.ico"  # Replace with your icon file path
if os.path.exists(icon_path):
    root.iconbitmap(icon_path)


style = ttk.Style()
style.theme_use("clam")

# Customize colors for dark mode
root.configure(bg="#333333")  # Dark background for the main window
style.configure("TFrame", background="#333333")
style.configure("TLabel", background="#333333", foreground="#ffffff", font=("Arial", 10))
style.configure("TButton", background="#555555", foreground="#ffffff", font=("Arial", 10), padding=6)
style.map("TButton", background=[("active", "#777777")])
style.configure("TScrollbar", background="#444444")
style.configure("TEntry", fieldbackground="#222222", foreground="#ffffff", background="#444444")
style.configure("TText", background="#222222", foreground="#ffffff")

# Main frame
main_frame = ttk.Frame(root)
main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

# Code editor
editor_label = ttk.Label(main_frame, text="Code Editor")
editor_label.pack(anchor=tk.W, pady=(0, 5))

editor = scrolledtext.ScrolledText(
    main_frame, wrap=tk.WORD, width=80, height=20, background="#222", foreground="#fff", insertbackground="white"
)
editor.pack(fill=tk.BOTH, expand=True, pady=(0, 10))

# Run button
run_button = ttk.Button(main_frame, text="Run Code", command=run_code)
run_button.pack(pady=5, anchor=tk.CENTER)

# Output display
output_label = ttk.Label(main_frame, text="Output")
output_label.pack(anchor=tk.W, pady=(10, 5))

output_display = scrolledtext.ScrolledText(
    main_frame, wrap=tk.WORD, width=80, height=10, background="#222", foreground="#fff", insertbackground="white"
)
output_display.tag_config("error", foreground="red")  # Highlight error messages in red
output_display.pack(fill=tk.BOTH, expand=True)

root.bind("<Control-plus>", increase_font_size)  # Ctrl +
root.bind("<Control-minus>", decrease_font_size)  # Ctrl -

# Run the application
root.mainloop()
