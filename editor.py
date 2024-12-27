import tkinter as tk
from tkinter import scrolledtext, messagebox
import subprocess
import os
import platform

if platform.system() == "Windows":
    exe_path = os.path.join(os.getcwd(), "sss.exe")
else:
    exe_path = os.path.join(os.getcwd(), "./sss.exe")
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
        output_display.insert(tk.END, result.stdout)
    except FileNotFoundError:
        messagebox.showerror("Error", f"{exe_path} not found")
    except Exception as e:
        messagebox.showerror("Error", f"Execution failed: {str(e)}")
root = tk.Tk()
root.title("Code Editor")
editor = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=80, height=20)
editor.pack(padx=10, pady=10)
run_button = tk.Button(root, text="Run", command=run_code)
run_button.pack(pady=5)
output_display = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=80, height=10)
output_display.pack(padx=10, pady=10)
root.mainloop()
