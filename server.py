from flask import Flask
import pygame

app = Flask(__name__)

@app.route("/play_sound")
def play_sound():
    sound_file = r"C:\Users\khali\Music\untitled.mp3" # change it to your sound directory

    pygame.mixer.init()
    pygame.mixer.music.load(sound_file)
    pygame.mixer.music.play()

    return "Sound played"

if __name__ == "__main__":
    play_sound()
    app.run(host="0.0.0.0", port=80)