import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext
import subprocess
import os

def selecionar_arquivo():
    caminho = filedialog.askopenfilename(filetypes=[("Arquivos de texto", "*.txt")])
    if caminho:
        entrada_var.set(caminho)

def selecionar_executavel():
    caminho = filedialog.askopenfilename(filetypes=[("Executáveis", "*.exe" if os.name == 'nt' else "*")])
    if caminho:
        exe_var.set(caminho)

def executar_analisador():
    caminho_entrada = entrada_var.get()
    caminho_saida = saida_var.get()
    caminho_exe = exe_var.get()

    if not caminho_entrada or not caminho_exe:
        messagebox.showwarning("Aviso", "Selecione o arquivo de entrada e o executável.")
        return

    try:
        resultado = subprocess.run([caminho_exe, caminho_entrada, caminho_saida],
                                   capture_output=True, text=True)

        saida_texto.delete("1.0", tk.END)

        if resultado.returncode == 0:
            saida_texto.insert(tk.END, "Compilado com sucesso.\n")
        else:
            mensagem = resultado.stderr.strip() or resultado.stdout.strip()
            saida_texto.insert(tk.END, f"Erros encontrados:\n{mensagem}\n")

    except FileNotFoundError:
        messagebox.showerror("Erro", "Executável não encontrado.")

janela = tk.Tk()
janela.title("Analisador PL/0")

entrada_var = tk.StringVar()
saida_var = tk.StringVar(value="saida.txt")
exe_var = tk.StringVar()

# Interface
frame = tk.Frame(janela, padx=10, pady=10)
frame.pack()

tk.Label(frame, text="Arquivo de entrada:").grid(row=0, column=0, sticky="w")
tk.Entry(frame, textvariable=entrada_var, width=40).grid(row=0, column=1)
tk.Button(frame, text="Selecionar", command=selecionar_arquivo).grid(row=0, column=2)

tk.Label(frame, text="Arquivo de saída:").grid(row=1, column=0, sticky="w")
tk.Entry(frame, textvariable=saida_var, width=40).grid(row=1, column=1)

tk.Label(frame, text="Executável:").grid(row=2, column=0, sticky="w")
tk.Entry(frame, textvariable=exe_var, width=40).grid(row=2, column=1)
tk.Button(frame, text="Selecionar", command=selecionar_executavel).grid(row=2, column=2)

tk.Button(janela, text="Executar Analisador", command=executar_analisador, bg="green", fg="white").pack(pady=10)

saida_texto = scrolledtext.ScrolledText(janela, width=70, height=15)
saida_texto.pack(padx=10, pady=10)

janela.mainloop()
