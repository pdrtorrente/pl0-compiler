import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import subprocess
import os
import platform
import sys
import shutil

def escolher_arquivo():
    caminho = filedialog.askopenfilename(filetypes=[("Arquivos de texto", "*.txt")])
    if caminho and caminho.endswith(".txt"):
        entrada_var.set(caminho)
    elif caminho:
        messagebox.showerror("Erro", "O arquivo deve ter extensão .txt")

def abrir_diretorio_saida():
    path = os.path.abspath(resource_path("output_files"))
    try:
        if os.name == "nt":
            os.startfile(path)
        elif sys.platform == "darwin":
            subprocess.run(["open", path])
        else:
            subprocess.run(["xdg-open", path])
    except Exception as e:
        messagebox.showwarning("Aviso", f"Erro ao abrir diretório: {e}")

def abrir_arquivo_saida(caminho_saida):
    try:
        if os.name == "nt":
            os.startfile(caminho_saida)
        elif sys.platform == "darwin":
            subprocess.run(["open", caminho_saida])
        else:
            subprocess.run(["xdg-open", caminho_saida])
    except Exception as e:
        messagebox.showwarning("Aviso", f"Erro ao abrir o arquivo de saída:\n{e}")

def resource_path(relative_path):
    # Compatível com PyInstaller --onefile
    if hasattr(sys, '_MEIPASS'):
        return os.path.join(sys._MEIPASS, relative_path)
    return os.path.join(os.path.abspath("."), relative_path)

def executar_analisador():
    caminho_entrada = entrada_var.get().strip()
    if not caminho_entrada or not caminho_entrada.endswith(".txt"):
        messagebox.showerror("Erro", "Escolha um arquivo .txt válido.")
        return

    os.makedirs(resource_path("output_files"), exist_ok=True)
    nome_arquivo = os.path.basename(caminho_entrada)
    caminho_saida = os.path.join(resource_path("output_files"), nome_arquivo)

    sistema = platform.system()
    if sistema == "Windows":
        caminho_exe = resource_path("pl0.exe")
    else:
        caminho_exe = resource_path("pl0")

    if not os.path.exists(caminho_exe):
        messagebox.showerror("Erro", f"Executável não encontrado: {caminho_exe}")
        return

    try:
        subprocess.run([caminho_exe, caminho_entrada, caminho_saida], check=True)

        # Criar o caminho com sufixo "_compilado"
        diretorio_entrada = os.path.dirname(caminho_entrada)
        nome_base, extensao = os.path.splitext(nome_arquivo)
        nome_compilado = f"{nome_base}_compilado{extensao}"
        caminho_saida_copia = os.path.join(diretorio_entrada, nome_compilado)

        shutil.copy(caminho_saida, caminho_saida_copia)

        messagebox.showinfo("Sucesso", f"Arquivo gerado em: {caminho_saida_copia}")
        abrir_arquivo_saida(caminho_saida_copia)
    except subprocess.CalledProcessError:
        messagebox.showerror("Erro", "Erro ao executar o analisador.")
    except FileNotFoundError:
        messagebox.showerror("Erro", "Executável não encontrado.")

# Interface gráfica
root = tk.Tk()
root.title("Analisador Léxico PL/0")
root.geometry("750x500")

style = ttk.Style()
style.theme_use("clam")

frame = ttk.Frame(root, padding="15")
frame.pack(fill=tk.BOTH, expand=True)

ttk.Label(frame, text="Analisador Léxico para a linguagem PL/0", font=("Segoe UI", 14, "bold")).grid(column=0, row=0, columnspan=3, pady=(0, 10))
ttk.Label(frame, text="Selecione o arquivo .txt contendo o código-fonte em PL/0.\nA saída será gerada no mesmo diretório do arquivo de entrada.").grid(column=0, row=1, columnspan=3, sticky="w")

ttk.Label(frame, text="Caminho do arquivo de entrada:").grid(column=0, row=2, sticky="w", pady=10)
entrada_var = tk.StringVar()
entrada_entry = ttk.Entry(frame, textvariable=entrada_var, width=60)
entrada_entry.grid(column=0, row=3, padx=(0, 10), sticky="w")
ttk.Button(frame, text="Escolher...", command=escolher_arquivo).grid(column=1, row=3)

ttk.Button(frame, text="Executar Analisador", command=executar_analisador).grid(column=0, row=4, pady=20, sticky="w")
ttk.Button(frame, text="Abrir pasta de saída", command=abrir_diretorio_saida).grid(column=1, row=4, pady=20, sticky="w")

ttk.Label(frame, text="Desenvolvido por:"
                        "\n   - Agnes Bressan de Almeida"
                        "\n   - Carolina Almeida Américo"
                        "\n   - Caroline Severiano Clapis"
                        "\n   - Pedro Oliveira Torrente"
                        "\n   - Rauany Martinez Secci"
          , font=("Segoe UI", 9, "italic")).grid(column=0, row=7, columnspan=3, pady=20, sticky="w")

root.mainloop()
