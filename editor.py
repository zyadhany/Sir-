import tkinter as tk
from tkinter import ttk, PhotoImage, Toplevel
from tkinter import scrolledtext, messagebox
import tkinter.font as tkFont
import subprocess
import os
import platform
import re
import signal
import threading

current_process = None

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
    global current_process
    output_display.delete("1.0", tk.END)
    code = editor.get("1.0", tk.END)
    code_lines = code.splitlines()

    with open("sir.sir", "w") as file:
        for line in code_lines:
            file.write(line + "\n")

    def target():
        try:
            global current_process
            current_process = subprocess.Popen(
                [exe_path, "sir.sir"],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )

            while True:
                output = current_process.stdout.readline()
                if output:
                    output_display.insert(tk.END, output)
                    output_display.see(tk.END)
                elif current_process.poll() is not None:
                    break

            error_output = current_process.stderr.read()
            if error_output:
                output_display.insert(tk.END, "\n[Error Output]:\n", "error")
                output_display.insert(tk.END, error_output, "error")

            current_process = None
        except FileNotFoundError:
            messagebox.showerror("Error", f"{exe_path} not found")
        except Exception as e:
            messagebox.showerror("Error", f"Execution failed: {str(e)}")
            current_process = None

    thread = threading.Thread(target=target)
    thread.start()


icon_path = "sirsharp.ico"
if os.path.exists(icon_path):
    root.iconbitmap(icon_path)

style = ttk.Style()
style.theme_use("clam")

root.configure(bg="#333333")
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


def highlight_syntax():
    code = editor.get("1.0", tk.END)

    # Clear previous highlights
    editor.tag_remove("keyword", "1.0", tk.END)
    editor.tag_remove("print_keyword", "1.0", tk.END)
    editor.tag_remove("string", "1.0", tk.END)

    # Define the font and colors for highlighting
    editor.tag_config("keyword", foreground="darkorange", font=("Courier", font_size, "bold"))
    editor.tag_config("print_keyword", foreground="purple", font=("Courier", font_size, "bold"))
    editor.tag_config("string", foreground="lightgreen", font=("Courier", font_size))

    # Highlight keywords except "print"
    keywords = ["if", "else", "while", "end"]
    keyword_pattern = r'\b(?:' + '|'.join(re.escape(kw) for kw in keywords) + r')\b'
    for match in re.finditer(keyword_pattern, code):
        start_idx = f"1.0 + {match.start()}c"
        end_idx = f"1.0 + {match.end()}c"
        editor.tag_add("keyword", start_idx, end_idx)

    # Highlight "print" in purple
    print_pattern = r'\bprint\b'
    for match in re.finditer(print_pattern, code):
        start_idx = f"1.0 + {match.start()}c"
        end_idx = f"1.0 + {match.end()}c"
        editor.tag_add("print_keyword", start_idx, end_idx)

    # Highlight double-quoted strings ("example")
    string_pattern = r'"([^"]*)"'
    for match in re.finditer(string_pattern, code):
        start_idx = f"1.0 + {match.start()}c"
        end_idx = f"1.0 + {match.end()}c"
        editor.tag_add("string", start_idx, end_idx)


editor.bind('<KeyRelease>', lambda event: highlight_syntax())

# Run button
run_icon = PhotoImage(file="runicon.png")
run_icon = run_icon.subsample(15, 15)

run_button = ttk.Button(main_frame, image=run_icon, command=run_code)
run_button.pack(pady=5, anchor=tk.CENTER)

run_label = ttk.Label(main_frame, text="Run Code", font=("Arial", 10), foreground="white")
run_label.pack(pady=(5, 10), anchor=tk.CENTER)


output_label = ttk.Label(main_frame, text="Output")
output_label.pack(anchor=tk.W, pady=(10, 5))

output_display = scrolledtext.ScrolledText(
    main_frame, wrap=tk.WORD, width=80, height=10, background="#222", foreground="#fff", insertbackground="white"
)
output_display.tag_config("error", foreground="red")  # Highlight error messages in red
output_display.pack(fill=tk.BOTH, expand=True)

root.bind("<Control-plus>", increase_font_size)  # Ctrl +
root.bind("<Control-minus>", decrease_font_size)  # Ctrl -


# Function to terminate running process
def terminate_process(event=None):
    global current_process
    if current_process:
        try:
            # Send SIGTERM first
            current_process.terminate()
            current_process.wait(timeout=2)  # Wait to ensure it terminates gracefully
        except subprocess.TimeoutExpired:
            if platform.system() == "Windows":
                current_process.kill()
            else:
                os.kill(current_process.pid, signal.SIGKILL)
        finally:
            current_process = None
            output_display.insert(tk.END, "\n[Process terminated by user]\n", "error")
            output_display.see(tk.END)


root.bind("<Control-c>", terminate_process)


def on_close():
    global current_process
    if current_process:
        terminate_process()
    root.quit()


root.protocol("WM_DELETE_WINDOW", on_close)

root.mainloop()
