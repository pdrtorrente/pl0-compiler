
import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext
import subprocess
import os
import re
from functools import partial

def selecionar_arquivo():
    caminho = filedialog.askopenfilename(filetypes=[("Arquivos de texto", "*.txt")])
    if caminho:
        entrada_var.set(caminho)

def mostrar_tooltip(evento, mensagem):
    global tooltip
    tooltip = tk.Toplevel(codigo_fonte)
    tooltip.wm_overrideredirect(True)
    tooltip.wm_geometry(f"+{evento.x_root + 10}+{evento.y_root + 10}")
    label = tk.Label(tooltip, text=mensagem, background="#ffdddd", relief="solid", borderwidth=1)
    label.pack()

def esconder_tooltip(evento):
    global tooltip
    if tooltip:
        tooltip.destroy()
        tooltip = None

def executar_analisador():
    caminho_entrada = entrada_var.get()
    caminho_saida = saida_var.get()
    caminho_exe = r".\pl0.exe" if os.name == 'nt' else "./pl0"

    if not caminho_entrada:
        messagebox.showwarning("Aviso", "Selecione o arquivo de entrada.")
        return

    try:
        resultado = subprocess.run([caminho_exe, caminho_entrada, caminho_saida],
                                   capture_output=True, text=True)

        saida_texto.delete("1.0", tk.END)
        codigo_fonte.delete("1.0", tk.END)
        codigo_fonte.tag_delete("erro")

        # Mostrar o código-fonte original
        with open(caminho_entrada, 'r', encoding='utf-8') as f:
            linhas = f.readlines()
            codigo_fonte.insert(tk.END, "".join(linhas))

        # Mostrar saída do analisador
        if resultado.stdout:
            saida_texto.insert(tk.END, resultado.stdout)
        if resultado.stderr:
            saida_texto.insert(tk.END, resultado.stderr)

        # # Marcar erros no código-fonte com debug
        # erros = resultado.stderr.splitlines()
        # for erro in erros:
        #     print(f"Debug: erro bruto = {erro}")  # DEBUG
        #     m = re.search(r"linha (\d+) caracter (\d+).*?: (.*)", erro)
        #     if m:
        #         linha, _, msg = int(m[1]), int(m[2]), m[3]
        #         print(f"Debug: linha={linha}, msg={msg}")  # DEBUG
        #         linha_ini = f"{linha}.0"
        #         linha_fim = f"{linha}.end"
        #         codigo_fonte.tag_add("erro", linha_ini, linha_fim)
        #         codigo_fonte.tag_bind("erro", "<Enter>", partial(mostrar_tooltip, mensagem=msg))
        #         codigo_fonte.tag_bind("erro", "<Leave>", esconder_tooltip)

        codigo_fonte.tag_config("erro", background="#ffcccc")

    except FileNotFoundError:
        messagebox.showerror("Erro", f"Executável '{caminho_exe}' não encontrado.")

janela = tk.Tk()
janela.title("Analisador PL/0")

entrada_var = tk.StringVar()
saida_var = tk.StringVar(value="saida.txt")
tooltip = None

# Interface
frame = tk.Frame(janela, padx=10, pady=10)
frame.pack()

tk.Label(frame, text="Arquivo de entrada:").grid(row=0, column=0, sticky="w")
tk.Entry(frame, textvariable=entrada_var, width=40).grid(row=0, column=1)
tk.Button(frame, text="Selecionar", command=selecionar_arquivo).grid(row=0, column=2)

tk.Label(frame, text="Arquivo de saída:").grid(row=1, column=0, sticky="w")
tk.Entry(frame, textvariable=saida_var, width=40).grid(row=1, column=1)

tk.Button(janela, text="Executar Analisador", command=executar_analisador, bg="green", fg="white").pack(pady=10)

tk.Label(janela, text="Código Fonte:").pack()
codigo_fonte = scrolledtext.ScrolledText(janela, width=70, height=20)
codigo_fonte.pack(padx=10, pady=(0,10))

tk.Label(janela, text="Saída:").pack()
saida_texto = scrolledtext.ScrolledText(janela, width=70, height=10)
saida_texto.pack(padx=10, pady=10)

janela.mainloop()
