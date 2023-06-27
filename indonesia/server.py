from flask import Flask
import pygame

app = Flask(__name__)

@app.route("/play_sound")

def play_sound():
    sound_file = r"C:\Music\untitled.mp3" #Ubah ke tempat folder suara yang ingin dimainkan

    pygame.mixer.init()
    pygame.mixer.music.load(sound_file)
    pygame.mixer.music.play()

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)