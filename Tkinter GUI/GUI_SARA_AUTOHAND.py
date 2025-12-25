import tkinter as tk

def atualizar_label_amp(valor):
    label_valor_amp.config(text=f"Amplitude: {int(float(valor))}") # Converte para int para exibir
def atualizar_label_vel(valor):
    label_valor_vel.config(text=f"Velocidade: {int(float(valor))}") # Converte para int para exibir

root = tk.Tk()
root.title("AUTOHAND")

#Amplitude
slider_amp = tk.Scale(root, from_=0, to=180, orient='horizontal', command=atualizar_label_amp)
slider_amp.pack(pady=20)

label_valor_amp = tk.Label(root, text="Amplitude: 0")
label_valor_amp.pack(pady=10)

#Velocidade
slider_vel = tk.Scale(root, from_=0, to=100, orient='horizontal', command=atualizar_label_vel)
slider_vel.pack(pady=20)

label_valor_vel = tk.Label(root, text="Velocidade: 0")
label_valor_vel.pack(pady=10)

root.mainloop()
